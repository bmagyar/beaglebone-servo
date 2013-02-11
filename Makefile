all: servo test1

servo: servo.h servo.cpp
	g++ -c servo.cpp -o servo.o	

test1: servo.o test1.cpp
	g++ test1.cpp servo.o -o test1	

clean: 
	rm servo.o test1
