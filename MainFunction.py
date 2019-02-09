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

    auto.moveTo(mousex+x, mousey+y, rate, auto.easeInQuad)







fig = plt.figure()
ax = fig.add_subplot(111)
fig.show()
ax.set_ylim([-400,400])


try:
    arduinoData = serial.Serial('com8',9600)
except:
    print("Check the port connection, no signal is being recived")
    



i = 0 
timey, x, y, z = [], [], [], []





while True:

    myData = arduinoData.readline().decode('utf-8').split(';')
    

    if(len(timey)>50):
        timey, x, y, z = [], [], [], []
        i=0
        plt.close()
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.set_ylim([-400,400])
        fig.show()

        
        
    x.append(float(myData[0]))
    y.append(float(myData[1]))
    z.append(float(myData[2]))
    timey.append(float(i))
    
    
    ax.plot(timey, x, color='g')
    ax.plot(timey, y, color='b')
    ax.plot(timey, z, color='r')
    fig.canvas.draw()
    ##ax.set_xlim(left=max(0, i-50), right=i+50)


    
    time.sleep(0.2)
    i += 1

plt.close()
