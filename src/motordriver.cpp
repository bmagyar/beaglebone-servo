#include "motordriver.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

MotorDriver::MotorDriver() 
{
	std::cout << " MotorDriver() is called" << std::endl;
}

void MotorDriver::init(){
	std::cout << " MotorDriver::init() is called" << std::endl;
	MotorPwm::enablepwm();
	
	std::cout << " init motor 1 " << std::endl;
	//init motor 1
	motor1.attach("P9_14");
	motor1dir = BeagleBone::gpio::P9(15);
	motor1dir->configure(BeagleBone::pin::OUT);
	std::cout << " init motor 1 " << std::endl;
	//init motor 2
	motor2.attach("P9_16");
	motor2dir = BeagleBone::gpio::P9(23);
	motor2dir->configure(BeagleBone::pin::OUT); 
}

void MotorDriver::forward(int milisec, int dutypercent){
	std::cout << "MotorDriver::forward(int milisec, int dutypercent) is called" << std::endl;
	motor1dir->set(1);
	motor2dir->set(0);
	motor1.write(dutypercent);
	motor2.write(dutypercent);
	sleep(milisec);
}

void MotorDriver::backward(int milisec, int dutypercent){
	
	motor1dir->set(0);
	motor2dir->set(1);
	motor1.write(dutypercent);
	motor2.write(dutypercent);
	sleep(milisec);
}

void MotorDriver::turnleft(int milisec, int dutypercent){
	motor1dir->set(0);
	motor2dir->set(0);
	motor1.write(dutypercent);
	motor2.write(dutypercent);
	sleep(milisec);
}

void MotorDriver::turnright(int milisec, int dutypercent){
	motor1dir->set(1);
	motor2dir->set(1);
	motor1.write(dutypercent);
	motor2.write(dutypercent);
	sleep(milisec);
	stop();
}

void MotorDriver::stop(){
	motor1.write(0);
	motor1.stop();
	motor2.write(0);
	motor2.stop();
}

void MotorDriver::detach(){
	motor1.detach();
	motor2.detach();
}

MotorDriver::~MotorDriver(){
	motor1.detach();
	motor2.detach();
}