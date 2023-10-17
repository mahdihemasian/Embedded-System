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
