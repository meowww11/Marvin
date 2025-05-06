\#from adafruit\_rplidar import RPLidar
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import threading
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from rplidar import RPLidar
import serial
from threading import Thread

startAngle = 45
endAngle = 315
dangerDistance = 700
radius = 2500
length = 360 \* 4

direction=1

s = serial.Serial('COM9', baudrate=115200, bytesize=8,
parity='N',
stopbits=1, timeout=None, xonxoff=False,
rtscts=False)

PORT\_NAME = "COM6"
lidar = RPLidar(PORT\_NAME)

scan\_data\_x = \[0] \* length
scan\_data\_y = \[0] \* length
scan\_data\_r = \[0] \* length
scan\_data\_theta = \[0] \* length

message = "forward"

theta = np.linspace( 0, 2 \* np.pi, 360 \* 4)
lidarBoundaryX = radius \* np.cos(theta)
lidarBoundaryY = radius \* np.sin(theta)

def fetch\_lidar\_data():
global scan\_data\_x
global scan\_data\_y
global scan\_data\_r
global scan\_data\_theta
global lidar
global message
for scan in lidar.iter\_scans():
message = "Forward"
direction = 1
for (\_, angle, distance) in scan:
angle = float(angle)
angle\_value = angle\*0.0174533
ox = np.sin(angle\_value) \* distance
oy = np.cos(angle\_value) \* distance
if distance <= dangerDistance:
message = "Stop"

```
            direction = 2
            if (((angle>=0) and (angle <= startAngle))):
                message = "Obst in Right so move Left"
                direction = 3
            elif ((angle >= endAngle) and (angle <= 359.99)):
                message = "Obst in Left so move Right"
                direction = 4
        scan_data_x.append(ox)
        scan_data_y.append(oy)
        scan_data_x = scan_data_x[-length:]
        scan_data_y = scan_data_y[-length:]
```

def writeSerial():
try:
while True:
direction = input("enter direction")
s.write(direction)
finally:
s.close()

data\_thread = threading.Thread(target = fetch\_lidar\_data)
data\_thread.start()

if not s.isOpen():
print("was closed")
s.open()

t1 = Thread(target=writeSerial)
t1.start()

fig=plt.figure(figsize=(8,12))
ax = fig.add\_suploat(1,1,1)

def animate(i):

```
global scan_data_x
global scan_data_y
global message
ax.clear()
ax.plot([0],[0],'black')
ax.plot(lidarBoundaryX,lidarBoundaryY,'y')
ax.plot(dangerBoundaryX, dangerBoundaryY, 'r')
ax.plot(scan_data_x,scan_data_y,'b')
ax.text(0,radius,message,fontsize = 20, bbox = dict(facecolor='red', alpha = 0.5))
```

ani = animation.FuncAnimation(fig, animate, fargs=(), interval=1)
plt.show()
