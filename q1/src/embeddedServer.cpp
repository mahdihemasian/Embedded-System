#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <cstring>
#include <stdio.h>
#include <ctime>
#include <fstream>
#include <mosquitto.h>
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "MQTTClient.h"
#include <ctime>
#include <mysql/mysql.h>
#include <signal.h>
#include <alsa/asoundlib.h>
#include <math.h>

using namespace cv;
using namespace std;


#define ADDRESS     "localhost"
#define CLIENTID    "Mahdi-Sender"

static int counter=0;


void finish_with_error(MYSQL *con);

void publish(MQTTClient client, char* topic, char* payload); 

int on_message(void *context, char *topicName, int topicLen, MQTTClient_message *message); 

int detectAndDisplay(Mat frame );

void handleSignalTakePhoto(int sig);



CascadeClassifier face_cascade;
Mat frame;
time_t now;
char* dt;

static char *device = "default";
short buffer[8*1024];
int buffer_size = sizeof(buffer)>>1;


int main( )
{
	//openCV Settings-
	face_cascade.load("/home/mahdi/mahdi/opencv/data/haarcascades/haarcascade_frontalface_alt.xml");
    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    if( !face_cascade.load( "/home/mahdi/mahdi/opencv/data/haarcascades/haarcascade_frontalface_alt.xml" ) )
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    }


	//Mosquitto Settings
	MQTTClient client;
    MQTTClient_create(&client, ADDRESS, CLIENTID, 		MQTTCLIENT_PERSISTENCE_NONE, NULL);
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.username = "mahdi";
    conn_opts.password = "mahdi";
	MQTTClient_setCallbacks(client, NULL, NULL, on_message, NULL);
    int rc;
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
   



	//MySQL Settings
	MYSQL *con = mysql_init(NULL);
	if (con == NULL){
   		fprintf(stderr, "%s\n", mysql_error(con));
    	exit(1);
   	}
  	if (mysql_real_connect(con, "localhost", "mahdi", "mahdi",
  		  					"Project_DB", 0, "/var/run/mysqld/mysqld.sock", 0) == NULL){
    	finish_with_error(con);
  	}


	
	//define signal handler
	signal( SIGUSR1, handleSignalTakePhoto);
	//global needed variables
	char buff[200];
	FILE *fp;
  	char command[1100];
	//face publish variables
	int prev_face_num = 0;
	int curr_face_num = 0;
	string pub_nums_face; 
	string pub_date_face; 
	string pub_send_face;
	char data_face[250];
	
	//infinite loop
	for(;;)	
	{
		//face processing and store
		camera >> frame;
		prev_face_num = curr_face_num;
		curr_face_num = detectAndDisplay(frame);
		if (prev_face_num != curr_face_num)
		{
			now = time(0);
			dt = ctime(&now);
			
			cout << "FACE deteced:  " << curr_face_num << "\t" << dt << "\n";

			sprintf(buff, "INSERT INTO Faces (numbers, date) VALUES('%d', '%s')", curr_face_num, dt);

			if (mysql_query(con, buff)) {
      			finish_with_error(con);
 			}

			pub_nums_face =  (to_string(curr_face_num).c_str()); 
			pub_date_face =  dt; 
			pub_send_face = pub_nums_face + "\t" + pub_date_face;
			strcpy(data_face, pub_send_face.c_str());
			publish(client, "Faces", data_face);
		}

	}

	MQTTClient_disconnect(client, 1000);
    MQTTClient_destroy(&client);
	mysql_close(con);
    return 0;
}



int detectAndDisplay(Mat frame)
{
    Mat frame_gray;
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces);

   
    return faces.size();
}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}


void publish(MQTTClient client, char* topic, char* payload) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = payload; 
	pubmsg.payloadlen = strlen((char *)pubmsg.payload);
    pubmsg.qos = 2;
    pubmsg.retained = 0;
    MQTTClient_deliveryToken token;
    MQTTClient_publishMessage(client, topic, &pubmsg, &token);
    MQTTClient_waitForCompletion(client, token, 1000L);
}

int on_message(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    char* payload = (char *) message->payload;   
    counter++;
    printf("%d)Received operation %s\n", counter, payload);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void handleSignalTakePhoto(int sig) {  
    Mat frame_gray;
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces);
    // Draw a rectangle and write a string for each detected face
    for (size_t i = 0; i < faces.size(); i++)
    {
        Point pt1(faces[i].x, faces[i].y);
        Point pt2(faces[i].x + faces[i].width, faces[i].y + faces[i].height);

        rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2);

        std::ostringstream oss;
        oss << "Face " << i+1;
        String text = oss.str();

        int fontFace = FONT_HERSHEY_SIMPLEX;
        double fontScale = 1;
        int thickness = 2;
        int baseline=0;
        Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);

        Point textOrg(faces[i].x, faces[i].y - 10);
        putText(frame, text, textOrg, fontFace, fontScale, Scalar(0, 0, 255), thickness);
    }
     // Write a string on the frame
    std::ostringstream oss;
    oss << "FACE:" << faces.size() << ", " << dt;
    String text = oss.str();
    int fontFace = FONT_HERSHEY_SIMPLEX;
    double fontScale = 1;
    int thickness = 2;
    int baseline=0;
    Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
    putText(frame, text, Point(20, 40), fontFace, fontScale, Scalar(0, 0, 0), thickness);
    std::string str1 = "/home/mahdi/mahdi/bin/";
    std::string str2 = dt;
    std::string str3 = ".jpg";
    std::string concatenated = str1 + str2 + str3;
	imwrite(concatenated, frame);
}





