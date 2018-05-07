#!/usr/bin/env python
# Software License Agreement (BSD License)
#
# Copyright (c) 2008, Willow Garage, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of Willow Garage, Inc. nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Revision $Id$

## Simple talker demo that listens to std_msgs/Strings published 
## to the 'chatter' topic

import rospy
from std_msgs.msg import String

#////////////////// Step motor /////////////////
from time import sleep
import RPi.GPIO as GPIO

DIR = 20
STEP = 21
CW = 1
CCW = 0
SPR = 3 #Step per Revolution (720 / 7.5)
count = (0)
T = 3 #delay per block
c = 'n'
B = 0

GPIO.setmode(GPIO.BCM)
GPIO.setup(DIR, GPIO.OUT)
GPIO.setup(STEP, GPIO.OUT)


MODE = (14, 15, 18)
GPIO.setup(MODE, GPIO.OUT)
RESOLUTION = {'FULL' :(0,0,0),
              'HALF' :(1,0,0),
              '1/4' : (0,1,0),
              '1/8' : (1,1,0),
              '1/16': (0,0,1),
              '1/32': (1,0,1)}
GPIO.output(MODE, RESOLUTION['1/32'])

def FW(block):
    GPIO.output(DIR, CW)
    step_count = SPR*52*block
    delay = .0208/100
    for x in range(step_count):
        GPIO.output(STEP, GPIO.HIGH)
        sleep(delay)
        GPIO.output(STEP, GPIO.LOW)
        sleep(delay)
        
def BW(block):    
    GPIO.output(DIR, CCW)
    step_count = SPR*52*block
    delay = .0208/100
    for x in range(step_count):
        GPIO.output(STEP, GPIO.HIGH)
        sleep(delay)
        GPIO.output(STEP, GPIO.LOW)
        sleep(delay)

#///////////////////////////////////////////////

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + 'I heard %s', data.data)
    global B
    global H
#////////////////// Step motor Line UP /////////////////

    if str(data.data) == 'a':
		B = 8
		BW(8)
    if str(data.data) == 'b':
		B = 15
		BW(15)
    if str(data.data) == 'c':
		B = 25
		BW(25)
    if str(data.data) == 'd':
		B = 32
		BW(32)
    if str(data.data) == 'e':
		B = 42
		BW(42)
    if str(data.data) == 'f':
		B = 49
		BW(49)
    if str(data.data) == 'g':
		B = 58
		BW(58)
    if str(data.data) == 'y':
		if B == 15:
			FW(7)
		if B == 25:
			FW(17)
		if B == 32:
			FW(24)
		if B == 42:
			FW(34)
		if B == 49:
			FW(41)
		if B == 58:
			FW(50)
    if str(data.data) == 'z':
		if B == 8 or B == 15 or B == 25 or B == 32 or B == 42 or B == 49 or B == 58:
			FW(8)
#////////////////// Step motor Line Down /////////////////
    if str(data.data) == 'i':
		H = 8
		BW(8)
    if str(data.data) == 'j':
		H = 15
		BW(15)
    if str(data.data) == 'k':
		H = 25
		BW(25)
    if str(data.data) == 'l':
		H = 32
		BW(32)
    if str(data.data) == 'm':
		H = 41
		BW(41)
    if str(data.data) == 'n':
		H = 48
		BW(48)
    if str(data.data) == 'o':
		H = 58
		BW(58)
    if str(data.data) == 'v':
		if H == 15:
			FW(7)
		if H == 25:
			FW(17)
		if H == 32:
			FW(24)
		if H == 41:
			FW(33)
		if H == 48:
			FW(40)
		if H == 58:
			FW(50)
    if str(data.data) == 'w':
		if H == 8 or H == 15 or H == 25 or H == 32 or H == 41 or H == 48 or H == 58:
			FW(8)

#///////////////////////////////////////////////

def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber('chatter', String, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
	listener()
