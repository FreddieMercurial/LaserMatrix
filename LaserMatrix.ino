
#include <SPI.h>


// SparkFun Pro Micro
// https://www.sparkfun.com/products/12640
const int RXLED = 17;  // The RX LED has a defined Arduino pin

// SparkFun 74HC595 breakout 
// https://www.sparkfun.com/products/10680
const int MATRIX_LATCH_PIN = 10;
const int MATRIX_CLOCK_PIN = 15;
const int MATRIX_SER_PIN = 16;
const int MATRIX_ENABLE_PIN = 18;
const int MATRIX_RESET_PIN = 19;
const long SPI_RATE = 14000000;
const long SPI_DIVIDER = SPI_CLOCK_DIV2;
const byte SPI_ORDER = MSBFIRST;
const byte SPI_MODE = SPI_MODE0;

// Mode      | Clock Polarity (CPOL) | Clock Phase (CPHA) | Output Edge | Data Capture
// ----------+-----------------------+--------------------+-------------+--------------
// SPI_MODE0 | 0                     | 0                  | Falling     | Rising
// SPI_MODE1 | 0                     | 1                  | Rising      | Falling
// SPI_MODE2 | 1                     | 0                  | Rising      | Falling
// SPI_MODE3 | 1                     | 1                  | Falling     | Rising

bool RxLedOn = false;

void setup() {
  pinMode(RXLED, OUTPUT);
  setRxLed(true);

  pinMode(MATRIX_LATCH_PIN, OUTPUT);
  pinMode(MATRIX_CLOCK_PIN, OUTPUT);
  pinMode(MATRIX_SER_PIN, OUTPUT);
  pinMode(MATRIX_ENABLE_PIN, OUTPUT);
  pinMode(MATRIX_RESET_PIN, OUTPUT);
  digitalWrite(MATRIX_ENABLE_PIN, false); // enable LOW
  digitalWrite(MATRIX_RESET_PIN, true); // reset LOW  

  SPI.begin();
  SPI.setBitOrder(SPI_ORDER);
  SPI.setDataMode(SPI_MODE);
  SPI.setClockDivider(SPI_DIVIDER);  
  
  digitalWrite(MATRIX_LATCH_PIN, LOW);
  delay(500);
  SPI.beginTransaction(SPISettings(SPI_RATE, SPI_ORDER, SPI_MODE));
  SPI.transfer(B01010101);
  delay(500);
  SPI.endTransaction();
  digitalWrite(MATRIX_LATCH_PIN, HIGH);
}

void setRxLed(bool power)
{
  digitalWrite(RXLED, power);
  RxLedOn = power;
}

void loop() {
  delay(500);  
  setRxLed(!RxLedOn);
}
