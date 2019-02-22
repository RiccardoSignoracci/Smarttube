#ifndef __RECEIVER__
#define __RECEIVER__

#include "Element.h"

class Receiver : public Element{
  public:
    Receiver(int pin);
    virtual int getValue();
};

#endif
