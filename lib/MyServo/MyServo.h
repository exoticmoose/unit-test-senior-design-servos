#ifndef MYSERVO_H
#define MYSERVO_H
// ------------------------------------------- MYSERVO_H

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>



extern HardwareSerial Serial;
extern Adafruit_PWMServoDriver servo_pwm;


class MyServo {
	public:

		MyServo(unsigned char id) {
			my_id = id;
			goal_pw = 0;
			next_pw = 0;
			curr_pw = 0;
			Serial.println("Default servo created.");
		}

		void heartbeat();

		void setGoal(unsigned short);
		void calcNext();
		void sendNext();

		unsigned short getGoal();
		unsigned short getNext();
		unsigned short getCurr();

	private:
		unsigned short my_id;

		unsigned short goal_pw;
		unsigned short next_pw;
		unsigned short curr_pw;
};

// ------------------------------------------ \MYSERVO_H
#endif