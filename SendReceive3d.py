#!/usr/local/bin/python

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
cxn = Serial('/dev/tty.usbmodem1421', baudrate=9600)

f= open("lab2readings.txt","wb")
fig = plt.figure()
ax = fig.gca(projection='3d')
coorz = []
coorx = []
coory = []
running = True
threshold = 16 #16 for polar coordinates, x for cartesian 

while running == True:
# try:
    cxn.write([1])

    result = str(cxn.readline())

    print(result)
    if result[2:-5] == 'done':
        running = False

    else:

        start_pos1 = result.index(';')
        start_pos2 = result.index('/')
        end_pos2 = result.index(':')

        r = int(result[2:start_pos1])
        theta = int(result[start_pos2+1:end_pos2])
        phi = int(result[start_pos1+1:start_pos2])
        r = 112.1425508814386 - 1.0035935392387034*r + 0.00405508173593060*r**2 - 7.416839407985343*10**(-6)*r**3 + 4.934357177555067*10**(-9)*r**4
        
        x = r*np.cos(theta)*np.sin(phi)
        y = r*np.sin(theta)*np.sin(phi)
        z = r*np.cos(phi)

        if r < threshold:
            coorx.append(x)
            coory.append(y)
            coorz.append(z)


    # except ValueError:
    #     print("You must enter an integer value between 1 and 2.")


'''
coorx = np.linspace(1,20,20)
coory = np.linspace(1,5,20)
coorz = np.linspace(-10,-30,20)
'''

print([coorx,coory,coorz])
pickle.dump([coorx,coory,coorz], f) 
f.close()

file_pi2 = open('lab2readings.txt', 'rb') 
object_pi2 = pickle.load(file_pi2) 
print(object_pi2)
#X, Y = np.meshgrid(coorx, coory)
surf = ax.scatter(coorx, coory, coorz) #, cmap=cm.coolwarm, linewidth=0, antialiased=False)
    #ball = sphere(pos=vector(coord[0],coord[1],coord[2]), radius=0.5)

ax.set_xlabel('r')
ax.set_ylabel('Theta')
ax.set_zlabel('Phi')

# Customize the z axis.
#ax.zaxis.set_major_locator(LinearLocator(10))
#ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))

# Add a color bar which maps values to colors.
#fig.colorbar(surf, shrink=0.5, aspect=5)
#ax.set_xlabel('X axis')
#ax.set_ylabel('Z axis')
#ax.set_zlabel('Y axis')

plt.show()


