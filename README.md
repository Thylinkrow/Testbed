# Testbed v1.0

## Authors:
- Loïc Caille
- Arthur Pisiaux

## Project:
This project aims to make testbed to test multiple kinds of engines. It uses a 3D printed structure along with a flywheel (for power mesurment) and some electronics
![](https://i.imgur.com/aUb6ZGq.png)



## Features:
### User Interface
The user interface allows you to use the testbed without the need of a computer nearby. It offers 4 Menus that you can control using the 3 buttons (from left to right: enter - left - right)
- Record: Launches a new record that you can exit by pressing the enter button
- On Input *(not yet implemented)*: Launches the record once 3 rotations have been detected
- Configuation: Access the configuration menu
- Clear: Resets the testbed to "factory" settings

### Data Logging
Using an SD Card module the testbed can record the rpm and pressure of your test (in files named power_X.csv or speed_X.csv depending on the reading mode).
The maximum readings of each session lies at the end of these files.

### Configuration
The configuration menu allows to change the following settings:
| Parameter        | Description                           | Default | Min   | Max   |
|------------------|---------------------------------------|---------|-------|-------|
| Read Time (ms)   | The time between each sensor readings | 250     | 20    | 1000  |
| Number of Blades | The number of blades on the fan       | 4       | 1     | 16    |
| Read Mode        | Which sensor is to be used            | Power   | Power | Speed |

Once modified the parameter are stored within the ESP32 even when powered off.

## Equipment (Electornics only)
Here is the list of the electronics used for this project:
| Name            | Quantity | Required | Additional Info        |
|-----------------|----------|----------|------------------------|
| ESP32           | 1        | Yes      |                        |
| IR Speed Sensor | 2        | Yes      |                        |
| Push-Button     | 3        | Yes      |                        |
| 10k Resistors   | 5        | Yes      |                        |
| OLED Screen     | 1        | Yes      | SH-S130                |
| SD Card Module  | 1        | No       | (Required for logging) |
| Pressure Sensor | 1        | No       | 500psi                 |

![](https://i.imgur.com/QGyZgbr.jpg)

## Electronic schemes
### Main Board
![](https://i.imgur.com/BWAXsbA.jpg)

### Buttons Board
![](https://i.imgur.com/a0bc3YB.jpg)
