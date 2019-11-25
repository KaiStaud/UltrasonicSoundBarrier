# -*- coding: utf-8 -*-
"""
Created on Fri Nov 22 23:32:23 2019

@author: kai-s
"""

from Crypto.Util import number
result = 1
encryption_key = 1
#Generate two random 32 Bit primes
p=(number.getPrime(32))
q=(number.getPrime(32))

# Generate Public and Private Key
#loop until statement is true
while(!(isinstance(result, int))):
    

