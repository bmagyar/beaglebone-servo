#include "motorpwm.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdlib.h> 
MotorPwm::MotorPwm() 
    : _duty(0),  _run(0)
{
	std::cout << " MotorPwm() is called" << std::endl;
}

void MotorPwm::attach(const std::string& pin)
{
	std::cout << " MotorPwm::attach(const std::string& pin) is called" << std::endl;
    std::string filename = pinToFile(pin); // should throw an exception when something's wrong with the pin name

    // check if the pwm device is not used by someone else
    std::stringstream sysfsfile_request;
    sysfsfile_request << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_REQUEST;
    std::ifstream req_file(sysfsfile_request.str().c_str());
    std::string req_status;
    std::getline(req_file, req_status);
    std::cout << "MotorPwm attach req status: " << req_status << std::endl;
    if(req_status.find("free") == std::string::npos)
    {
        //throw std::exception();
	    std::cerr << "PWM device not available at this time."<< std::endl << " Request status: " << req_status << std::endl;
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

    sysfsfile_duty << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_DUTY_PERC;
    sysfsfile_period << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_PERIOD_FREQUENCY;
    sysfsfile_run << SYSFS_EHRPWM_PREFIX << filename << "/" << SYSFS_EHRPWM_RUN;

    _filename_request = sysfsfile_request.str();
    _filename_duty = sysfsfile_duty.str();
    _filename_period = sysfsfile_period.str();
    _filename_run = sysfsfile_run.str();


    set_request(1);    
    set_run(0);
    set_period(PWM_FREQUENCY);
    set_duty(0); // initialize to 0 degree
	set_run(1);
    _pin = pin;
}

void MotorPwm::write(int value)
{
	std::cout << "writing " << value << std::endl;
    if(_attached)
    {
       if (value>MAX_SPEED) value= MAX_SPEED;
	   std::cout << "MotorPwm::write(int value) " << value << std::endl;
	   set_duty(value); // micro -> nano
       _lastValue = value;
    }
    else 
    {
        std::cerr << "MotorPwm object not attached to pin!" << std::endl;
    }
}

void MotorPwm::writeMicroseconds(int value)
{
    /*if(_attached)
    {
        std::cout << " writeMicroseconds value " << value << " *1000 " << value*1000 << std::endl;
		set_duty(value*1000); // micro -> nano
        _lastValue = value*1000;
    }
    else 
    {
        std::cerr << "MotorPwm object not attached to pin!" << std::endl;
    }*/
}

int MotorPwm::read() const
{
    if(_attached)
    {
        return _lastValue;
    }
    else 
    {
        std::cerr << "MotorPwm object not attached to pin!" << std::endl;
    }
}

bool MotorPwm::attached() const
{
    return _attached;
}

void MotorPwm::stop()
{
    if(_attached)
    {
        set_run(0);
        _run = 0;
    }
    else 
    {
        std::cerr << "MotorPwm object not attached to pin!" << std::endl;
    }
}

void MotorPwm::detach()
{
    if(_attached)
    {
        set_run(0);
        set_request(0);
        _attached = false;
    }
    else 
    {
        std::cerr << "MotorPwm object not attached to pin!" << std::endl;
    }
}

std::string MotorPwm::toString() const
{
    std::stringstream ss;

    ss << "Attached: " << _attached << ", pin: " << _pin 
       << ", period: " << _PERIOD << ", duty: " << _duty 
       << "run: " << _run;

    return ss.str();
}


void MotorPwm::set_request(const int val) 
{
    if(_attached)
    {
				//set the value
				std::stringstream ss ;
				std::cout << "set duty request to " << val << std::endl;
                ss<<"echo " << val << " > " << _filename_request;
                system(ss.str().c_str());
				//get the setted value
				std::ifstream req_file(_filename_request.c_str());
                std::string req_status;
				std::getline(req_file, req_status);
				std::cout << "setted value: " << req_status << std::endl;
				/*ss.str(std::string());
				ss << val ;
				return ss.compare(req_status)== 0 */
    }
    else if(forced)
    {

    }
    else{
            std::cerr << "Pin is not attached!" << std::endl;
            //if (_pin==null||_pin==null){
                //std::cerr << "Pin is not set!" << std::endl;
            //}
            //else
            std::cerr << "Pin value: "<< _pin << std::endl;
    }
    
}

void MotorPwm::set_duty(const int val) 
{
    if(_attached)
    {
                //set the value
				std::cout << "MotorPwm::set_duty(const int val) " << val << std::endl;
				std::stringstream ss ;
                ss << "echo " << val <<" > " << _filename_duty;
                system(ss.str().c_str());
				//get the setted value
				std::ifstream duty_file(_filename_duty.c_str());
				std::string duty_status;
				std::getline(duty_file, duty_status);
				std::cout << "setted value: " <<duty_status << std::endl;
				/*ss.str(std::string());
				ss << val ;
				return ss.compare(duty_status) == 0 */
    }
    else if(forced)
    {

    }
    else{
            std::cerr << "Pin is not attached!" << std::endl;
            //if (_pin==null||_pin==null){
                //std::cerr << "Pin is not set!" << std::endl;
            //}
            //else
            std::cerr << "Pin value: "<< _pin << std::endl;
    }
}

void MotorPwm::set_period(const int val)
{
    if(_attached)
    {
				std::cout << "set period value to: " << val << std::endl;
				std::stringstream ss ;
				ss << "echo " << val << " > " << _filename_period;
				system(ss.str().c_str());
				std::ifstream period_file(_filename_period.c_str());
				std::string period_status;
				std::getline(period_file, period_status);
				std::cout << "setted value: " << period_status << std::endl;
				/*ss.str(std::string());
				ss << val ;
				return ss.compare(period_status) == 0 */
    }
    else if(forced)
    {

    }
    else{
            std::cerr << "Pin is not attached!" << std::endl;
            //if (_pin==null||_pin==null){
                //std::cerr << "Pin is not set!" << std::endl;
            //}
            //else
            std::cerr << "Pin value: "<< _pin << std::endl;
    }
}

void MotorPwm::set_run(const int val)
{
    if(_attached)
    {
			std::cout << " set run value to: "<< val << std::endl;
			std::stringstream ss ;
			ss << "echo " << val << " > " << _filename_run;
			system(ss.str().c_str());
			std::ifstream run_file(_filename_run.c_str());
			std::string run_status;
			std::getline(run_file, run_status);
			std::cout << " get run value: " << run_status << std::endl;
			/*ss.str(std::string());
			ss << val ;
			return ss.compare(run_status) == 0 */
    }
    else if(forced)
    {

    }
    else{
            std::cerr << "Pin is not attached!" << std::endl;
            //if (_pin==null||_pin==null){
                //std::cerr << "Pin is not set!" << std::endl;
            //}
            //else
            std::cerr << "Pin value: "<< _pin << std::endl;
    }

}

MotorPwm::~MotorPwm()
{
    if(_attached)
    {
        this->detach();
    }
}

void MotorPwm::enablepwm()
{
	std::stringstream ss ;
	//std::cout << "current dir: "<<get_currentdirectory() << std::endl;
    //ss << "python " << get_currentdirectory() <<"pwm.py" << std::endl;
	//TODO get current running directory
    ss << "python /root/drivers/BeagleBone-Tools/servo/example9.py" << std::endl;
	std::cout << ss.str().c_str();
	system(ss.str().c_str());
}

std::string MotorPwm::pinToFile(const std::string& pin) 
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

}