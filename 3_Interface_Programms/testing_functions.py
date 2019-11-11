# -*- coding: utf-8 -*-
"""
Created on Sun Nov 10 20:05:39 2019

@author: kai-s

module covers HIL and normal System Test
"""

import serial

def Hardware_Test():
    # Callbacks received, when entering a new state
    callbacks_received = ['Init finished','Idling MCU','entering sleep mo'] 
    enter_callbacks = ['Just','Empty','Space']
    # Callbacks received, when leaving current state
    leaving_message = ['Back to standard run mode','Back up runnning'] 
    leave_callbacks = ['nya','nicesu']
    
    SUT = serial.Serial('COM5', baudrate = 9600, timeout = 1)
    enter_callbacks[0] = SUT.readline().decode('ascii')
    
    # Wait for Initialization Callback 
    if(enter_callbacks[0] == callbacks_received[0]):
        print(callbacks_received[0])     
    
    
    # Enter Sleep mode
    SUT.write(b'b')
    while(enter_callbacks[1] != callbacks_received[1]):
        enter_callbacks[1] = SUT.readline().decode('ascii')
    print(callbacks_received[1])    
    
    # Wake  up SUT 
    SUT.write(b'x')
    while(leave_callbacks[0] != leaving_message[0]):
        leave_callbacks[0] = SUT.readline().decode('ascii')
    print(leaving_message[0])    
    
    # close session
    SUT.close()
    
