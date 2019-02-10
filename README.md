# gestureControlMouse
hackathon
The main objective of our project is 2-fold:- it tracks predefined hand movements using an Arduino and converts them into  a signal for 
a python script to control the movement of the mouse cursor in all planes. It allows you to take specific signals and define new scripts for the new functions.
There are 2 main files:
- To setup the ArduinoAccelerometer file, you need to connect Arduino to the Computer and ensure all repositories are installed. then check which port is used for output, by looking at the config values of the arduino.
NOTE: The development of this project was done using Arduino 101. Therefore change arduino IDE rendering to reflect the defult specifications of the arduino board.
- To setup the Python file MainFunction.py; you need to ensure all libraries are imported and that you pass the value of the port that the Arduino is outputting to the Python script.
NOTE: e.g. "arduinoData = serial.Serial('com10',9600)" will update the value of com10 with your associated output port from the Arduino.


1 of them tracks the signals via python of the arduino to the serial bus. 

