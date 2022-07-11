
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

void loop(){
    int rawData = analogRead(A0);
    float vcc = 5.0;
    float voltage = rawData * (vcc / 1024.0);
    float temperature = voltage * 100;
//  float millivoltage = (rawData/1024.0)*3300;
//    float temperature = millivoltage/10;
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");
    delay(500);
}   
