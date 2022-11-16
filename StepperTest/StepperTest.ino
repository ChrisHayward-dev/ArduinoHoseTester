// Include the Arduino Stepper Library
#include <Stepper.h>

// Number of steps per output rotation
const int stepsPerRevolution = 200;

// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 6, 9, 10, 11);
float nrot = 10;

void setup()
{
	// set the speed at 60 rpm:
	myStepper.setSpeed(120);
	// initialize the serial port:
	Serial.begin(9600);
//   while(!Serial) {
//     delay(100);
//   }
}

void loop() 
{
//  for(int k=0;k<20;k++) {
//    myStepper.step(11);
//    delay(100);
//    myStepper.step(-12);
//    delay(150);
//  }

	// step one revolution in one direction:
	Serial.println("clockwise");
	myStepper.step(stepsPerRevolution*nrot);
	delay(100);

	// step one revolution in the other direction:
	Serial.println("counterclockwise");
	myStepper.step(-stepsPerRevolution*nrot);
	delay(100);
}
