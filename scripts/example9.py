import time
import pwm #Used to enable PWM
from servo import Servo

#You can use your own method to enable PWM, but this just works
pwm.enable();

servo1 = Servo()
servo1.attach("P9_14")
servo2 = Servo()
servo2.attach("P9_16")
servo3 = Servo()
servo3.attach("P8_13")
servo4 = Servo()
servo4.attach("P8_19")

servo1.detach()
servo2.detach()
servo3.detach()
servo4.detach()

