/*
	Unit testing for servo motors

	Hardware: 	- atmega328p / Arduino Uno R3
				- Keyestudio 16 Channel PWM shield (Adafruit headers)
				- 4qty hobby rc high torque servos

*/
#include <proj_parms.h>

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <MyServo.h>


Adafruit_PWMServoDriver servo_pwm = Adafruit_PWMServoDriver();

MyServo servo_fl = MyServo(0);


void serialEvent() {
	Serial.print("SE - ");
	long tmp = Serial.parseInt();
	Serial.print("got: ");
	Serial.println(tmp);

	if (tmp == 11) {
		Serial.println(servo_fl.getGoal());
	}
	else if (tmp == 22) {
		Serial.println(servo_fl.getCurr());
	}
	else if (tmp == 33) {
		Serial.println(servo_fl.getNext());
	}
	else if (tmp == 99) {
		servo_fl.calcNext();
	}
	else servo_fl.setGoal(tmp);
}





void setup() {
	Serial.begin(9600);
	Serial.println("Testing Stuff!");

	servo_pwm.begin();
	servo_pwm.setPWMFreq(300);  // This is the maximum PWM frequency
		
	// save I2C bitrate
	//uint8_t twbrbackup = TWBR;
	// must be changed after calling Wire.begin() (inside pwm.begin())
	TWBR = 12; // upgrade to 400KHz!
    
}

void loop() {
  // Drive each PWM in a 'wave'
  delay(500);
  servo_fl.calcNext();
  servo_fl.sendNext();
  
  Serial.println("");
	


	
}