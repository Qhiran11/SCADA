#include <Servo.h>
Servo servoMotor1;
Servo servoMotor2;


void setupServo(int s1, int s2){
    servoMotor1.attach(s1);
    servoMotor2.attach(s2); 
  }



void servo(int perintah, int derajat) {  
  if (perintah == 1){
    servoMotor1.write(derajat);
  }
  if (perintah == 2){
    servoMotor2.write(derajat);
  }
  
}