#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
WiFiClient wifiClient;

int redPin = 13; 
int greenPin = 12;//GPIO 13 corresponds to pin D7. You can check the pinout.
int buzzerPin=16;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup(){
WiFi.begin("RCA-WiFi", "rca@2019");
lcd.begin();
lcd.backlight();
lcd.println("temperature");
// initialize ledPin as an output.
Serial.begin(9600);
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(buzzer,OUTPUT);
lcd.clear();
}
// the loop function runs over and over again forever
void loop(){

    int rawData = analogRead(A0);
    float vcc = 5.0;
    float voltage = rawData * (vcc / 1024.0);
    float temperature = voltage * 100;

      if (temperature == 35){
    digitalWrite(greenPin,LOW);
    digitalWrite(redPin,HIGH);
    digitalWrite(buzzer.HIGH);
    delay(500);
    digitalWrite(buzzer.HIGH);
    lcd.setCursor(0,1);   
    lcd.print(temperature);
      }
     else {
    digitalWrite(greenPin,HIGH);
    digitalWrite(redPin,LOW);
    digitalWrite(buzzer.LOW);  
       }
  String host = "insecure.benax.rw";
  String path = "/iot/";
  int port = 8000;
  String request = "POST /insecure.benax.rw/iot/?device=RCA0125BGE&temperature="+(String)temperature+" HTTP/1.1";
  wifiClient.connect(host, port);
  wifiClient.println(request);
  wifiClient.println("Host: "+host);
  wifiClient.println("User-Agent: ESP8266/1.0");
  wifiClient.println("C: ESP8266/1.0");
  wifiClient.println();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("*C");
  Serial.println("Response: "+wifiClient.readStringUntil('\n'));
  delay(1000);
}
