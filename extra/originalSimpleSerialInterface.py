import serial

try:
    arduinoData = serial.Serial('com8',9600)
except:
    print("Check the port connection, no signal is being recived");
    

while(True):    
    myDatax = (arduinoData.readline().strip())
    myDatay = (arduinoData.readline().strip())
    myDataz = (arduinoData.readline().strip())
    print(myDatax.decode('utf-8'))
    print(myDatay.decode('utf-8'))
    print(myDataz.decode('utf-8'))
