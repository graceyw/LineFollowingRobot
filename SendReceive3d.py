from serial import Serial, SerialException
import numpy as np
import pickle

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter

# The Serial constructor will take a different first argument on
# Windows. The first argument on Windows will likely be of the form
# 'COMX' where 'X' is a number like 3,4,5 etc.
# Eg.cxn = Serial('COM5', baudrate=9600
#
# NOTE: You won't be able to program your Arduino or run the Serial
# Monitor while the Python script is running.
cxn = Serial('/dev/ttyACM0', baudrate=9600)

fig = plt.figure()

running = True
leftMotor = []
leftSensor = []
rightMotor = []
rightSensor = []

while running:
    cxn.write([1])
    while cxn.inWaiting():
        continue

    result = str(cxn.readline()
    print(result)
    if result[0] == '<':
        result = result[1:-1]   #cut off carrot
        result = result.replace('\n','')   #replace any \n 's with nothing
        data = result.split(',')

        if len(data) = 4:
            leftMotor.append(data[0])
            leftSensor.append(data[1])
            rightMotor.append(data[2])
            rightSensor.append(data[3])
    if len(leftMotor) > 10000:
        break

plt.plot(np.linspace(1,len(leftMotor),len(leftMotor)),leftMotor,label="Left Motor")    #linspace(start,end,number of points)
plt.plot(np.linspace(1,len(leftMotor),len(leftMotor)),leftSensor,label="Left Sensor")    #linspace(start,end,number of points)
plt.plot(np.linspace(1,len(leftMotor),len(leftMotor)),rightMotor,label="Right Motor")    #linspace(start,end,number of points)
plt.plot(np.linspace(1,len(leftMotor),len(leftMotor)),rightSensor,label="Right Sensor")    #linspace(start,end,number of points)
plt.legend()
plt.show()
ax.set_xlabel('Time')
ax.set_ylabel('Values')

# Customize the z axis.
#ax.zaxis.set_major_locator(LinearLocator(10))
#ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))

# Add a color bar which maps values to colors.
#fig.colorbar(surf, shrink=0.5, aspect=5)
#ax.set_xlabel('X axis')
#ax.set_ylabel('Z axis')
#ax.set_zlabel('Y axis')
