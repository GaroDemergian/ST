
// Solar Tracker
// This code is written mainly as a school project for simulating a solar
// tracking program using Arduino uno. The main simulation environment used is Tinkercad.
// Dont forget to change file extension to .ino before using it.


#include <Servo.h> // include Servo library

// 180 degrees horizontal MAX
Servo horizontal; // horizontal servo
int servoh = 180; // 180 rotation degrees available

// 90 degrees is the servos starting position
// rotation between 0 and 180 degrees
int servohLimitHigh = 180;
int servohLimitLow = 0;

// 120 degrees vertical MAX
Servo vertical;   // vertical servo
int servov = 120; // 120 rotation degrees available

// 90 degrees is the servos starting position
// rotation between 30 and 150 degrees
int servovLimitHigh = 150;
int servovLimitLow = 30;

// Lightsensors pin connections
// name  = analogpin;
int bottom = A2; // - Bottom sensor    <--- BDG
int top = A3;	// - Upper sensor
int left = A0;   // - Left side sensor
int right = A1;  // - Right side sensor

int dtime = 10; //delay time. used to give time to servos to rotate
int tol = 50;   //tolerance

void setup()
{
	Serial.begin(9600);

	// servo connections
	// name.attacht(pin);
	horizontal.attach(5);
	vertical.attach(6);

	//starting servos at 90 degrees
	horizontal.write(90);
	vertical.write(90);
	delay(2000);
}

void loop()
{
	//reading sensors values
	int up = analogRead(top);
	int down = analogRead(bottom);
	int LEFT = analogRead(left);
	int RIGHT = analogRead(right);

	int dvert = up - down;	 // check the diffirence of up and down
	int dhoriz = LEFT - RIGHT; // check the diffirence og left and rigt

	//checking vertical sensors and writing to vertical servo
	if (-1 * tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
	{
		if (up > down)
		{
			servov = ++servov;
			if (servov > servovLimitHigh)
			{
				servov = servovLimitHigh;
			}
		}
		else if (up < down)
		{
			servov = --servov;
			if (servov < servovLimitLow)
			{
				servov = servovLimitLow;
			}
		}
		vertical.write(servov);
	}

	//checking horizontal sensorns and writing to horizontal servo
	if (-1 * tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
	{
		if (LEFT > RIGHT)
		{
			servoh = --servoh;
			if (servoh < servohLimitLow)
			{
				servoh = servohLimitLow;
			}
		}
		else if (LEFT < RIGHT)
		{
			servoh = ++servoh;
			if (servoh > servohLimitHigh)
			{
				servoh = servohLimitHigh;
			}
		}
		else if (LEFT = RIGHT)
		{
			// nothing
		}
		horizontal.write(servoh);
	}
	delay(dtime);
}
