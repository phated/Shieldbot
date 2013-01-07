#include <Shieldbot.h>

Shieldbot shieldbot = Shieldbot();

void setup(){
  Serial.begin(9600);
  shieldbot.setMaxSpeed(255);//255 is max
}

void loop(){
  leftSquare();  
}

void leftSquare(){
  shieldbot.forward();
  delay(750);
  shieldbot.left(255);
  delay(400);
}

void infinity(){
  leftCircle();
  delay(3500);
  rightCircle();
  delay(3500);
}

void leftCircle(){
  shieldbot.left(100);
}

void rightCircle(){
  shieldbot.right(100);
}
