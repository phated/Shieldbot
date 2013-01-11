/*
  Created to support the release of the Sheildbot from SeeedStudios
  http://www.seeedstudio.com/wiki/Shield_Bot

  Created by Jacob Rosenthal and Colin Ho, December 30, 2012.
  Released into the public domain.
*/

// include core Wiring API
#include "Arduino.h"

// include this library's description file
#include "Shieldbot.h"

#define right1 5			//define I1 interface
#define speedPinRight 6  	//enable right motor (bridge A)
#define right2 7      		//define I2 interface 
#define left1 8      		//define I3 interface 
#define speedPinLeft 9  	//enable motor B
#define left2 10     		//define I4 interface 
#define finder1 A0   		//define line finder S1
#define finder2 A1   		//define line finder S2
#define finder3 A2   		//define line finder S3
#define finder4 A3   		//define line finder S4
#define finder5 4    		//define line finder S5

int speedmotorA = 255; //define the speed of motorA
int speedmotorB = 255; //define the speed of motorB

Shieldbot::Shieldbot()
{
  pinMode(right1,OUTPUT);
  pinMode(right2,OUTPUT);
  pinMode(speedPinRight,OUTPUT);
  pinMode(left1,OUTPUT);
  pinMode(left2,OUTPUT);
  pinMode(speedPinLeft,OUTPUT);
  pinMode(finder1,INPUT);
  pinMode(finder2,INPUT);
  pinMode(finder3,INPUT);
  pinMode(finder4,INPUT);
  pinMode(finder5,INPUT);
}

//sets same max speed to both motors
void Shieldbot::setMaxSpeed(int both){
  setMaxLeftSpeed(both);
  setMaxRightSpeed(both);
}

void Shieldbot::setMaxSpeed(int left, int right){
  setMaxLeftSpeed(left);
  setMaxRightSpeed(right);
}

void Shieldbot::setMaxLeftSpeed(int left){
  speedmotorB=left;
}

void Shieldbot::setMaxRightSpeed(int right){
  speedmotorA=right;
}

int Shieldbot::readS1(){
  return digitalRead(finder1);
}

int Shieldbot::readS2(){
  return digitalRead(finder2);
}

int Shieldbot::readS3(){
  return digitalRead(finder3);
}

int Shieldbot::readS4(){
  return digitalRead(finder4);
}

int Shieldbot::readS5(){
  return digitalRead(finder5);
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
    //Serial.print("forward right: ");
    //Serial.println(actualSpeed);
    analogWrite(speedPinRight,actualSpeed);
    digitalWrite(right1,HIGH);
    digitalWrite(right2,LOW);//turn right motor clockwise
  }else if(mag == 0){ //neutral
    Serial.println("nuetral right");
	stopRight();
  }else { //meaning backwards
    float ratio = (float)abs(mag)/128;
    actualSpeed = ratio*speedmotorA;
    //Serial.print("backward right: ");
    //Serial.println(actualSpeed);
    analogWrite(speedPinRight,actualSpeed);
    digitalWrite(right1,LOW);
    digitalWrite(right2,HIGH);//turn right motor counterclockwise
  }
}

//TODO shouldnt these share one function and just input the differences?
void Shieldbot::leftMotor(char mag){
  int actualSpeed = 0;  
  if(mag >0){ //forward
    float ratio = (float)(mag)/128;
    actualSpeed = (int)(ratio*speedmotorB); //define your speed based on global speed
    //Serial.print("forward left: ");
    //Serial.println(actualSpeed);
    analogWrite(speedPinLeft,actualSpeed);
    digitalWrite(left1,HIGH);
    digitalWrite(left2,LOW);//turn left motor counter-clockwise
  }else if(mag == 0){ //neutral
    Serial.println("nuetral left");
	stopLeft();
  }else { //meaning backwards
    float ratio = (float)abs(mag)/128;
    actualSpeed = ratio*speedmotorB;
    //Serial.print("backward left: ");
    //Serial.println(actualSpeed);
    analogWrite(speedPinLeft,actualSpeed);
    digitalWrite(left1,LOW);
    digitalWrite(left2,HIGH);//turn left motor counterclockwise
  }
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
  stopLeft();
  stopRight();
}

void Shieldbot::stopLeft(){
  analogWrite(speedPinLeft,0);
}

void Shieldbot::stopRight(){
  analogWrite(speedPinRight,0);
}

//may be dangerous to motor if reverse current into hbridge exceeds 2A
void Shieldbot::fastStopLeft(){
  digitalWrite(left1,LOW);
  digitalWrite(left2,LOW);//turn DC Motor B move clockwise
}

//may be dangerous to motor if reverse current into hbridge exceeds 2A
void Shieldbot::fastStopRight(){
  digitalWrite(right1,LOW);
  digitalWrite(right2,LOW);//turn DC Motor A move anticlockwise
}

//may be dangerous to motor if reverse current into hbridge exceeds 2A
void Shieldbot::fastStop(){
	fastStopRight();
	fastStopLeft();
}