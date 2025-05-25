#include <Servo.h>

// Servo objects and limits
Servo servohori; 
int servoh = 0; 
int servohLimitHigh = 180; 
int servohLimitLow = 0;   

Servo servoverti; 
int servov = 0; 
int servovLimitHigh = 180;
int servovLimitLow = 0; 

// LDR pin definitions
int ldrtopr = A1;
int ldrtopl = A2;
int ldrbotr = A0;
int ldrbotl = A3;

void setup() 
{
  servohori.attach(6);
  servohori.write(60);
  
  servoverti.attach(5); 
  servoverti.write(0);

  Serial.begin(9600);
  delay(2000); // Allow setup time
}

void loop()
{
  // Read LDR values
  int topl = analogRead(ldrtopl); 
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl); 
  int botr = analogRead(ldrbotr);

  // Calculate voltages
  float topl_v = 5.0 - topl * (5.0 / 1023.0);
  float topr_v = 5.0 - topr * (5.0 / 1023.0);
  float botl_v = 5.0 - botl * (5.0 / 1023.0);
  float botr_v = 5.0 - botr * (5.0 / 1023.0);

  // Average voltages
  float avgtop = (topl_v + topr_v) / 2.0;
  float avgbot = (botl_v + botr_v) / 2.0;
  float avgleft = (topl_v + botl_v) / 2.0;
  float avgright = (topr_v + botr_v) / 2.0;

  // Read current positions
  servoh = servohori.read();
  servov = servoverti.read();

  // Movement threshold
  float threshold = 0.05;

  // Vertical control
  if ((avgtop - avgbot) > threshold) {
    servov -= 2;
    if (servov < servovLimitLow) servov = servovLimitLow;
    servoverti.write(servov);
  }
  else if ((avgbot - avgtop) > threshold) {
    servov += 2;
    if (servov > servovLimitHigh) servov = servovLimitHigh;
    servoverti.write(servov);
  }

  // Horizontal control
  if ((avgleft - avgright) > threshold) {
    servoh -= 2;
    if (servoh < servohLimitLow) servoh = servohLimitLow;
    servohori.write(servoh);
  }
  else if ((avgright - avgleft) > threshold) {
    servoh += 2;
    if (servoh > servohLimitHigh) servoh = servohLimitHigh;
    servohori.write(servoh);
  }

  // Print only once per second
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint >= 1000) {
    Serial.print("TopL: "); Serial.print(topl_v, 2); Serial.print("V  ");
    Serial.print("TopR: "); Serial.print(topr_v, 2); Serial.print("V  ");
    Serial.print("BotL: "); Serial.print(botl_v, 2); Serial.print("V  ");
    Serial.print("BotR: "); Serial.println(botr_v, 2);
    lastPrint = millis();
  }

  delay(10); // Small delay for smoother transitions
}
