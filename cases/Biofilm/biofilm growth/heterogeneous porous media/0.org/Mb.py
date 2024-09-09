import numpy as np
#import requests
#from lxml import etree
import linecache

def average(list):
    average = sum(list)/len(list)
    return average

def readGradP(filepath):
    lnum = 0
    GradPdata = []
    with open(filepath, 'r') as fd:
        for line in fd:
            lnum += 1;
            if (lnum >= 23) & (lnum <= Pnum+22):
                temp=line.strip('()\n')
                GradPdata.append(temp)
    return GradPdata

line_read=21
my_file='MbbyMmax'
Pnum = 0
with open(my_file, 'r', encoding='utf8') as file:
    Pnum = int(linecache.getline(my_file,21))

Mb=readGradP("MbbyMmax")
sume=0.000
for i in range(Pnum):
    sume = sume + float(Mb[i])
Mbav = sume/Pnum
np.savetxt('Mb.txt', np.c_[Mbav], delimiter='\t')
