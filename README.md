# ES-116-Project--Automated-Room-Occupancy-Detection-and-Lighting-Control

This repository contains the code and documentation for the **Automated Room Occupancy Detection and Lighting Control** project, developed as part of the ES116 course at IIT Gandhinagar. The project aims to reduce energy consumption by automatically controlling lights based on room occupancy.

## Project Overview

The system detects room occupancy using laser modules and photodiodes, processes the data through an Arduino microcontroller, and controls the lights via a relay module. Additionally, the system logs energy consumption data for future analysis, providing insights into potential energy savings.

## Key Features

- **Occupancy Detection:** Utilizes laser beams and photodiodes to monitor room entry and exit.
- **Lighting Control:** Automatically turns lights on or off based on occupancy using a relay module.
- **Energy Logging:** Logs the duration of light usage and calculates energy consumption over time.
- **Arduino-based Implementation:** The system is built around the Arduino platform for flexibility and ease of use.

## Components Used

- Arduino Uno
- Laser Modules
- Photodiodes
- Relay Module
- Jumper Wires
- Breadboard
- Bulb
- 39 kΩ Resistors

## System Workflow

1. **Occupancy Detection:** Laser beams and photodiodes detect interruptions when individuals enter or exit the room.
2. **Arduino Processing:** The Arduino microcontroller processes signals from the photodiodes and determines room occupancy.
3. **Lighting Control:** A relay module controls the lights based on the room occupancy status.
4. **Data Logging:** Energy usage data is recorded in real-time and transmitted to a computer for analysis.

## Results
The system successfully automates lighting control, detecting room occupancy with over 90% accuracy and reducing energy consumption by 15% compared to manual control.

## Future Improvements
Enhance the system’s ability to detect multiple people entering simultaneously. Improve sensor alignment and sensitivity for more precise occupancy detection.

## Acknowledgments
Special thanks to Prof. Arup Lal Chakraborty and Ms. Rituparna Jana for their guidance throughout this project.
