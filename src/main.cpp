/*
	Unit testing for servo motors

	Hardware: 	- atmega328p / Arduino Uno R3
				- Keyestudio 16 Channel PWM shield (Adafruit headers)
				- 4qty hobby rc high torque servos

*/
#include <proj_parms.h>

// Default Libraries
#include <Arduino.h>
#include <Wire.h>

// Borrowed Libraries
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include <MPU6050.cpp>
#include <I2Cdev.cpp>

// Developed Libraries
#include <MyServo.h>

long tmp_time = 0;

Adafruit_PWMServoDriver servo_pwm = Adafruit_PWMServoDriver();

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;

float angle_x = 0;
float angle_y = 0;

#define OUTPUT_READABLE_ACCELGYRO

MyServo servo_fl = MyServo(0, 2440, 1440, 90, 0); // 0 = 
MyServo servo_fr = MyServo(2, 2440, 1440, 90, 1); 
MyServo servo_rl = MyServo(4, 2250, 1250, 90, 0); 
MyServo servo_rr = MyServo(6, 2250, 1250, 90, 1); 

void serialEvent() {
	Serial.print("SE - ");
	long addr = Serial.parseInt();
	long angle= Serial.parseInt();


	Serial.print("got: ");
	Serial.print(addr); Serial.print(" @ ");
	Serial.println(angle);

	switch (addr) {
		case 0:
			servo_fl.setGoalAngle(angle);
			break;
		case 2:
			servo_fr.setGoalAngle(angle);
			break;
		case 4:
			servo_rl.setGoalAngle(angle);
			break;
		case 6:
			servo_rr.setGoalAngle(angle);
			break;

		case -1:
			servo_fl.setGoalAngle(angle);
			servo_rl.setGoalAngle(angle);
			servo_fr.setGoalAngle(angle);
			servo_rr.setGoalAngle(angle);
			break;
	}
}

void sendServoCommands() {
	//

}



void setup() {
	Serial.begin(500000);
	Serial.println("Testing Stuff!"); Serial.println("");

	Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
	servo_pwm.begin();
	servo_pwm.setPWMFreq(250);  // This is the maximum PWM frequency


	// verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
		


    Serial.print("\n");
	// save I2C bitrate
	//uint8_t twbrbackup = TWBR;
	// must be changed after calling Wire.begin() (inside pwm.begin())
	//TWBR = 12; // upgrade to 400KHz!
    
}

void loop() {
  // Drive each PWM in a 'wave'
	delay(10);

	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);


#ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        // Serial.print("a/g:\t");
        // Serial.print(ax); Serial.print("\t");
        // Serial.print(ay); Serial.print("\t");
        // Serial.print(az); Serial.print("\t");
        // Serial.print(gx); Serial.print("\t");
        // Serial.print(gy); Serial.print("\t");
        // Serial.println(gz); Serial.println("--\t--");
#endif
	
	angle_x = abs(ax / (float)20000 * 90);
	//erial.println(angle_x);
	angle_y = abs(ay / (float)20000 * 90);
	//Serial.println(angle_y);

	// servo_fl.setGoalAngle(angle_x);
	// servo_rl.setGoalAngle(angle_y);
	// servo_fr.setGoalAngle(angle_x);
	// servo_rr.setGoalAngle(angle_y);


	servo_fl.calcNext();
	servo_rl.calcNext();
	servo_fr.calcNext();
	servo_rr.calcNext();


	servo_fl.sendNext();
	servo_rl.sendNext();
	servo_fr.sendNext();
	servo_rr.sendNext();
  
  //Serial.println("");
	


	
}