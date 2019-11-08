#!/usr/bin/python3

import os
from collections import namedtuple

try:
    import numpy as np
except:
    print("You don't have numpy, so please install it.")
    os.system("sudo pip3 install numpy")

Constants = namedtuple('Constants', ['page_llimit', 'page_ulimit', 'behave_l', 'behave_u'])
const = Constants(32, 48, 0, 5)

def write_proc(fhand, n):
    for i in range(n):
        pgnum = np.random.randint(const.page_llimit, const.page_ulimit+1)
        behave = np.random.randint(const.behave_l, const.behave_u+1)
        fhand.write(str(pgnum)+" "+str(behave)+"\n")

if __name__ == '__main__':
    n = int(input("Enter number of processes: "))
    fhand = open('proc_details.txt', 'w')
    write_proc(fhand, n)
    fhand.close()
