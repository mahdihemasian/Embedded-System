import http.server
import socketserver
import urllib.parse
import json
from http.server import BaseHTTPRequestHandler, HTTPServer

import RPi.GPIO as GPIO
import time

PORT = 9000

states = [False, False, False]

LED_PINs = [17, 18, 23]

GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PINs[0], GPIO.OUT)
GPIO.setup(LED_PINs[1], GPIO.OUT)
GPIO.setup(LED_PINs[2], GPIO.OUT)


class MyHandler(BaseHTTPRequestHandler):

    def set_Led(self):
        for i in range(3):
            if states[i]:
                GPIO.output(LED_PINs[i], GPIO.HIGH)
            else:
                GPIO.output(LED_PINs[i], GPIO.LOW)
        time.sleep(0.02)

    def do_GET(self):
        if self.path == '/':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            # Bootstrap HTML page with 3 buttons and 3 states
            html = '''
            <html>
            <head>
            <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css">
            <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js"></script>
            <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js"></script>
            <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"></script>
            <style>
            body {
                background-color: #f8f9fa;
            }
            .container {
                margin-top: 50px;
            }
            .badge {
                font-size: 1.2rem;
                padding: 6px;
                margin-bottom: 4px;
            }
            .badge-success {
                background-color: #28a745;
            }
            .badge-danger {
                background-color: #dc3545;
            }
            </style>
            <script>
            function clicked(button) {
                fetch('/', {
                    method: 'POST',
                    body: JSON.stringify({ button: button }),
                    headers: { 'Content-Type': 'application/json' }
                }).then(response => {
                    if (response.ok) {
                        return response.json();
                    } else {
                        throw new Error('Error updating state');
                    }
                }).then(data => {
                    // Update the state of the clicked button
                    var stateEl = document.getElementById('state-' + button);
                    stateEl.innerHTML = data.state;
                    stateEl.className = 'badge badge-' + (data.state ? 'success' : 'danger');
                }).catch(error => {
                    console.error(error);
                });
            }
            </script>
            </head>
            <body>
            <div class="container">
            <h1 class="text-center mb-5">GPIO in Raspberry Pi 4</h1>
            <div class="row justify-content-center">
            <div class="col mb-3">
            <button type="button" class="btn btn-primary btn-lg btn-block" onclick="clicked(0)">Pin17</button>
            <p class="text-center">State: <span id="state-0" class="badge badge-''' + ('success' if states[0] else 'danger') + '''">''' + str(states[0]) + '''</span></p>
            </div>
            <div class="col mb-3">
            <button type="button" class="btn btn-primary btn-lg btn-block" onclick="clicked(1)">Pin18</button>
            <p class="text-center">State: <span id="state-1" class="badge badge-''' + ('success' if states[1] else 'danger') + '''">''' + str(states[1]) + '''</span></p>
            </div>
            <div class="col mb-3">
            <button type="button" class="btn btn-primary btn-lg btn-block" onclick="clicked(2)">Pin23</button>
            <p class="text-center">State: <span id="state-2" class="badge badge-''' + ('success' if states[2] else 'danger') + '''">''' + str(states[2]) + '''</span></p>
            </div>
            </div>
            </div>
            </body>
            </html>
            '''
            self.wfile.write(html.encode())
        else:
            # Serve files from the local directory
            parsed_path = urllib.parse.urlparse(self.path)
            real_path = parsed_path.path.strip('/')
            self.path = real_path
            return http.server.SimpleHTTPRequestHandler.do_GET(self)
      

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        data = json.loads(post_data.decode())
        button = data['button']
        states[button] = not states[button]
        self.send_response(200)
        self.send_header('Content-type', 'application/json')
        self.end_headers()
        response = {'success': True, 'state': states[button]}
        self.wfile.write(json.dumps(response).encode())
        self.set_Led()



myServer = HTTPServer(("localhost", PORT), MyHandler)
print("Server started on port", PORT)
myServer.serve_forever()

