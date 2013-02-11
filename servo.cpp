#include "servo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

Servo::Servo() 
    : _duty(0), _polarity(0), _run(0)
{
}

void Servo::attach(const std::string& pin)
{
    std::string filename = pinToFile(pin); // should throw an exception when something's wrong with the pin name

    // check if the pwm device is not used by someone else
	std::stringstream sysfsfile_request;
	_sysfsfid_request.open(sysfsfile_request.str().c_str());
	sysfsfile_request << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_REQUEST;
    int req_status;
    sysfsfile_request >> req_status;
//    if(req_status != 0)
//        throw std::exception("PWM device not available at this time.");
    
    // if everything is okay we can move forward with opening the other files 
    std::stringstream sysfsfile_duty;
	std::stringstream sysfsfile_period;
	std::stringstream sysfsfile_polarity;
	std::stringstream sysfsfile_run;

	sysfsfile_duty << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_DUTY;
	sysfsfile_period << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_PERIOD;
	sysfsfile_polarity << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_POLARITY;
	sysfsfile_run << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_RUN;

	_sysfsfid_duty.open(sysfsfile_duty.str().c_str());
	_sysfsfid_period.open(sysfsfile_period.str().c_str());
	_sysfsfid_polarity.open(sysfsfile_polarity.str().c_str());
	_sysfsfid_run.open(sysfsfile_run.str().c_str());
    


    _sysfsfid_request << "1" << std::endl;
    _sysfsfid_run << "0" << std::endl;
    _sysfsfid_period << _period << std::endl;
    _sysfsfid_duty << MIN_DUTY_NS << std::endl; // initialize to 0 degree
    _sysfsfid_run << "1" << std::endl;

    // push the fixed period setting and close the file
    _sysfsfid_period.close();

    _pin = pin;
    _attached = true;
}

void Servo::write(int value)
{
    _duty = MIN_DUTY_NS + value * DEGREE_TO_NS;
    _lastValue = value;
    _sysfsfid_duty << value << std::endl;
}

void Servo::writeMicroseconds(int value)
{
    _sysfsfid_duty << value << "000" << std::endl; // micro -> nano
    _lastValue = value*1000;
}

int Servo::read() const
{
    return _lastValue;
}

bool Servo::attached() const
{
    return _attached;
}

void Servo::stop()
{
	_sysfsfid_run << "0" << std::endl;
    _run = 0;
}

void Servo::detach()
{
	_sysfsfid_run << "0" << std::endl;
	_sysfsfid_request << "0" << std::endl;
    _attached = false;
}

std::string Servo::toString() const
{
    std::stringstream ss;

    ss << "Attached: " << _attached << ", pin: " << _pin 
       << ", period: " << _period << ", duty: " << _duty 
       << "run: " << _run
       ;

    return ss.str();
}

/*
void Servo::setDuty(int value)
{
    _duty = value;
    _sysfsfid_duty << value << std::endl;
}

void Servo::setPeriod(int value)
{
    _period = value;
    _sysfsfid_period << value << std::endl;
}

void Servo::setPolarity(int value)
{
    _polarity = value;
    _sysfsfid_polarity << value << std::endl;
}
*/

Servo::~Servo()
{
    this->detach();
}

std::string Servo::pinToFile(const std::string& pin) 
{
    if(pin == "P8_13")
        return "ehrpwm.2:1";
    else if(pin == "P8_19")
        return "ehrpwm.2:0";
    else if(pin == "P9_14")
        return "ehrpwm.1:0";
    else if(pin == "P9_16")
        return "ehrpwm.1:1";
    else if(pin == "P9_31")
        return "ehrpwm.0:0";
    else if(pin == "P9_29")
        return "ehrpwm.0:1";
    else if(pin == "P9_42")
        return "ecap.0";
    else if(pin == "P9_28")
        return "ecap.2";
    else 
//        throw std::exception("Invalid pin name");
        ;
}
