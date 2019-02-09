import pyautogui as auto


##rate is in seconds, so how many seconds to move it
def moveBy(x, y, rate):
    ##x and y is the current position of the mouse this needs to be in a loop otherwise it wont update :(
    mousex,mousey = auto.position()

    auto.moveTo(mousex+x, mousey+y, rate, auto.easeInQuad)


    
