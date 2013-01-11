/*
  

  Created by Jacob Rosenthal and Colin Ho, December 30, 2012.
  Released into the public domain.
*/

// include core Wiring API
#include "Arduino.h"

// include this library's description file
#include "Shieldbot.h"

#define pinI1 5      //define I1 interface
#define speedpinA 6  //enable motor A
#define pinI2 7      //define I2 interface 
#define pinI3 8      //define I3 interface 
#define speedpinB 9  //enable motor B
#define pinI4 10     //define I4 interface 
#define lyfind1 A0   //define line finder S1
#define lyfind2 A1   //define line finder S2
#define lyfind3 A2   //define line finder S3  //d3 always 0
#define lyfind4 A3   //define line finder S4  //d4 always 1
#define lyfind5 4    //define line finder S5
int speedmotorA =75; //define the speed of motorA
int speedmotorB =75; //define the speed of motorB


Shieldbot::Shieldbot()
{
	pinMode(pinI1,OUTPUT);
	pinMode(pinI2,OUTPUT);
	pinMode(speedpinA,OUTPUT);
	pinMode(pinI3,OUTPUT);
	pinMode(pinI4,OUTPUT);
	pinMode(speedpinB,OUTPUT);
	pinMode(lyfind1,INPUT);
	pinMode(lyfind2,INPUT);
	pinMode(lyfind3,INPUT);
	pinMode(lyfind4,INPUT);
	pinMode(lyfind5,INPUT);
}

//sets same max speed to both motors
void Shieldbot::setMaxSpeed(int both){
  setMaxLeftSpeed(both);
  setMaxRightSpeed(both);
}

void Shieldbot::setMaxLeftSpeed(int left){
  speedmotorB=left;
}

void Shieldbot::setMaxRightSpeed(int right){
  speedmotorA=right;
}

int Shieldbot::readS1(){
	return digitalRead(lyfind1);
}

int Shieldbot::readS2(){
	return digitalRead(lyfind2);
}

int Shieldbot::readS3(){
	return digitalRead(lyfind3);
}

int Shieldbot::readS4(){
	return digitalRead(lyfind4);
}

int Shieldbot::readS5(){
	return digitalRead(lyfind5);
}

void Shieldbot::drive(char left, char right){
	rightMotor(right);
	leftMotor(left);
}

//char is 128 to 127
//mag is the direction to spin the right motor
//-128 backwards all the way
//0 dont move
//127 forwards all the way
void Shieldbot::rightMotor(char mag){
  int actualSpeed = 0;  
  if(mag >0){ //forward
    float ratio = (float)mag/128;
    actualSpeed = (int)(ratio*speedmotorA); //define your speed based on global speed
    Serial.print("forward right: ");
    Serial.println(actualSpeed);
    analogWrite(speedpinA,actualSpeed);
    digitalWrite(pinI1,HIGH);
    digitalWrite(pinI2,LOW);//turn right motor clockwise
  }else if(mag == 0){ //neutral
    Serial.println("nuetral right");
	stopRight();
  }else { //meaning backwards
    float ratio = (float)abs(mag)/128;
    actualSpeed = ratio*speedmotorA;
    Serial.print("backward right: ");
    Serial.println(actualSpeed);
    analogWrite(speedpinA,actualSpeed);
    digitalWrite(pinI1,LOW);
    digitalWrite(pinI2,HIGH);//turn right motor counterclockwise
  }
}
//TODO shouldnt these share one function and just input the differences?
void Shieldbot::leftMotor(char mag){
  int actualSpeed = 0;  
  if(mag >0){ //forward
    float ratio = (float)(mag)/128;
    actualSpeed = (int)(ratio*speedmotorB); //define your speed based on global speed
    Serial.print("forward left: ");
    Serial.println(actualSpeed);
    analogWrite(speedpinB,actualSpeed);
    digitalWrite(pinI3,HIGH);
    digitalWrite(pinI4,LOW);//turn left motor counter-clockwise
  }else if(mag == 0){ //neutral
    Serial.println("nuetral left");
	stopLeft();
  }else { //meaning backwards
    float ratio = (float)abs(mag)/128;
    actualSpeed = ratio*speedmotorB;
    Serial.print("backward left: ");
    Serial.println(actualSpeed);
    analogWrite(speedpinB,actualSpeed);
    digitalWrite(pinI3,LOW);
    digitalWrite(pinI4,HIGH
    );//turn left motor counterclockwise
  }
}


//direction true is forward, false is backward
//Turns left, mag varies from wide left (0) to tight left (255)
//tight left (255) maps to Right motor all the way forwards, left motor all teh way backwards
//half left (128) maps to Right motor all the way forwards, left motor off
//wide left (0) maps to right motor all the way forwards, left motor all the way forwards
void Shieldbot::left(int mag, direction dir){
  
  Serial.print("mag: ");
  Serial.println(mag);

  int left, right;

  if(dir==FORWARD){
  	left = map(mag,0,255,127,-128);
	right = 127;
  }else{
  	left = map(mag,0,255,-128,127);
	right = -128;
  }
  
  Serial.print("right turn: ");
  Serial.println(left);
  
  leftMotor(left); //minimum is 0
  rightMotor(right); //max is 127

}

//direction true is forward, false is backward
//Turns right, mag varies from wide right (0) to tight right (255)
//direction is true for forward, false for backward, defaults to true
//tight right (255) maps to left motor all the way forwards, right motor all teh way backwards
//half right (128) maps to left motor all the way forwards, right motor off
//wide right (0) maps to left motor all the way forwards, right motor all the way forwards
void Shieldbot::right(int mag, direction dir){
  
  Serial.print("mag: ");
  Serial.println(mag);
  //so if mag is 255, left motor is 0, is 
  //if mag is 255 left motor 1, right motor 254
  
  int left, right;

  if(dir==FORWARD){
  	right = map(mag,0,255,127,-128);
	left = 127;
  }else{
	right = map(mag,0,255,-128,127);
	left = -128;
  }

  Serial.print("left turn: ");
  Serial.println(right);

  
  rightMotor(right); //minimum is 0
  leftMotor(left); //max is 127
}

void Shieldbot::forward(){
  leftMotor(127);
  rightMotor(127); 
}

void Shieldbot::backward(){
  leftMotor(-128);
  rightMotor(-128); 
}

void Shieldbot::stop(){
	fastStopLeft();
	fastStopRight();
}

void Shieldbot::stopLeft(){
  digitalWrite(pinI3,LOW);
  digitalWrite(pinI4,LOW);//turn DC Motor B move clockwise
}

void Shieldbot::stopRight(){
  digitalWrite(pinI1,LOW);
  digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise

}
