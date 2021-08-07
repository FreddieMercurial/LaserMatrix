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


bool RxLedOn = false;
byte j = 0;

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
  
}

void setRxLed(bool power)
{
  digitalWrite(RXLED, power);
  RxLedOn = power;
}

void loop() {
  delay(500);  
  setRxLed(!RxLedOn);

  
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(MATRIX_LATCH_PIN, LOW);
    shiftOut(MATRIX_SER_PIN, MATRIX_CLOCK_PIN, LSBFIRST, j);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(MATRIX_LATCH_PIN, HIGH);
    delay(300);
    j = (j + 1) % 256;
}
