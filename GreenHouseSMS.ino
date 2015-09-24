#include "LGSM.h"

#define WATER_SENSOR A1
const char* contact_no = "0123456798";


void setup() {
  Serial.begin(9600); 
  pinMode(WATER_SENSOR, INPUT);


  Serial.println("Initialize GSM for SMS");
  while (!LSMS.ready()){
      delay(1000);
      Serial.println(".");
  }
  Serial.println("GSM ready for sending SMS");
  
}

void loop() {
        check_water_level();
        delay(20000);
}


void check_water_level(){

    Serial.print("Water Level:");
    int water_level = analogRead(WATER_SENSOR);
    Serial.println(water_level);

    if (water_level > 60){
        //no more water
        send_low_water_SMS();
    }
}

void send_low_water_SMS(){

    LSMS.beginSMS(contact_no);

    LSMS.print("Water tank is running low!");
    if (LSMS.endSMS()){
        Serial.println("SMS successfully sent");
    }
    else{
        Serial.println("SMS failed to send");
    }
}


