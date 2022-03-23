#include <virtuabotixRTC.h>
virtuabotixRTC myRTC(A0, A1, A2);

#include <Wire.h>                             // библиотека для устройств I2C 
#include <LiquidCrystal_I2C.h>       // подключаем библиотеку для дисплея
LiquidCrystal_I2C LCD(0x3F,16,2);  // присваиваем имя дисплею

void setup() {
   delay(300);
   LCD.init();
   LCD.backlight();  // включение подсветки дисплея
  // seconds, minutes, hours, day of the week, day of the month, month, year
   myRTC.setDS1302Time(30, 50, 18, 6, 12, 03, 2022);
}

void loop() {
   // если прошла 1 секунда выводим время на дисплей
   if (millis() % 1000 == 0) {
      myRTC.updateTime();
      LCD.setCursor(2,0);
      LCD.print(myRTC.dayofmonth);
      LCD.print("/");
      LCD.print(myRTC.month);
      LCD.print("/");
      LCD.print(myRTC.year);
      LCD.setCursor(12,0);
      LCD.print("Hi!");
      LCD.setCursor(4,1);
      LCD.print(myRTC.hours);
      LCD.print(":");
      LCD.print(myRTC.minutes);
      LCD.print(":");
      LCD.print(myRTC.seconds);
      
      delay(1);
   }
}
