# -*- coding: utf-8 -*-
"""
Created on Sat Nov  9 18:11:41 2019

@author: kai-s

This file drives overlying the main application
"""
 
import config_functions as DUT_cf
import testing_functions as DUT_tf


commands =['f','g']

print("Enter 1 for initializing a new system, 2 for creating alarms, 3 for basic testing or 4 for an full HIL Test" )
select = int(input('Input:'))

if(select == 1):
    DUT_cf.init_module(1)
elif(select == 2):
    DUT_cf.na_module()
elif(select == 3):
    DUT_tf.Hardware_Test()
elif(select == 4):    
    print("Not implement yet")
    
    