#include "KitEncoder.h"

/** Constructor
  * @param int slavePin The digital pin to which the slave select line to the encoder counter chip is conncted
  * Assumes that the SPI bus is wired on the default pins
  **/

//#TODO: Move SPI setup to robot instantiation
KitEncoder::KitEncoder(int slavePin) {
	_slavePin = slavePin;
}

/**
 * Performs initial setup of the encoder, using a 4-byte counter, in quadrature mode, MSB transferred first, using SPI Mode 0
 **/
void KitEncoder::initialize() {
  pinMode(_slavePin, OUTPUT);
  digitalWrite(_slavePin,HIGH);
  spiSettings = SPISettings(40000, MSBFIRST, SPI_MODE0);
  SPI.begin();
  SPI.beginTransaction(spiSettings); 


  digitalWrite(_slavePin,LOW);        // Begin SPI conversation
  SPI.transfer(0x88);                       // Write to MDR0
  SPI.transfer(0x03);                       // Configure to 4 byte mode
  digitalWrite(_slavePin,HIGH);       // Terminate SPI conversation 
  SPI.endTransaction();
  clearEncoderCount();
}

/**
 * Zeros the current encoder count by writing zeros to the count register of the counter IC
 **/
void KitEncoder::clearEncoderCount() {
  SPI.beginTransaction(spiSettings);
  // Set encoder1's data register to 0
  digitalWrite(_slavePin,LOW);      // Begin SPI conversation  
  // Write to DTR
  SPI.transfer(0x98);    
  // Load data
  SPI.transfer(0x00);  // Highest order byte
  SPI.transfer(0x00);           
  SPI.transfer(0x00);           
  SPI.transfer(0x00);  // lowest order byte
  digitalWrite(_slavePin,HIGH);     // Terminate SPI conversation 
  
  delayMicroseconds(100);  // provides some breathing room between SPI conversations
  
  // Set encoder1's current data register to center
  digitalWrite(_slavePin,LOW);      // Begin SPI conversation  
  SPI.transfer(0xE0);    
  digitalWrite(_slavePin,HIGH);     // Terminate SPI conversation    
  SPI.endTransaction();
}

/**
 * Returns the current count of the encoder
 * @return long The current count of this encoder
**/
long KitEncoder::getCount() {
  
  SPI.beginTransaction(spiSettings);
  digitalWrite(_slavePin,LOW);      // Begin SPI conversation
  SPI.transfer(0x60);                     // Request count
  count_1 = SPI.transfer(0x00);           // Read highest order byte
  count_2 = SPI.transfer(0x00);          
  count_3 = SPI.transfer(0x00);         
  count_4 = SPI.transfer(0x00);           // Read lowest order byte
  digitalWrite(_slavePin,HIGH);     // Terminate SPI conversation 
  SPI.endTransaction();
  
  // Calculate encoder count
  count_value = (count_1 << 8) + count_2;
  count_value = (count_value << 8) + count_3;
  count_value = (count_value << 8) + count_4;
  
  return count_value;
}