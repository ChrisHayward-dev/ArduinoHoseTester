// HoseTester M2
/* Pin definitions */
#include <SPI.h>
#include  <AllSensors_DLHR.h>

#define GREENLED  8
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
  //while(!Serial) delay(100);
  Serial.println("Starting HoseTesterM2");

  pinMode(RELAY_A, OUTPUT);
  pinMode(RELAY_B, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  digitalWrite(RELAY_A, LOW);
  digitalWrite(RELAY_B, LOW);

  pinMode(DLHRA_EOC, INPUT_PULLUP);
  pinMode(DLHRB_EOC, INPUT_PULLUP);
  pinMode(DLHRA_CS, OUTPUT);
  pinMode(DLHRB_CS, OUTPUT);
  Serial.println("PinMode Complete");
  Serial.println("Checking EOCs");
  if (digitalRead(DLHRA_EOC) == LOW) Serial.println("DLHR A is low");
  else Serial.println("DLHR A is high");
  if (digitalRead(DLHRB_EOC) == LOW) Serial.println("DLHR B is low");
  else Serial.println("DLHR B is high");
  Serial.println("Setting up DLHR SPI mode sensors");
  dlhrAverage = AllSensors_DLHR::MeasurementType::AVERAGE16;
  pressureA.setPressureUnit(AllSensors_DLHR::PressureUnit::PASCAL);
  pressureB.setPressureUnit(AllSensors_DLHR::PressureUnit::PASCAL);

}

float pa = 0;
float pb = 0;
float zeroA = 0;
float zeroB = 0;
void takePressures(bool state) {
  for (int nsamp = 0; nsamp < 300; nsamp++) {
    pressureA.startMeasurement();
    pressureB.startMeasurement();
    pressureA.readData(true);
    pressureB.readData(true);
    pa = pressureA.pressure;
    pb = pressureB.pressure;
//    Serial.print("P1: ");
//    Serial.print(pa - zeroA);
//    Serial.print(" P2: ");
//    Serial.print(pb - zeroB);
//    Serial.print(" Ratio ");
//    if (!state) {
//      Serial.print(" 0.0");
//    } else {
//      Serial.print(100 * (pa - zeroA) / (pb - zeroB));
//    }
//    Serial.println();
    delay(10);
  }
}

void loop() {
  static int16_t pumpPower = 0;
  float ratio;
  Serial.print("Pump Power cycle");
  for (int pwm = 64; pwm < 255; pwm += 16) {
    analogWrite(RELAY_A, 0);
    digitalWrite(RELAY_B, LOW);
    takePressures(false);
    zeroA = pa;
    zeroB = pb;
    Serial.print("Pump Power:");
    Serial.print(pwm);
    analogWrite(RELAY_A, pwm);
    digitalWrite(RELAY_B, HIGH);
    takePressures(true);
    Serial.print(" Ratio: ");
    Serial.print(100 * (pa - zeroA) / (pb - zeroB));
    Serial.println();
  }
}
