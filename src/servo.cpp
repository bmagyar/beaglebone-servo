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
    sysfsfile_request << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_REQUEST;
    std::ifstream req_file(sysfsfile_request.str().c_str());
    std::string req_status;
    std::getline(req_file, req_status);
    std::cout << "req status: " << req_status << std::endl;
    if(req_status.find("free") == std::string::npos)
    {
        //throw std::exception();
	std::cerr << "PWM device not available at this time." << std::endl;
        _attached = false;
    } 
    else 
    {
        _attached = true; 
    }
    
    // if everything is okay we can move forward with opening the other files 
    std::stringstream sysfsfile_duty;
    std::stringstream sysfsfile_period;
    std::stringstream sysfsfile_polarity;
    std::stringstream sysfsfile_run;

    sysfsfile_duty << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_DUTY;
    sysfsfile_period << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_PERIOD;
    sysfsfile_run << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_RUN;

    _filename_request = sysfsfile_request.str();
    _filename_duty = sysfsfile_duty.str();
    _filename_period = sysfsfile_period.str();
    _filename_run = sysfsfile_run.str();


    set_request(1);    
    set_run(0);
    set_period(_PERIOD);
    set_duty(MIN_DUTY_NS); // initialize to 0 degree
    set_run(1);

    _pin = pin;
}

void Servo::write(int value)
{
    if(_attached)
    {
        _duty = MIN_DUTY_NS + value * DEGREE_TO_NS;
        _lastValue = value;
       set_duty(value);
    }
    else 
    {
        std::cerr << "Servo object not attached to pin!" << std::endl;
    }
}

void Servo::writeMicroseconds(int value)
{
    if(_attached)
    {
        set_duty(value*1000); // micro -> nano
        _lastValue = value*1000;
    }
    else 
    {
        std::cerr << "Servo object not attached to pin!" << std::endl;
    }
}

int Servo::read() const
{
    if(_attached)
    {
        return _lastValue;
    }
    else 
    {
        std::cerr << "Servo object not attached to pin!" << std::endl;
    }
}

bool Servo::attached() const
{
    return _attached;
}

void Servo::stop()
{
    if(_attached)
    {
        set_run(0);
        _run = 0;
    }
    else 
    {
        std::cerr << "Servo object not attached to pin!" << std::endl;
    }
}

void Servo::detach()
{
    if(_attached)
    {
        set_run(0);
        set_request(0);
        _attached = false;
    }
    else 
    {
        std::cerr << "Servo object not attached to pin!" << std::endl;
    }
}

std::string Servo::toString() const
{
    std::stringstream ss;

    ss << "Attached: " << _attached << ", pin: " << _pin 
       << ", period: " << _PERIOD << ", duty: " << _duty 
       << "run: " << _run
       ;

    return ss.str();
}


void Servo::set_request(const int val) 
{
    if(_attached)
    {
        _sysfsfid_request.open(_filename_request.c_str());
        _sysfsfid_request << val << std::endl;
        _sysfsfid_request.close();
    }
}

void Servo::set_duty(const int val) 
{
    if(_attached)
    {
        _sysfsfid_duty.open(_filename_duty.c_str());
        _sysfsfid_duty << val << std::endl; 
        _sysfsfid_duty.close();
    }
}

void Servo::set_period(const int val)
{
    if(_attached)
    {
        _sysfsfid_period.open(_filename_period.c_str());
        _sysfsfid_period << val << std::endl;
        _sysfsfid_period.close();
    }
}

void Servo::set_run(const int val)
{
    if(_attached)
    {
        _sysfsfid_run.open(_filename_run.c_str());
        _sysfsfid_run << val << std::endl;
        _sysfsfid_run.close();
    }
}


Servo::~Servo()
{
    if(_attached)
    {
        this->detach();
    }
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
//        throw std::exception();
        std::cerr << "Invalid pin name" << std::endl;
        ;
}
