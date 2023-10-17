# Face Detection and Recognition Web Server(q1)

This project implements a web server that streams video input from a webcam or video source and performs real-time face detection. The detected faces are framed, and the corresponding person's ID is displayed beside each face. The system also displays the current system time and the number of recognized faces in the corner of the image.

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Installation](#installation)

## Project Overview

The Face Detection and Recognition Web Server project aims to provide real-time face detection capabilities by utilizing pre-trained models such as the Haar Cascade classifier. The system streams video input from a webcam or video source, detects faces in each frame, and draws bounding boxes around the detected faces. Additionally, it displays the assigned person's ID beside each face. The system also records the system time and the number of recognized faces whenever the detected faces change and stores this information in a database.

## Features

- Real-time face detection: Utilizes pre-trained models like Haar Cascade classifier for efficient and accurate face detection.
- Face framing and person ID display: Draws bounding boxes around detected faces and displays the assigned person's ID.
- System time and face count display: Shows the current system time and the number of recognized faces in the corner of the image.
- Database integration: Stores the system time and the number of recognized faces in a database whenever there is a change in the detected faces.
- MQTT integration: Publishes the face change event to an appropriate MQTT topic for subscribers to receive notifications.
- HTTP web server: Provides an HTTP API for users to submit and retrieve image data.

## Installation

1. Clone the repository
2. Run embedded server c code


# Video Streaming and Audio Analysis Server(q2)

This project implements a server that streams video using the GStreamer library with the HLS (HTTP Live Streaming) standard. The video is streamed from one server and displayed on another server. Users can view the streamed data through a web browser on the second server. The project also includes audio analysis functionality using the SOX tool. The server captures audio from a microphone and saves it based on a user-defined threshold. The result of the audio analysis is displayed in a web browser using an HTML page.

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Installation](#installation)

## Project Overview

The Video Streaming and Audio Analysis Server project aims to provide video streaming capabilities using the GStreamer library with the HLS standard. It enables streaming video from one server and displaying it on another server, allowing users to view the streamed data through a web browser. Additionally, the project incorporates audio analysis functionality using the SOX tool. The server captures audio from a microphone, saves it based on a user-defined threshold, and displays the result of the audio analysis in a web browser.

## Features

- Video streaming with GStreamer: Utilizes the GStreamer library to stream video using the HLS standard.
- Audio capture and analysis: Uses the SOX tool to capture audio from a microphone and perform analysis based on a user-defined threshold.
- HTML interface: Provides a shared interface, implemented with Flask or a simple HTML server, for interacting with the video streaming and audio analysis components.
- User input and interaction: Accepts user inputs and interactions through the HTML interface for configuring the streaming and audio analysis functionalities.

## Installation

1. Clone the repository
2. Run embedded server c code
