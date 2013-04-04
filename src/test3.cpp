#include "motordriver.h"
#include <unistd.h> // to use sleep
#include <iostream>


int main(int argc, char** argv)
{
    MotorDriver md;
    //servo.attach("P9_14");

    for(int i=0; i<3; ++i)
    {
        std::cout << i << std::endl;
        sleep(1);
    }
	md.init();
	md.forward(2,10);
	md.backward(2,10);
	md.turnleft(2,10);
	md.turnright(2,10);
    md.stop();
	md.detach();

    return 0;
}
