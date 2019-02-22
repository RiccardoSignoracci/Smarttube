#include "Transmitter.h"
#include <FS.h>

Transmitter::Transmitter(int pin){
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void Transmitter::switchON(){
  digitalWrite(this->pin, HIGH);
  Serial.print("Led On");
}

void Transmitter::switchOFF(){
  digitalWrite(this->pin, LOW);
  Serial.print("Led Off");
}
