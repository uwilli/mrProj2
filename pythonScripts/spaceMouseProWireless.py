#!/usr/bin/python3
"""
This script reads the data from the 3d connexion Spacemouse Pro Wireless and prints them to the console.
Currently only single button presses are considered. The information available would allow concurrent and nested pushes
to be recognized.

Sources used:
From jwick1234, github. Link: https://github.com/uwilli/3d-mouse-rpi-python/blob/develop/HelloSpaceNavigator.py
From johnhw, github. Space Mouse Wireless Windows: https://github.com/johnhw/pyspacenavigator/blob/master/spacenavigator.py

Changed and blended and marinated by Urban Willi
"""

import usb.core
import usb.util
import time

######################################################################################################
# Class
######################################################################################################

class Spacemouse:
    def __init__(self):
        ## Instance variables
        self.x = None
        self.y = None
        self.z = None
        self.roll = None
        self.pitch = None
        self.yaw = None

        self.escape = None
        self.b1 = None
        self.b2 = None
        self.b3 = None
        self.b4 = None
        self.lockRotation = None

        self.dev = None

        ## Init
        # Look for Space Mouse
        self.dev = usb.core.find(idVendor=0x256f, idProduct=0xc652)  # use usbFindVendorProductID.py
        if self.dev is None:
            raise ValueError('Spacemouse not found');
        else:
            print('Spacemouse Pro Wireless found')

        # dev.set_configuration() # Apparently automatically chosen config, as this throws an error.

        # Deal with Error resource-busy
        if self.dev.is_kernel_driver_active(0):
            try:
                self.dev.detach_kernel_driver(0)
            except usb.core.USBError as e:
                sys.exit("Could not detach kernel driver from interface 0")

    def __del__(self):
        usb.util.dispose_resources(self.dev) # free usb device

    # Spacemouse talks via receiver over Usb, using interrupt msgs.
    # Timeout for waiting on interrupt, in s. (Milliseconds recommended).
    # Single button presses and following release recognized. Simultaneous several buttons not yet supported.
    def getInterruptMsg(self):
        usbInt = self.dev.read(0x81, 0x20, 10)  # endpoint address, msg length -> wMaxPacketSize, timeout (optional, device default if not set)

        msgType = usbInt[0]

        released = True  # if buttons released/Joystick not touched, msg is all zeros except msg type
        for item in usbInt[1:]:
            if item != 0:
                released = False
                break

        if msgType == 1: # Joystick
            if released:
                self.x = None
                self.y = None
                self.z = None
                self.roll = None
                self.pitch = None
                self.yaw = None
                print('Joystick released')
                return

            print('Joystick')

            self.x = self.__to_int16(self.__tryIndexAbsVal(usbInt, 1), self.__tryIndexAbsVal(usbInt, 2))
            self.y = -1 * self.__to_int16(self.__tryIndexAbsVal(usbInt, 3), self.__tryIndexAbsVal(usbInt, 4))
            self.z = -1 * self.__to_int16(self.__tryIndexAbsVal(usbInt, 5), self.__tryIndexAbsVal(usbInt, 6))
            self.pitch = -1 * self.__to_int16(self.__tryIndexAbsVal(usbInt, 7), self.__tryIndexAbsVal(usbInt, 8))
            self.roll = -1 * self.__to_int16(self.__tryIndexAbsVal(usbInt, 9), self.__tryIndexAbsVal(usbInt, 10))
            self.yaw = -1 * self.__to_int16(self.__tryIndexAbsVal(usbInt, 11), self.__tryIndexAbsVal(usbInt, 12))

            # print('x     : ', self.x)
            # print('y     : ', self.y)
            # print('z     : ', self.z)
            # print('pitch  : ', self.pitch)
            # print('roll : ', self.roll)
            # print('yaw   : ', self.yaw)

        elif msgType == 3:
            if released:
                self.escape = None
                self.b1 = None
                self.b2 = None
                self.b3 = None
                self.b4 = None
                self.lockRotation = None
                print('Button released')
                return
            # print('Button')

            # Position 1
            val = self.__tryIndexAbsVal(usbInt, 1)
            if val == 1:
                print('Menu')
            elif val == 2:
                print('Fit')
            elif val == 4:
                print('Top')
            elif val == 16:
                print('Right')
            elif val == 32:
                print('Front')

            # Position 2
            val = self.__tryIndexAbsVal(usbInt, 2)
            if val == 1:
                print('Roll View')
            elif val == 16:
                self.b1 = True
                #print('B1')
            elif val == 32:
                self.b2 = True
                #print('B2')
            elif val == 64:
                self.b3 = True
                #print('B3')
            elif val == 128:
                self.b4 = True
                #print('B4')

            # Position 3
            val = self.__tryIndexAbsVal(usbInt, 3)
            if val == -1:  # out of range
                return

            if val == 64:
                #print('Escape')
                self.escape = True
            elif val == 128:
                print('Alt')

            # Position 4
            val = self.__tryIndexAbsVal(usbInt, 4)
            if val == -1:  # out of range
                return

            if val == 1:
                print('Shift')
            elif val == 2:
                print('Ctrl')
            elif val == 4:
                self.lockRotation = True
                #print('Lock Rotation')

        elif msgType == 23:
            # print('inactivity?')
            pass
        else:
            print('unknown')

        # enumerate
        # for i, item in enumerate(usbInt):
        #     print(item)


    # returns None if index out of range
    def __tryIndexTwosComp(self, list, index):
        ret = None
        try:
            absVal = list[index]
        except ValueError:
            return ret

        if absVal > 127: # two's complement
            ret = ~absVal & 1
        else:
            ret = absVal
        return ret


    # returns -1 if index out of range
    def __tryIndexAbsVal(self, list, index):
        try:
            ret = list[index]
        except ValueError:
            return -1
        return ret

    # convert two 8 bit bytes to a signed 16 bit integer
    # from johnhw
    def __to_int16(self, y1, y2):
        x = (y1) | (y2 << 8)
        if x >= 32768:
            x = -(65536 - x)
        return x



######################################################################################################
# Main
######################################################################################################

if __name__ == "__main__":

    controller = Spacemouse()

    # FOR LATER, in the moment only single button presses reliable
    # Remember if button pressed or released, starting with all released.
    # Order: Menu, Fit, Top, Right, Front, Roll View, B1, B2, B3, B4,  Escape, Alt, Shift, Ctrl, Lock Rotation
    # ButtonStates = [False, False, False, False, False, False, False, False, False, False, False, False, False, False, False]


    # Loop, this usb device works with interrupt communication
    run = True
    sleepPeriod = 0.01

    while run:
        try:
            controller.getInterruptMsg()
            if controller.escape:
                run = False

        except usb.core.USBError as er:
            if er.errno == 110: # Timeout
                pass

        # Should print none with no movement
        print('x     : ', controller.x)
        print('y     : ', controller.y)
        print('z     : ', controller.z)
        print('roll  : ', controller.roll)
        print('pitch : ', controller.pitch)
        print('yaw   : ', controller.yaw)

        print('B1     : ', controller.b1)
        print('B2     : ', controller.b2)
        print('B3     : ', controller.b3)
        print('B4     : ', controller.b4)
        print('LockRot: ', controller.lockRotation)

        time.sleep(sleepPeriod)
    # end while
