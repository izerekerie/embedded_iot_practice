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
//    float vcc = 3.3;
//    float millivolts = rawData * (vcc / 1024.0);
//    float temperature = millivolts * 100;
//    float offset = 3.0;
//    temperature = temperature-offset;
      if (temperature == 35){
    digitalWrite(greenPin,LOW);
    digitalWrite(redPin,HIGH);
    digitalWrite(buzzer.HIGH);
    delay(500);
    digitalWrite(buzzer.HIGH);
   String host = "insecure.benax.rw";
  String path = "/iot/";
  int port = 80;
 // String request = "POST /insecure.benax.rw/iot/?device=RCA0125BGE&temperature="+(String)temperature+" HTTP/1.1";
  String mData="";
  String device = "kerie";
  mData = "device="+device+"&distance="+(String)temperatire;
  sendData(port, host,path,mData); 
      }
     else {
    digitalWrite(greenPin,HIGH);
    digitalWrite(redPin,LOW);
    digitalWrite(buzzer.LOW);  
       }
    lcd.clear();
    lcd.setCursor(0,1);   
    lcd.print(temperature);
    delay(1000);
}

void sendData(const int httpPort, const char* host,const char* filepath , String data){
  wifiClient.connect(host, httpPort); 
  wifiClient.println("POST "+(String)filepath+" HTTP/1.1");
  wifiClient.println("Host: " + (String)host);
  wifiClient.println("User-Agent: ESP8266/1.0");
  wifiClient.println("Content-Type: application/x-www-form-urlencoded");
  wifiClient.println("Content-Length: " +(String)data.length());
  wifiClient.println();
  wifiClient.print(data);
  Serial.println("Response: " + wifiClient.readStringUntil('\n'));

}
