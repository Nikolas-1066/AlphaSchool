#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <Servo.h>


PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);
Servo servo;
  
void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello!");

  nfc.begin();
  
  servo.attach(6);

  
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); 
  }
  
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  nfc.setPassiveActivationRetries(0xFF);
  

  nfc.SAMConfig();
    
  Serial.println("Waiting for an ISO14443A card");
}

void loop(void) {
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  
  uint8_t uidLength;                        
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  
  if (success) {
    Serial.println("Found a card!");
    Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("UID Value: ");
    String hex_value = "";
    for (uint8_t i=0; i < uidLength; i++) 
    {
      Serial.print(" 0x");Serial.print(uid[i], HEX);       
      //Serial.print(" ");Serial.print(uid[i], HEX);       
      hex_value += (String)uid[i];
    }

    Serial.println(", value="+hex_value);

    if(hex_value == "3724536195") {
      Serial.println("This is Key Tag. ");
       servo.write(90); // Поворачиваем серву на угол 90 градусов(Отпираем какой либо механизм: задвижку, поворациваем ключ и т.д.)
    }
    else if(hex_value == "147175225") {
      Serial.println("This is Card Tag. ");
      servo.write(0);
    }
    else if(hex_value == "81199945") {
      Serial.println("This is Phone Tag. ");
    }
    else
      Serial.println("I don't know.");

    Serial.println("");
    delay(1000);
  }
  else
  {
    Serial.println("Waiting for a card...");
  }

}
