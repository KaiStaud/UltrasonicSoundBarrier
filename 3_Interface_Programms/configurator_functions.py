# -*- coding: utf-8 -*-
"""
Created on Sat Nov  9 20:30:43 2019

@author: kai-s

this module contains functions for the UltrasonicSoundBarrier
"""

import datetime

def create_timestamp():
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
    
    #print(timestamp)
    return timestamp


