# -*- coding: utf-8 -*-
"""
Created on Sat Nov  9 20:30:43 2019

@author: kai-s

this module contains  configuration functions for the UltrasonicSoundBarrier
"""

import datetime
import serial

def current_time():
    connected_device = serial.Serial('COM10', baudrate = 9600, timeout = 1)
    
    date_time= [12,40,00,0.,11,2018]
    timestamp = datetime.datetime.now()
    date_time[0]= timestamp.hour
    date_time[1]= timestamp.minute
    date_time[2]= timestamp.second
    date_time[3]= timestamp.year
    date_time[4]= timestamp.month
    date_time[5]= timestamp.day
    
    for x in range(0, 6):
        date_time[x] = str(date_time[x])
        #print(date_time[x])
       
    timestamp =  ",".join(date_time)
    
    return timestamp



def create_alert():
   section = 0
   strings = ["Hours","Minutes", "Seconds","Year","Months","Days"]
   user_input = ["12","40","00","0","11","2018"]

   while(section<6):
        print("Enter " + strings[section])
        user_input[section] = input();
        section = section +1 

   new_alert = ",".join(user_input)
   print(new_alert)
    
   return new_alert

def sort_alarms():
   sorted_alarms = [0,0]
    # Get alamrnumber from EEPROM
   i = 8
   
   # Poll for Data until every alarm was sent
   while(i>0):
       i = i-1
   
   
   #convert to useable format
   
   #sort alarms in ascending order
   
   
   return sorted_alarms