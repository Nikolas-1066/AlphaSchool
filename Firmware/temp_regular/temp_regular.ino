#include "DHT.h"
#define DHTPIN 2 
DHT dht(DHTPIN, DHT22);
#include <Servo.h>
Servo servo; 
void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(13, OUTPUT); 
  servo.attach(6);
  servo.write(0);
}
void loop() {
  delay(2000);
  float t = dht.readTemperature(); 
  if (isnan(h) || isnan(t)) { 
    Serial.println("Ошибка считывания");
    return;
  }
  Serial.print("Температура: ");
  Serial.print(t);
  Serial.println(" *C ");
  if (t < 19){
    digitalWrite(13, HIGH);
  }
  if (t > 23) {
    servo.write(90); 
  }
  
}
