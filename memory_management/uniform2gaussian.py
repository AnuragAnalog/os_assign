#!/usr/bin/python3

import os
from collections import namedtuple

try:
    import numpy as np
except:
    print("You don't have numpy, so please install it.")
    os.system("sudo pip3 install numpy")

Constants = namedtuple('Constants', ['rand_max'])
const = Constants(32767)

def rand_uniform(ll, hh):
    u1 = 
