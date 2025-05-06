# Marvin - Autonomous Robot with Lidar and Obstacle Avoidance

## Overview

![Marvin Preview]([Marvin/pixel.jpg])

Marvin is an autonomous robot designed to navigate using Lidar and ultrasonic sensors.It performs obstacle detection and avoidance using Arduino and Python. The robot uses an **RPLidar** sensor for mapping its environment and ultrasonic sensors for detecting obstacles.

The **Lidar sensor** emits ultraviolet (UV) rays in all directions, which then hit obstacles in the robot's path. These rays travel back to the sensor, and Marvin calculates the distance to the obstacle based on the time it takes for the rays to return. This allows Marvin to map its surroundings and make navigation decisions, like moving forward, turning left, or turning right, depending on the detected obstacles.

The movement is controlled based on sensor readings and real-time data processing.

## Features
- **Lidar-based environment scanning** for autonomous navigation.
- **Obstacle detection** using ultrasonic sensors.
- **Real-time data visualization** of Lidar readings.
- **Movement control** based on obstacle detection (forward, left, right, stop).
- Simple yet effective **Python-Arduino interaction** for seamless control.
