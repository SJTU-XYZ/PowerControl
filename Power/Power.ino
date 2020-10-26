#include <Arduino.h>

class BlueTooth {
private:
    int value,leftvalue;
    int valuecontrol[5];

    void getValue() { 
      value = Serial.read()-16;
      leftvalue = value;
      for (int i=0; i < 5; i++) {
        valuecontrol[i] = leftvalue%2;
        leftvalue = value/2;
      }
    }

public:
    void Reset();
    void Control();
};

int Yuba=7,Fountain=8,Power2=9,Power3=10,Power4=11;

void BlueTooth::Reset() {
    Serial.begin(9600);
    pinMode(Yuba,OUTPUT);
    pinMode(Fountain,OUTPUT);
    pinMode(Power2,OUTPUT);
    pinMode(Power3,OUTPUT);
    pinMode(Power4,OUTPUT);
}

void BlueTooth::Control() {
    getValue();
    digitalWrite(Yuba,valuecontrol[0]);
    digitalWrite(Fountain,valuecontrol[1]);
    digitalWrite(Power2,valuecontrol[2]);
    digitalWrite(Power3,valuecontrol[3]);
    digitalWrite(Power4,valuecontrol[4]);
}

BlueTooth blueTooth;
int init_count = 0;
bool start_flag = false;

void setup() {
    blueTooth.Reset();
    init_count = 0;
}

void loop() {
    if(init_count <= 12) init_count++;

    int value = Serial.read();
    Serial.println(value);
    delay(100);

    if(init_count >= 12) blueTooth.Control();
}
