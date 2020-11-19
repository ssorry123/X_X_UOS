# -*- coding: utf-8 -*-
import socket
import sys
import os
import numpy as np
import pdb

import cv2
import time
import math

from Image2 import *
from Utils import *



# camera
from picamera import PiCamera
from time import sleep


# with aduino
import serial

#int change to 3byte string
def Aspeed(sL, sR):
    sL = sL - 5
    min = 10
    max = 30
    if(sL<min):
        n1 = min
    elif(sL >max):
        n1 = max
    else:
        n1 = sL
        
    if(sR<min):
        n2 = min
    elif(sR >max):
        n2 = max
    else:
        n2 = sR
    n3 = 100*int(n1) +int(n2)
    return n3
    
def fcmd(c, n):
    cmd = ("X%c%d\n" %(c,n)).encode('ascii')
    print("My cmd is %s" % cmd)
    for i in range(5):
        ser.write(cmd)
        sleep(0.1)


ser = serial.Serial('/dev/ttyUSB0',9600)
if ser is None:
    print('123')
    ser = serial.Serial('/dev/ttyUSB1',9600)

t=True
###########################################

speedL2 = 0
speedR2 = 0
temp2 = 0
olddirection = 0
while t:
    try:
        font = cv2.FONT_HERSHEY_SIMPLEX
        direction = 0

#N_SLICES만큼 이미지를 조각내서 Images[] 배열에 담는다
        Images=[]
        N_SLICES = 3

        for q in range(N_SLICES):
            Images.append(Image())

    #img = cv2.imread('dave.jpg')
        camera = PiCamera()

        camera.capture('/home/pi/image.jpeg', use_video_port=True)
        img = cv2.imread('/home/pi/image.jpeg')
        camera.close()
        print("as")
        points=[]
        if img is not None:
    #이미지를 조각내서 윤곽선을 표시하게 무게중심 점을 얻는다
            points = Points = SlicePart(img, Images, N_SLICES)
        #print('Points : ', Points)

    #N_SLICES 개의 무게중심 점을 x좌표, y좌표끼리 나눈다
            x = Points[::2]
            y = Points[1::2]

    #조각난 이미지를 한 개로 합친다
            fm = RepackImages(Images)
    
    
        #sleep(1)
    #완성된 이미지를 표시한다
        #cv2.imshow("Vision Race", fm)
        #if cv2.waitKey(0) & 0xFF == ord('q'):
       #     cv2.destroyAllWindows()
        else:
            print('not even processed')
        print(points)
        print('move')
    
        import math

        x1 =1.5
        x2 =1.5

        y1 = (points[2][0] - points[1][0])/250
        y2 = (points[1][0] - points[0][0])/250

        c = 20
        speedL1 = c*x1/2 -  y1
        speedR1 = c*x1/2 +  y1
        
        
    
        midweightpoint = (points[0][0] + points[1][0]+ points[2][0])
        temp1 = points[0][0]*points[0][1] + points[1][0]*points[1][1] + points[2][0]*points[2][1]
        
        if (points[0][1] < 0.3 and points[1][1] < 0.3 ):
            '''
            if points[0][1] < 0.3:
                olddirection = points[1][0]
            else:
                olddirection = points[0][0]
                '''
            if olddirection < 0 :
                print('go right from olddirection')
                fcmd('L', 6000)
                continue
            else:
                print('go left from olddirection')
                fcmd('R',6000)
                continue
       
        else:
            if(points[0][1] < 0.3):
                olddirection = points[1][0]
            else:
                olddirection = points[0][0]
   
   #dudwjawhwjf
        if points[2][1] >0.5:
            if points[2][0] > 150:
        #if points[2][0]*points[2][1] + points[1][0]*points[1][0] > 450:
                print('change 0point')
                fcmd('R', 6000)
            #fcmd('R',2000)
                continue
            elif points[2][0]  < -100:
        #if points[2][0]*points[2][1] + points[1][0]*points[1][0] < -400:
                print('change 0point')
                fcmd('L', 6000)
            #fcmd('R',2000)
                continue
            else:
                print('go straight0')
                fcmd('R',2000)
                
        elif points[1][1] > 0.5:
            if points[1][0] > 400:
        #if points[2][0]*points[2][1] + points[1][0]*points[1][0] > 450:
                print('change 0point from second point')
                fcmd('R', 6000)
            #fcmd('R',2000)
                continue
            elif points[1][0]  < -350:
        #if points[2][0]*points[2][1] + points[1][0]*points[1][0] < -400:
                print('change 0point from second point')
                fcmd('L', 6000)
            #fcmd('R',2000)
                continue
            else:
                print('go straight0 from second point')
                fcmd('R',2000)
                
        elif points[0][1] > 0.5
            if points[0][0] > 600:
        #if points[2][0]*points[2][1] + points[1][0]*points[1][0] > 450:
                print('change 0point from third point')
                fcmd('R', 6000)
            #fcmd('R',2000)
                continue
            elif points[0][0]  < -550:
        #if points[2][0]*points[2][1] + points[1][0]*points[1][0] < -400:
                print('change 0point from third point')
                fcmd('L', 6000)
            #fcmd('R',2000)
                continue
            else:
                print('go straight0 from third point')
                fcmd('R',2000)
                
    
        if speedL1 > speedR1 :
            if midweightpoint <0:
            #if temp1 > 0:
                print('go straight1')
                fcmd('R',2000)
            else:
                print('go left')
                fcmd('R', 6000)
        else:
            if midweightpoint >= 0:
            #if temp1<0:
                print('go straight2')
                fcmd('R',2000)
            else:
                print('go right')
                fcmd('L', 6000)
        
        speedL2 = c*x2/2 -  y2
        speedR2 = c*x2/2 +  y2
        
                
        #if speedL2 > speedR2 :
        #    if midweightpoint <0:
        #        fcmd('R',2000)
        #    else:
       #         fcmd('R', 6000)
       # else:
       #     if midweightpoint >= 0:
      #          fcmd('R',2000)
       #     else:
       #         fcmd('L', 6000)
    
    
    
    #if speedL2 > speedR2 :
     #   cmd = ("XR%d\n" % 6000 ).encode('ascii')
      #  print("My cmd is %s" % cmd)
       # for i in range(5):
        #    ser.write(cmd)
         #   sleep(0.1)
    #else:
     #   cmd = ("XL%d\n" % 6000 ).encode('ascii')
      #  print("My cmd is %s" % cmd)
       # for i in range(5):
        #    ser.write(cmd)
         #   sleep(0.1)
    
    
    
        #read_serial=ser.readline()
        #print (read_serial)
        print('sss')
        t=True
    except Exception as s:
        print(s)
        print("Exception")
        if olddirection < 0 :
            print('go right from olddirection')
            fcmd('L', 6000)
            continue
        else:
            print('go left from olddirection')
            fcmd('R',6000)
            continue
        t=True
        continue
        
    
    

