from serial import Serial, SerialException
import numpy as np
import pickle

import matplotlib.pyplot as plt
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
input()

while running:
    while not cxn.inWaiting():
        continue
    res =cxn.readline()
    print(res)
    result = res.decode("utf-8","ignore")
    print(result)
    if result[0] == '<':
        result = result[1:-1]   #cut off carrot
        result = result.replace('\n','')   #replace any \n 's with nothing
        result = result.replace('<',',')   #replace any <'s with commas
        data = result.split(',')
        if len(data) == 4:                      #if it is usable data containing one value from each sensor and motor
            print(len(leftMotor))
            leftMotor.append(float(data[0]))     #add the left motor value to the leftMotor list
            leftSensor.append(float(data[1]))    #add the left sensor value to the leftSensor list
            rightMotor.append(float(data[2]))    #add the right motor value to the rightMotor list
            rightSensor.append(float(data[3]))   #add the right motor value to the rightMotor list
    if len(leftMotor) > 500:
        break                   #stop after 500 because we don't need more than ~500 data points to create a useful visualization

leftMotor = np.array(leftMotor)
leftSensor= np.array(leftSensor)
rightMotor = np.array(rightMotor)
rightSensor = np.array(rightSensor)


leftMotor = (np.array(leftMotor))/np.amax(rightMotor)
leftSensor = (np.array(leftSensor) - np.amin(leftSensor))/np.amax(leftSensor)
rightMotor = (np.array(rightMotor))/np.amax(rightMotor)
rightSensor = (np.array(rightSensor) - np.amin(rightSensor))/np.amax(rightSensor)
plt.plot(np.linspace(1,len(leftMotor),len(leftMotor)),leftMotor,label="Left Motor")    #linspace(start,end,number of points)
plt.plot(np.linspace(1,len(leftMotor),len(leftMotor)),leftSensor,label="Left Sensor")    #linspace(start,end,number of points)
plt.plot(np.linspace(1,len(leftMotor),len(leftMotor)),rightMotor,label="Right Motor")    #linspace(start,end,number of points)
# plt.plot(np.linspace(1,len(leftMotor),len(leftMotor)),rightSensor,label="Right Sensor")    #linspace(start,end,number of points)
plt.legend()
plt.xlabel('Time')
plt.ylabel('Values')
plt.show()
