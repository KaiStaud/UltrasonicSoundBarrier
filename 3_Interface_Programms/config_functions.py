# -*- coding: utf-8 -*-
"""
Created on Sat Nov  9 20:30:43 2019

@author: kai-s

this module contains  configuration functions for the UltrasonicSoundBarrier
"""

import datetime
import serial
# open connection
connection = serial.Serial('COM10',baudrate = 9600,timeout = 1)

# Software Interface Layer
    #This function allows an complete or time only configuration
def init_module(full_config):
    # Get current time
    now = current_time()
    send_serial(now)
    # configurate alarms
    if full_config:
        na_module()
 
    #close serial port
    else:
        connection.close()

# Create two new alarms     
def na_module():    
    alarms = ["Alarm1","Alarm2","z\r\n"]
    # configurate alarms
    alarms[0] = new_alarm()
    alarms[1]=  new_alarm()
    joint_alarms = ",".join(alarms)
    send_serial(joint_alarms)
    #close serial port
    connection.close()

    
    
# Barebone Init Functions
    # Get the current time -> return to Send Serial Layer
def current_time():
    #connected_device = serial.Serial('COM10', baudrate = 9600, timeout = 1)
    
    date_time= [12,40,00,0,11,2018,00]
    timestamp = datetime.datetime.now()
    date_time[0]= timestamp.hour
    date_time[1]= timestamp.minute
    date_time[2]= timestamp.second
    date_time[3]= timestamp.year
    date_time[4]= timestamp.month
    date_time[5]= timestamp.day
    # Terminate String
    date_time[6] ="z\r\n"
    
    for x in range(0, 7):
        date_time[x] = str(date_time[x])
        #print(date_time[x])
       
    timestamp =  ",".join(date_time)
    
    return timestamp    

    # Function for creating new alarm -> return to Send Serial
def new_alarm() :
    inputs = ["Hours","Minutes","Seconds"]
    
    # Get input from user
    for i in range(3):
      print("Please Enter " + inputs[i])
      inputs[i] = str(input())
    
     # Merge strings together
    alarm = ",".join(inputs)
    print(alarm)
    #return string from function
    return alarm;      

# Hardware Interface Layer
    # only this function actually interfaces to the Hardware
def send_serial(nts):
#encode to bytes
    string_b = nts.encode()
# send to Serial Port  
    connection.write(string_b)