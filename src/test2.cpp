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
    servo.writeMicroseconds(2000); //to middle
    sleep(1);

    std::cout << "To max" << std::endl;
    servo.writeMicroseconds(1390); //max
    sleep(1);

    std::cout << "To min" << std::endl;
    servo.writeMicroseconds(500); //min
    sleep(1);

    servo.detach();

    return 0;
}
