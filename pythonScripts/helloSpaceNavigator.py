#!/usr/bin/python3
"""From jwick1234, github. Link: https://github.com/uwilli/3d-mouse-rpi-python/blob/develop/HelloSpaceNavigator.py"""
"""Space Mouse Wireless Windows: https://github.com/johnhw/pyspacenavigator/blob/master/spacenavigator.py"""
"""Changed and blended and marinated by Urban Willi"""

# See http://stackoverflow.com/questions/29345325/raspberry-pyusb-gets-resource-busy#29347455
# Run python2 as root (sudo /usr/bin/python2.7 /home/pi/pythondev/HelloSpaceNavigator.py)
import usb.core
import usb.util
import sys
from time import gmtime, strftime
import time

# Look for Space Mouse
dev = usb.core.find(idVendor=0x256f, idProduct=0xc652)
if dev is None:
    raise ValueError('Spacemouse not found');
else:
    print('Spacemouse found')

#dev.set_configuration() # Apparently automatically chosen config, as this throws an error.

# Try to get interrupt Communication to work
it = 0
while True:
    try:
        ret = dev.read(0x81, 0x20, 100) # endpoint address, msg length -> wMaxPacketSize, timeout (optional, device default if not set)
        print('return message is: ', ret, '   ', it)
    except:
        pass
    it = it+1
    time.sleep(0.01)

## TODO: Possibility to exit loop!


cfg = dev.get_active_configuration()
print
'cfg is ', cfg
intf = cfg[(0, 0)]
print('intf is ', intf)
ep = usb.util.find_descriptor(intf, custom_match=lambda e: usb.util.endpoint_direction(
    e.bEndpointAddress) == usb.util.ENDPOINT_IN)
print('ep is ', ep)

reattach = False
if dev.is_kernel_driver_active(0):
    reattach = True
    dev.detach_kernel_driver(0)

ep_in = dev[0][(0, 0)][0]
ep_out = dev[0][(0, 0)][1]

print
''
print
'Exit by pressing any button on the SpaceNavigator'
print
''

run = True
while run:
    try:
        data = dev.read(ep_in.bEndpointAddress, ep_in.bLength, 0)
        # raw data
        # print data

        # print it correctly T: x,y,z R: x,y,z
        if data[0] == 1:
            # translation packet
            tx = data[1] + (data[2] * 256)
            ty = data[3] + (data[4] * 256)
            tz = data[5] + (data[6] * 256)

            if data[2] > 127:
                tx -= 65536
            if data[4] > 127:
                ty -= 65536
            if data[6] > 127:
                tz -= 65536
            print
            "T: ", tx, ty, tz

        if data[0] == 2:
            # rotation packet
            rx = data[1] + (data[2] * 256)
            ry = data[3] + (data[4] * 256)
            rz = data[5] + (data[6] * 256)

            if data[2] > 127:
                rx -= 65536
            if data[4] > 127:
                ry -= 65536
            if data[6] > 127:
                rz -= 65536
            print
            "R: ", rx, ry, rz

        if data[0] == 3 and data[1] == 0:
            # button packet - exit on the release
            run = False

    except usb.core.USBError:
        print("USB error")
    except:
        print("read failed")
# end while
usb.util.dispose_resources(dev)

if reattach:
    dev.attach_kernel_driver(0)