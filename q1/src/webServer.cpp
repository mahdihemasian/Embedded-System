#include "fields_alloc.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <cstring>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <string.h>
#include "stdlib.h"
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <stdio.h>
#include <mysql/mysql.h>
#include "unistd.h"
#include "MQTTClient.h"

namespace beast = boost::beast;         
namespace http = beast::http;   
namespace net = boost::asio;        
using tcp = boost::asio::ip::tcp;       

class FFError
{
public:
    std::string    Label;

    FFError( ) { Label = (char *)"Generic Error"; }
    FFError( char *message ) { Label = message; }
    ~FFError() { }
    inline const char*   GetMessage  ( void )   { return Label.c_str(); }
};


MYSQL      *MySQLConRet;
MYSQL      *MySQLConnection = NULL;
MYSQL_RES  *MySQLResult;
MYSQL_ROW  row;



std::string picture();

std::string returnLastNData(const char* table, int num);

// Return a reasonable mime type based on the extension of a file.
beast::string_view
mime_type(beast::string_view path)
{
    using beast::iequals;
    auto const ext = [&path]
    {
        auto const pos = path.rfind(".");
        if(pos == beast::string_view::npos)
            return beast::string_view{};
        return path.substr(pos);
    }();
    if(iequals(ext, ".htm"))  return "text/html";
    if(iequals(ext, ".html")) return "text/html";
    if(iequals(ext, ".php"))  return "text/html";
    if(iequals(ext, ".css"))  return "text/css";
    if(iequals(ext, ".txt"))  return "text/plain";
    if(iequals(ext, ".js"))   return "application/javascript";
    if(iequals(ext, ".json")) return "application/json";
    if(iequals(ext, ".xml"))  return "application/xml";
    if(iequals(ext, ".swf"))  return "application/x-shockwave-flash";
    if(iequals(ext, ".flv"))  return "video/x-flv";
    if(iequals(ext, ".png"))  return "image/png";
    if(iequals(ext, ".jpe"))  return "image/jpeg";
    if(iequals(ext, ".jpeg")) return "image/jpeg";
    if(iequals(ext, ".jpg"))  return "image/jpeg";
    if(iequals(ext, ".gif"))  return "image/gif";
    if(iequals(ext, ".bmp"))  return "image/bmp";
    if(iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
    if(iequals(ext, ".tiff")) return "image/tiff";
    if(iequals(ext, ".tif"))  return "image/tiff";
    if(iequals(ext, ".svg"))  return "image/svg+xml";
    if(iequals(ext, ".svgz")) return "image/svg+xml";
    return "application/text";
}

class http_worker
{
public:
    http_worker(http_worker const&) = delete;
    http_worker& operator=(http_worker const&) = delete;

    http_worker(tcp::acceptor& acceptor, const std::string& doc_root) :
        acceptor_(acceptor),
        doc_root_(doc_root)
    {
    }

    void start()
    {
        accept();
        check_deadline();
    }

private:
    using alloc_t = fields_alloc<char>;
    using request_body_t = http::string_body;
    tcp::acceptor& acceptor_;
    std::string doc_root_;
    tcp::socket socket_{acceptor_.get_executor()};
    beast::flat_static_buffer<8192> buffer_;
    alloc_t alloc_{8192};
    boost::optional<http::request_parser<request_body_t, alloc_t>> parser_;
    net::steady_timer request_deadline_{acceptor_.get_executor(), (std::chrono::steady_clock::time_point::max)()};
    boost::optional<http::response<http::string_body, http::basic_fields<alloc_t>>> string_response_;
    boost::optional<http::response_serializer<http::string_body, http::basic_fields<alloc_t>>> string_serializer_;
    boost::optional<http::response<http::file_body, http::basic_fields<alloc_t>>> file_response_;
    boost::optional<http::response_serializer<http::file_body, http::basic_fields<alloc_t>>> file_serializer_;

    void accept()
    {
        beast::error_code ec;
        socket_.close(ec);
        buffer_.consume(buffer_.size());

        acceptor_.async_accept(
            socket_,
            [this](beast::error_code ec)
            {
                if (ec)
                {
                    accept();
                }
                else
                {
                    request_deadline_.expires_after(
                        std::chrono::seconds(60));

                    read_request();
                }
            });
    }

    void read_request()
    {
        parser_.emplace(
            std::piecewise_construct,
            std::make_tuple(),
            std::make_tuple(alloc_));

        http::async_read(
            socket_,
            buffer_,
            *parser_,
            [this](beast::error_code ec, std::size_t)
            {
                if (ec)
                    accept();
                else
                    process_request(parser_->get());
            });
    }

    void process_request(http::request<request_body_t, http::basic_fields<alloc_t>> const& req)
    {
        std::string target_str = req.target().to_string();
        switch (req.method())
        {
        case http::verb::get:
            if(target_str == "/picture") {
                std::string filename = picture();
                std::cout << "/" + filename.substr(0, filename.size()-1);
                send_file("/" + filename + ".jpg");
            } else if(target_str.substr(0, 6) == "/Faces") {
                try {
                    int n = stoi(
                        target_str.substr(7, target_str.size() - 7)
                        );
                    const char* table = target_str.substr(1, 5).c_str();
                    std::string result_string = returnLastNData(table, n);
                    send_bad_response(http::status::accepted, result_string);
                } catch (const std::exception& e) {
                    send_bad_response(http::status::not_found, "File not found\r\n");
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }else {
                send_bad_response(http::status::not_found, "File not found\r\n");
            }
            break;
        default:
            send_bad_response(
                http::status::bad_request,
                "Invalid request-method '" + std::string(req.method_string()) + "'\r\n");
            break;
        }
    }

    void send_bad_response(
        http::status status,
        std::string const& error)
    {
        string_response_.emplace(
            std::piecewise_construct,
            std::make_tuple(),
            std::make_tuple(alloc_));

        string_response_->result(status);
        string_response_->keep_alive(false);
        string_response_->set(http::field::server, "Beast");
        string_response_->set(http::field::content_type, "text/plain");
        string_response_->body() = error;
        string_response_->prepare_payload();

        string_serializer_.emplace(*string_response_);

        http::async_write(
            socket_,
            *string_serializer_,
            [this](beast::error_code ec, std::size_t)
            {
                socket_.shutdown(tcp::socket::shutdown_send, ec);
                string_serializer_.reset();
                string_response_.reset();
                accept();
            });
    }

    void send_file(beast::string_view target)
    {
        // Request path must be absolute and not contain "..".
        if (target.empty() || target[0] != '/' || target.find("..") != std::string::npos)
        {
            send_bad_response(
                http::status::not_found,
                "File not found\r\n");
            return;
        }

        std::string full_path = doc_root_;
        full_path.append(
            target.data(),
            target.size());

        http::file_body::value_type file;
        beast::error_code ec;
        file.open(
            full_path.c_str(),
            beast::file_mode::read,
            ec);
        if(ec)
        {
            send_bad_response(
                http::status::not_found,
                "File not found\r\n");
            return;
        }

        file_response_.emplace(
            std::piecewise_construct,
            std::make_tuple(),
            std::make_tuple(alloc_));

        file_response_->result(http::status::ok);
        file_response_->keep_alive(false);
        file_response_->set(http::field::server, "Beast");
        file_response_->set(http::field::content_type, mime_type(std::string(target)));
        file_response_->body() = std::move(file);
        file_response_->prepare_payload();

        file_serializer_.emplace(*file_response_);

        http::async_write(
            socket_,
            *file_serializer_,
            [this](beast::error_code ec, std::size_t)
            {
                socket_.shutdown(tcp::socket::shutdown_send, ec);
                file_serializer_.reset();
                file_response_.reset();
                accept();
            });
    }

    void check_deadline()
    {
        // The deadline may have moved, so check it has really passed.
        if (request_deadline_.expiry() <= std::chrono::steady_clock::now())
        {
            // Close socket to cancel any outstanding operation.
            socket_.close();

            // Sleep indefinitely until we're given a new deadline.
            request_deadline_.expires_at(
                (std::chrono::steady_clock::time_point::max)());
        }

        request_deadline_.async_wait(
            [this](beast::error_code)
            {
                check_deadline();
            });
    }
};


int main(int argc, char* argv[])
{

    MySQLConnection = mysql_init( NULL );

    try
    {
        MySQLConRet = mysql_real_connect( MySQLConnection,
                                          "localhost",
                                          "mahdi",
                                          "mahdi",
                                          "Project_DB",
                                          0, 
                                          "/var/run/mysqld/mysqld.sock",
                                          0 );

        if ( MySQLConRet == NULL )
            throw FFError( (char*) mysql_error(MySQLConnection) );
   
        printf("MySQL Connection Info: %s \n", mysql_get_host_info(MySQLConnection));
        printf("MySQL Client Info: %s \n", mysql_get_client_info());
        printf("MySQL Server Info: %s \n", mysql_get_server_info(MySQLConnection));

    }
    catch ( FFError e )
    {
        printf("%s\n",e.Label.c_str());
        return 1;
    }

    // Http Server
    try
    {
        auto const address = net::ip::make_address("0.0.0.0");
        unsigned short port = static_cast<unsigned short>(8089);
        std::string doc_root = ".";
        int num_workers = 100;
        bool spin = (std::strcmp("block", "spin") == 0);

        net::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {address, port}};

        std::list<http_worker> workers;
        for (int i = 0; i < num_workers; ++i)
        {
            workers.emplace_back(acceptor, doc_root);
            workers.back().start();
        }

        if (spin)
          for (;;) ioc.poll();
        else
          ioc.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // MYSQL disconnect
    mysql_close(MySQLConnection);
}




std::string picture() {
    FILE *fp;
    char path[100];
    fp = popen("pidof embedded", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    while (fgets(path, sizeof(path), fp) != NULL) {
        try{
            pid_t pid = std::stoi(path);
            kill(pid, SIGUSR1);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    fp = popen("ls -t1", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    fgets(path, sizeof(path), fp);
    pclose(fp);
    return path;

}


std::string returnLastNData(const char* table, int num) {
    char path[100];
    sprintf(path, "SELECT * from %s ORDER BY ID DESC LIMIT %d", table, num);
    if (mysql_query(MySQLConnection, path) ) {
        printf("Error %u: %s\n", mysql_errno(MySQLConnection), mysql_error(MySQLConnection));
		exit(1);
    }
    MySQLResult = mysql_store_result(MySQLConnection);
    std::string result_string = "";
    std::string converted_result = "";

    int num_fields = mysql_num_fields(MySQLResult);
    while ((row = mysql_fetch_row(MySQLResult)))
    {
        std::string Row;
        for(int i = 0; i < num_fields; i++) {
            if(row[i] != NULL)
                Row = Row + row[i] + " ";
        }
        result_string = result_string + Row + "\n";
    }
    

    if(result_string == "") {
        return "No result\r\n";
    }
    return result_string;
}










