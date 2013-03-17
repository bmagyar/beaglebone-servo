beaglebone-servo
================

Servo library for the BeagleBone that mimics the functionality of Arduino servo library. 
Written in C++ although needs setPWMReg.py to be run after booting the BeagleBone and before attempting to use servos.

To build: 
mkdir build & cd build & cmake .. & make
