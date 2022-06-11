#!/usr/bin/python3
"""
Sources used:
From jwick1234, github. Link: https://github.com/uwilli/3d-mouse-rpi-python/blob/develop/HelloSpaceNavigator.py
From johnhw, github. Space Mouse Wireless Windows: https://github.com/johnhw/pyspacenavigator/blob/master/spacenavigator.py

Changed and blended and marinated by Urban Willi
"""

import usb.core
import usb.util
import time

######################################################################################################
# Functions
######################################################################################################

# returns None if index out of range
def tryIndexTwosComp(list, index):
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
def tryIndexAbsVal(list, index):
    try:
        ret = list[index]
    except ValueError:
        return -1
    return ret

# convert two 8 bit bytes to a signed 16 bit integer
# from johnhw
def to_int16(y1, y2):
    x = (y1) | (y2 << 8)
    if x >= 32768:
        x = -(65536 - x)
    return x


######################################################################################################
# Main
######################################################################################################

if __name__ == "__main__":
    # Look for Space Mouse
    dev = usb.core.find(idVendor=0x256f, idProduct=0xc652) # use usbFindVendorProductID.py
    if dev is None:
        raise ValueError('Spacemouse not found');
    else:
        print('Spacemouse Pro Wireless found')

    #dev.set_configuration() # Apparently automatically chosen config, as this throws an error.

    # Deal with Error resource-busy
    if dev.is_kernel_driver_active(0):
        try:
            dev.detach_kernel_driver(0)
        except usb.core.USBError as e:
            sys.exit("Could not detach kernel driver from interface 0")

    # FOR LATER, in the moment only single button presses reliable
    # Remember if button pressed or released, starting with all released.
    # Order: Menu, Fit, Top, Right, Front, Roll View, B1, B2, B3, B4,  Escape, Alt, Shift, Ctrl, Lock Rotation
    ButtonStates = [False, False, False, False, False, False, False, False, False, False, False, False, False, False, False]


    # Loop, this usb device works with interrupt communication
    run = True
    sleepPeriod = 0.01

    while run:
        try:
            usbInt = dev.read(0x81, 0x20, 10) # endpoint address, msg length -> wMaxPacketSize, timeout (optional, device default if not set)

            msgType = usbInt[0]

            released = True # if buttons released/Joystick not touched, msg is all zeros except msg type
            for item in usbInt[1:]:
                if item != 0:
                    released = False
                    break

            if msgType == 1:
                if released:
                    print('Joystick released')
                    time.sleep(sleepPeriod)
                    continue
                print('Joystick')

                x = to_int16(tryIndexAbsVal(usbInt, 1), tryIndexAbsVal(usbInt, 2))
                y = -1*to_int16(tryIndexAbsVal(usbInt, 3), tryIndexAbsVal(usbInt, 4))
                z = -1 * to_int16(tryIndexAbsVal(usbInt, 5), tryIndexAbsVal(usbInt, 6))
                pitch = -1 * to_int16(tryIndexAbsVal(usbInt, 7), tryIndexAbsVal(usbInt, 8))
                roll = -1 * to_int16(tryIndexAbsVal(usbInt, 9), tryIndexAbsVal(usbInt, 10))
                yaw = -1 * to_int16(tryIndexAbsVal(usbInt, 11), tryIndexAbsVal(usbInt, 12))
                print('x     : ', x)
                print('y     : ', y)
                print('z     : ', z)
                print('pitch  : ', pitch)
                print('roll : ', roll)
                print('yaw   : ', yaw)

            elif msgType == 3:
                if released:
                    print('Button released')
                    time.sleep(sleepPeriod)
                    continue
                #print('Button')

                # Position 1
                val = tryIndexAbsVal(usbInt, 1)
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
                val = tryIndexAbsVal(usbInt, 2)
                if val == 1:
                    print('Roll View')
                elif val == 16:
                    print('B1')
                elif val == 32:
                    print('B2')
                elif val == 64:
                    print('B3')
                elif val == 128:
                    print('B4')

                # Position 3
                val = tryIndexAbsVal(usbInt, 3)
                if val == -1: # out of range
                    time.sleep(sleepPeriod)
                    continue

                if val == 64:
                    print('Escape')
                    run = False
                elif val == 128:
                    print('Alt')

                # Position 4
                val = tryIndexAbsVal(usbInt, 4)
                if val == -1:  # out of range
                    time.sleep(sleepPeriod)
                    continue

                if val == 1:
                    print('Shift')
                elif val == 2:
                    print('Ctrl')
                elif val == 4:
                    print('Lock Rotation')

            elif msgType == 23:
                #print('inactivity?')
                pass
            else:
                print('unknown')

            # enumerate
            # for i, item in enumerate(usbInt):
            #     print(item)

        except usb.core.USBError as er:
            if er.errno == 110: # Timeout
                pass

        time.sleep(sleepPeriod)

    # end while
    usb.util.dispose_resources(dev)