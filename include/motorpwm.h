/*
BSD License
Copyright © 2013, Bence Magyar
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the owner nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __MOTORPWM_H_
#define __MOTORPWM_H_

#define MAX_SPEED 78
#define MIN_SPEED 10
#define PWM_FREQUENCY 8000 //hz

#define SYSFS_EHRPWM_PREFIX "/sys/class/pwm/"
#define SYSFS_EHRPWM_SUFFIX_A ":0"
#define SYSFS_EHRPWM_DUTY_PERC "duty_percent"
#define SYSFS_EHRPWM_PERIOD_FREQUENCY "period_frequency"
#define SYSFS_EHRPWM_POLARITY "polarity"
#define SYSFS_EHRPWM_RUN "run"
#define SYSFS_EHRPWM_REQUEST "request"


#include <fstream>
#include <string>

/**
 * \author Bence Magyar
 * \year 2013
 * \brief This is a class implementing an Arduino-style servo interface for the BeagleBone. PWM control is used through the filesystem interface of Angstrom and Debian systems.
 **/
class MotorPwm
{
private:
    std::string _pin;
    bool _attached;
    double _lastValue;
	
/*****************************************
 *
 * sysfs tree:
 *
ehrpwm.0:0
¦   +-- duty_ns
¦   +-- period_ns
¦   +-- polarity
¦   +-- request
¦   +-- run
+-- ehrpwm.0:1 -> ../../devices/platform/omap/ehrpwm.0/pwm/ehrpwm.0:1
¦   +-- duty_ns
¦   +-- period_ns
¦   +-- polarity
¦   +-- request
¦   +-- run
 *

Define files to match sysfs tree:
*/

    std::ofstream _sysfsfid_duty;
    std::ofstream _sysfsfid_period;
    //std::ofstream _sysfsfid_polarity;
    std::ofstream _sysfsfid_run;
    std::fstream _sysfsfid_request;

    std::string _filename_request;
    std::string _filename_duty;
    std::string _filename_period;
    //std::string _filename_polarity;
    std::string _filename_run;
    int _duty;
    static const int _PERIOD = PWM_FREQUENCY;
    int _polarity;
    int _run;
    bool forced;
    static std::string pinToFile(const std::string& pin); 
    
		
public:
    MotorPwm();
     ~MotorPwm();
	void attach(const std::string& pin);
    //void init();
    void write(int value);
    void writeMicroseconds(int value);
    int read() const;
    bool attached() const;
    void stop();
    void detach();
	static void enablepwm();
	std::string toString() const;

private:
    void set_request(const int val); 
    void set_duty(const int val); 
    void set_period(const int val); 
    void set_run(const int val); 
};

#endif 
