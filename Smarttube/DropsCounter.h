#ifndef __DROPS_COUNTER__
#define __DROPS_COUNTER__

#include "Receiver.h"
#include "Transmitter.h"

class DropsCounter{
  public:
    DropsCounter();
    virtual bool isDetected() = 0;
   private:
    Receiver* receiver;
    Transmitter* transmitter;
};

#endif
