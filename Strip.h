//
// Strip -- Base class for LED strips
//
//


#ifndef Strip_h
#define Strip_h

#include <inttypes.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;


class Strip
{

 protected:
    
    uint16_t numLEDs;

    
 public:

    virtual void setLEDcolor(uint16_t n, color_t color) = 0;
    virtual void getLEDcolor(uint16_t n, color_t* color) = 0;

    virtual void update() = 0;

    virtual void blank() = 0;
    virtual void sleep() = 0;
    virtual void wakeup() = 0;
    
    uint16_t getNumLEDs() { return numLEDs; }
};

#endif
