#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

#define BLYNK_TEMPLATE_ID "TMPL3weGq7d1e"
#define BLYNK_TEMPLATE_NAME "Box automation with iot"
#define BLYNK_AUTH_TOKEN "f6JKDqVQpMdckOqsYLqUXtbogkDw0BKU"
#define ssid "Skytrack9840698842 D"
#define pass "dhamodaran1965"
#define BLYNK_PRINT Serial

int pir=19;
int trig=18;
int echo=5;
float pvalue;
int opvalue=0;
int value=0;
Servo motor;
BlynkTimer timer;

BLYNK_WRITE(V0){
  value=param.asInt();
  if(value){
    Serial.println("OPEN NOW!");
  }
}
void setup() {
  Serial.begin(112500);
  pinMode(pir,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  motor.attach(17,500,2400);
  motor.write(0);
  Blynk.begin(BLYNK_AUTH_TOKEN,ssid,pass,"blynk.cloud",80);
  delay(2000);
  timer.setInterval(250L, person);
  timer.setInterval(250L, opened);
}

void loop() {
    Blynk.run();
    timer.run();
}

void person(){
    digitalWrite(trig,LOW);
    delayMicroseconds(3);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    pvalue=pulseIn(echo,HIGH);
    float distance=(pvalue*0.3443/20);Serial.println(pvalue);
    Serial.println(distance);
    if(distance<10){
      if(value){
        motor.write(150);
      }
      else{
        Blynk.logEvent("person_detected");
        motor.write(0);
      }
    }
}
void opened(){
  opvalue=digitalRead(pir);
  if(opvalue==HIGH){
    if(!(value)){
      Blynk.logEvent("opened");
    }
  }
}
