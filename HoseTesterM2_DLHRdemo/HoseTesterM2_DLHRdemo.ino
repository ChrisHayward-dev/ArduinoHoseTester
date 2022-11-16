// HoseTester M2
/* Pin definitions */
#include <SPI.h>
#include <AllSensors_DLHR.h>

#define GREENLED  8
#define REDLED    13
#define RELAY_B   6   //valve control
#define RELAY_A   9   //pump control (PWM)
#define DLHRB_CS  10
#define DLHRB_EOC 11
#define DLHRA_CS  12
#define DLHRA_EOC 5  //patch on PCB to move 13 to 5

enum AllSensors_DLHR::MeasurementType dlhrAverage;
AllSensors_SPI_DLHR_L01D_8 pressureA(DLHRA_CS);
AllSensors_SPI_DLHR_L01D_8 pressureB(DLHRB_CS);

void setup() {
  Serial.begin(9600);
  while(!Serial) delay(100);
  Serial.println("Starting HoseTesterM2 DLHR demo");
  delay(1000);
  
  Serial.println("Setting pinMode");
  pinMode(RELAY_A,OUTPUT);
  pinMode(RELAY_B,OUTPUT);
  pinMode(GREENLED,OUTPUT);
  digitalWrite(RELAY_A,LOW);
  digitalWrite(RELAY_B,LOW);

  pinMode(DLHRA_EOC,INPUT_PULLUP);
  pinMode(DLHRB_EOC,INPUT_PULLUP);
  pinMode(DLHRA_CS,OUTPUT);
  digitalWrite(DLHRA_CS,HIGH);
  pinMode(DLHRB_CS,OUTPUT);
  digitalWrite(DLHRB_CS,HIGH);
  Serial.println("PinMode Complete"); 
  Serial.println("Checking EOCs");
  if(digitalRead(DLHRA_EOC)==LOW) Serial.println("DLHR A is low");
  else Serial.println("DLHR A is high");
  if(digitalRead(DLHRB_EOC)==LOW) Serial.println("DLHR B is low");
  else Serial.println("DLHR B is high");

  Serial.println("Setting up DLHR SPI mode sensors");
  dlhrAverage = AllSensors_DLHR::MeasurementType::AVERAGE16;
  pressureA.setPressureUnit(AllSensors_DLHR::PressureUnit::PASCAL);
  pressureB.setPressureUnit(AllSensors_DLHR::PressureUnit::PASCAL);
}

void loop() {
  pressureA.startMeasurement();
  pressureA.readData(true);
  pressureB.startMeasurement();
  pressureB.readData(true);

  Serial.print("P1: ");
  Serial.print(pressureA.pressure);
  Serial.print(" P2: ");
  Serial.print(pressureB.pressure);
  Serial.print(" T1: ");
  Serial.print(pressureA.temperature);
  Serial.print(" T2: ");
  Serial.println(pressureB.temperature);
  delay(100);
}
