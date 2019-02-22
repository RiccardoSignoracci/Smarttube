#ifndef __TRANSMITTER__
#define __TRANSMITTER__

#include "Element.h"

class Transmitter : public Element{
  public:
    Transmitter(int pin);
    virtual void switchON();
    virtual void switchOFF();
};

#endif
