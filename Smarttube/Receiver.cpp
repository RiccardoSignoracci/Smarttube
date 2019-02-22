#include "Receiver.h"
#include <FS.h>

Receiver::Receiver(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);
}

int Receiver::getValue(){
  return analogRead(this->pin);
}
