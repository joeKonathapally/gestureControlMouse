import time
import psutil
import matplotlib.pyplot as plt
import numpy as np
import serial
from decimal import Decimal
import pyautogui as auto


##rate is in seconds, so how many seconds to move it
def moveBy(x, y, rate):
    ##x and y is the current position of the mouse this needs to be in a loop otherwise it wont update :(
    mousex,mousey = auto.position()

    auto.moveTo(mousex+x, mousey-y, rate, auto.easeInQuad)



try:
    arduinoData = serial.Serial('com8',9600)
except:
    print("Check the port connection, no signal is being recived")


while True:

    myData = arduinoData.readline().decode('utf-8').strip()
    print(myData)
    if(myData=="UP"):
        moveBy(0,15,0.25)
        

        
    if (myData=="DOWN"):
        moveBy(0,-15,0.25)

        
    if (myData=="LEFT"):
        moveBy(-15,0,0.25)

        
    if (myData=="RIGHT"):
        moveBy(15,0,0.25)

    if (myData=="RIGHT-CLICK"):
        auto.click(button='right')


    if (myData=="LEFT-CLICK"):
        auto.click(button='left')
        
    

    

plt.close()

