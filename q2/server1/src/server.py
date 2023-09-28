from flask import Flask, send_from_directory
from flask import redirect, request
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

in_name = None

def gen_page():
    page = """
    <html>
        <head>
            <title>  Flask  </title>
        </head>
        <body>
            <h1> Welcome</h1>
            <p> Hello </p>
        </body>
    </html>
    """
    return page

@app.route('/')
def hello():
    return gen_page()

@app.route('/GStreamer/<path:path>')
def get_file(path):
    print(path)
    print('salam')
    print(send_from_directory('GStreamer', path))
    return send_from_directory('GStreamer', path)

@app.route('/send_request', methods=['POST'])
def send_request():
    url = request.form['url']
    data = request.form['data']
    headers = {'Content-Type': 'application/json'}
    response = request.post(url, data=data, headers=headers)
    return response.text

if __name__ == '__main__':
    app.run() 
