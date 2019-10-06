#!/usr/bin/python3

import sys
import numpy as np
from math import floor, ceil

def input_data() -> (int, int, str):
    M = int(input("Enter the value of M: "))
    S = int(input("Enter the value of S[0-5]: "))
    if S not in range(0, 6):
        print("S should be in the range of [0-5]")
        sys.quit()
    fname = input("Enter the file name: ")

    return M, S, fname

def generate_addresses(M: int, S: int, fname: str) -> None:
    fh = open(fname, "w")

    for i in range(M):
        c = np.random.randint(M) + 1
        L = np.random.randint(512, 4097)

        normal = list()
        uniform = list()

        d = c * 4096 + 2048
        j = 0
        while j < floor(0.9*L):
            val = (np.random.randint(0, 1) * (500*(S+1))) + d
            np.random.seed(val) # Seeding the PRNG
            val = (np.random.randint(0, 1) * (500*(S+1))) + d
            normal.append(val)
            j = j + 1

        c = np.random.randint(M) + 1
        for j in range(ceil(0.1*L)):
            uniform.append(np.random.randint(0, c))

        normal = " ".join(map(str, normal))
        uniform = " ".join(map(str, uniform))
        fh.write(normal+" "+uniform+"\n\n")
    fh.close()

if __name__ == "__main__":
    np.random.seed(88) # Seeding the PRNG
    M, S, fname = input_data()
    generate_addresses(M, S, fname)
