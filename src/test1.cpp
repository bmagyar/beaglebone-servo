#include "servo.h"
#include <unistd.h> // to use sleep
#include <iostream>


int main(int argc, char** argv)
{
    Servo servo;
    servo.attach("P9_14");

    for(int i=0; i<3; ++i)
    {
        std::cout << i << std::endl;
        sleep(1);
    }

    std::cout << "To middle" << std::endl;
    servo.writeMicroseconds(1500); //to middle
    sleep(1);

    std::cout << "To max" << std::endl;
    servo.writeMicroseconds(2000); //max
    sleep(1);

    std::cout << "To min" << std::endl;
    servo.writeMicroseconds(500); //min
    sleep(1);
    //The value in microseconds can change between servos. You can use this function to obtain the max and min values.
    // Next, you can use this values to fix the servo class to your own servos (if you need it)



//Angle from 0 to 180 degrees
    for(int i=0; i<180; ++i)
    {   
        std::cout << i << ","; 
        servo.write(i);
        usleep(200000);
    }
    std::cout << std::endl;
    
    for(int i=180; i<0; --i)
    {    
        std::cout << i << ","; 
        servo.write(i);
        usleep(200000);
    }
    std::cout << std::endl;

    servo.detach();

    return 0;
}
