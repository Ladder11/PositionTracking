#ifndef KITENCODER
#define KITENCODER
#include <SPI.h>
#include <Arduino.h>

#define MOSI_pin 51
#define MISO_pin 50
#define SCLK_pin 52

class KitEncoder {
public:
  KitEncoder(int slavePin);
  void initialize();
  long getCount();
  void clearEncoderCount();
private:
  char _slavePin;
  SPISettings spiSettings;
  unsigned int count_1, count_2, count_3, count_4;
  long count_value;  
};



#endif