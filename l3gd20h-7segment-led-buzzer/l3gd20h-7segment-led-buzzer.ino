#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20_U.h>

Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

#define buzPin 13
#define ledPin 12
#define butPin 11
#define normalEarthQuake 0.23
int k = 1000;
int mode = 1;
void setup(void) {
  pinMode(ledPin, OUTPUT);
  pinMode(buzPin, OUTPUT);
  pinMode(butPin, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  
  gyro.enableAutoRange(true);
  if(!gyro.begin()){
    Serial.println("Check your wiring!");
    // while(1);
  }
  delay(1000);
}

void loop(void) 
{
  
  if(mode==5) mode=1;
  if(true){
    if(mode==1){
      delay(100);
      Serial.print("Mode: ");
      Serial.println(mode);
      l3gd();
      digitalWrite(2,0);
      digitalWrite(3,1);
      digitalWrite(4,1);
      digitalWrite(5,1);
    }
    else  if(mode==2){
      delay(100);
      Serial.print("Mode: ");
      Serial.println(mode);
      digitalWrite(ledPin,0);
      digitalWrite(2,0);
      digitalWrite(3,0);
      digitalWrite(4,1);
      digitalWrite(5,1);
    }
    else if(mode==3){
      delay(100);
      Serial.print("Mode: ");
      Serial.println(mode);
      digitalWrite(ledPin,0);
      digitalWrite(2,0);
      digitalWrite(3,0);
      digitalWrite(4,0);
      digitalWrite(5,1);
    }
    else if(mode==4){
      delay(100);
      Serial.print("Mode: ");
      Serial.println(mode);
      digitalWrite(ledPin,0);
      digitalWrite(2,0);
      digitalWrite(3,0);
      digitalWrite(4,0);
      digitalWrite(5,0);
    }
    
  }
  if(digitalRead(butPin)==0){
    delay(1000);
    mode++;
  }
 
}

void l3gd(){
  float x,y,z;
  sensors_event_t event; 
  gyro.getEvent(&event);
 
  Serial.println("rad/s ");
  if(event.gyro.x<0) x = -1 *event.gyro.x;
  if(event.gyro.y<0) y = -1 *event.gyro.y;
  if(event.gyro.z<0) z = -1 *event.gyro.z;
  Serial.print("X: "); Serial.print(x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(z); Serial.println("  ");

  if(x>2 || y>normalEarthQuake || z>normalEarthQuake){
    digitalWrite(buzPin,1);
    digitalWrite(ledPin,0);
    delay(k);
    digitalWrite(buzPin,0);
    digitalWrite(ledPin,1);
    Serial.println("!!!!!!!!!EarthQuake!!!!!!!!");
  }
  else{
    digitalWrite(buzPin,0);
    digitalWrite(ledPin,1);
    delay(100);
  }
 
  // delay(100);
}