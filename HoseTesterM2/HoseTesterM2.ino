// HoseTester M2
/* Pin definitions */

#define GREENLED  8
#define RELAY_B   6
#define RELAY_A   9   //PWM capable
#define DLHRB_CS  D10
#define DLHRB_EOC D11
#define DLHRA_CS  D12
#define DLHRA_EOC D13

void setup() {
  Serial.begin(9600);
 // while(!Serial) delay(100);
  Serial.println("Starting HoseTesterM2");
  
  pinMode(RELAY_A,OUTPUT);
  pinMode(RELAY_B,OUTPUT);
  pinMode(GREENLED,OUTPUT);
  digitalWrite(RELAY_A,LOW);
  digitalWrite(RELAY_B,LOW);
}

void loop() {
  static int32_t maxtime = 5000;
  if(maxtime < 500) maxtime = 5000;
  Serial.print("Cycle   ");
  Serial.print(maxtime);
  Serial.println();
  digitalWrite(RELAY_A,HIGH);
  delay(random(500,maxtime));
  digitalWrite(RELAY_A,LOW);
  delay(random(100,maxtime*2));
  digitalWrite(RELAY_B,HIGH);
  delay(random(100,maxtime*0.5));
  digitalWrite(RELAY_B,LOW);
  maxtime = maxtime*0.99;
}
