# -*- coding: utf-8 -*-
#import needed modules
import datetime
import serial
import time

commands =['a','b','c','d','e','f','g']
date_time= [28,10,2019,12,40,00]

#Check if module is connected properly
slave= serial.Serial('COM5', baudrate = 9600, timeout = 1)
time.sleep(2)

#Ask user to create request
print("Choose your input. Type number according to options below:")
print("Set new Time -> 0 , Test functionality -> 1")
select = int(input('Input:'))

if select==0:
    # Get current date and time information
    timestamp = datetime.datetime.now()
    
    date_time[0]= timestamp.day
    date_time[1]= timestamp.month
    date_time[2]= timestamp.year
    date_time[3]= timestamp.hour
    date_time[4]= timestamp.minute
    date_time[5]= timestamp.second

elif select ==1:
        for x in commands:
        #   needs to be implemented : accessing array element
        #    slave.write(str.encode(commands[x]))
        #    print(slave.readline())
        # delay one second
        time.sleep(1)

slave.close()    
# roll out config routine    