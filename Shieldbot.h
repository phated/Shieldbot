/*
  

  Created by Jacob Rosenthal and Colin Ho, December 30, 2012.
  Released into the public domain.
*/

// ensure this library description is only included once
#ifndef Shieldbot_h
#define Shieldbot_h


// include types & constants of Wiring core API
#include "Arduino.h"

// library interface description
class Shieldbot
{
  // user-accessible "public" interface
  public:
	enum direction {
	  FORWARD,
	  BACKWARD
	};
	Shieldbot();
	int readS1();
	int readS2();
	int readS3();
	int readS4();
	int readS5();
	void setMaxSpeed(int);
	void setMaxLeftSpeed(int);
	void setMaxRightSpeed(int);
	void rightMotor(char);
	void leftMotor(char);
	void right(int, direction dir = FORWARD);
	void left(int, direction dir = FORWARD);
	void forward();
	void backward();
	void fastStop();
	void stop();

};

#endif