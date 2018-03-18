#include<SoftwareSerial.h>
#include<ArduinoJson.h>
#define TRIGGER_PIN 7
#define ECHO_PIN 6
SoftwareSerial serial(2,3);
StaticJsonBuffer<200> jsonBuffer;
int MAX = 10;
void setup(){
  Serial.begin(9600);
  serial.begin(9600);
  pinMode(TRIGGER_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);  
}

void loop(){
  digitalWrite(TRIGGER_PIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN,LOW);
  int d = pulseIn(ECHO_PIN,HIGH)/58;
  if(d > 0 && d < MAX){
    sendData(d);
   Serial.println(d);
  }
  delay(100);
}
void sendData(int dist){
  JsonObject& obj = jsonBuffer.createObject();
  obj["access"] = true;
  obj["distance"] = dist;
char jsonChar[100];
obj.printTo((char*)jsonChar, obj.measureLength() + 1);
  serial.write(jsonChar);
}



