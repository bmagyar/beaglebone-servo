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

#ifndef __SERVO_H_
#define __SERVO_H_

#define MIN_DUTY_NS 500000
#define MAX_DUTY_NS 2000000
#define PWM_FRECUENCY 50 //hz 
#define DEGREE_TO_NS (MAX_DUTY_NS-MIN_DUTY_NS)/180

#define SYSFS_EHRPWM_PREFIX "/sys/class/pwm/"
#define SYSFS_EHRPWM_SUFFIX_A ":0"
#define SYSFS_EHRPWM_DUTY "duty_ns"
#define SYSFS_EHRPWM_PERIOD "period_ns"
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
class Servo
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
│   ├── duty_ns
│   ├── period_ns
│   ├── polarity
│   ├── request
│   ├── run
├── ehrpwm.0:1 -> ../../devices/platform/omap/ehrpwm.0/pwm/ehrpwm.0:1
│   ├── duty_ns
│   ├── period_ns
│   ├── polarity
│   ├── request
│   ├── run
 *

Define files to match sysfs tree:
*/

    std::ofstream _sysfsfid_duty;
    std::ofstream _sysfsfid_period;
    std::ofstream _sysfsfid_polarity;
    std::ofstream _sysfsfid_run;
    std::fstream _sysfsfid_request;

	int _duty;
	static const int _period = PWM_FRECUENCY;
	int _polarity;
	int _run;
   
    static std::string pinToFile(const std::string& pin); 
     
public:
    Servo();
     ~Servo();

    void attach(const std::string& pin);
    void write(int value);
    void writeMicroseconds(int value);
    int read() const;
    bool attached() const;
    void stop();
    void detach();

    std::string toString() const;

    //void setDuty(int value);
    //void setPeriod(int value);
    //void setPolarity(int value);
};

#endif 
