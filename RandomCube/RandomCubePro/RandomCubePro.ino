#include <ShiftRegister74HC595.h>
#include <GyverButton.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#define adc_disable() (ADCSRA &= ~(1<<ADEN))
#define adc_enable()  (ADCSRA |=  (1<<ADEN))

#define DATA_PIN 0                            //Пін підключений до DS входу 74HC595
#define CLOCK_PIN 2                           //Пін підключений до SH_CP входу 74HC595
#define LATCH_PIN 3                           //Пін підключений до ST_CP входу 74HC595
#define NUMBER_OF_REGISTERS 2

#define BUTTON_PIN 1
#define MOTOR_PIN 4

#define LIGHT_PERIOD 3000
#define MY_VCC_CONST 1.05

#define MAX_BRIGHTNESS 250
#define MIN_BRIGHTNESS 0
#define BRIGHTNESS_STEP 10

byte brightness = 200;
unsigned long lightTimer = 0;
byte rndNumbers[2] = {7, 7};
byte displayedNumbers[2];
byte symbols[11] = {B00000000, B00010000, B00101000, B00111000, B10101010, B10111010, B11101110, B11111110, 
                B00000100, B00010100, B01010100}; //76543210

ShiftRegister74HC595 shiftRegister(NUMBER_OF_REGISTERS, DATA_PIN, CLOCK_PIN, LATCH_PIN); 
GButton button(BUTTON_PIN, LOW_PULL, NORM_OPEN);

// один клік ------------------ увімкнення підсвітки
// подвійний клік ------------- перемішування
// потрійний кнопки ----------- відображення заряду
// один клік + утриання ------- яскравість++
// подвійний клік + утримання - яскравість--

ISR(PCINT0_vect){
  button.tick();
}

void setup(){
  cli();                        // заборонити переривання
  GIMSK |= (1 << PCIE);
  PCMSK |= (1 << BUTTON_PIN);
  sei();                        // дозволяємо переривання
  wakeUp();

  button.setDebounce(5);
  //button.setTimeout(1000);
  button.setClickTimeout(500);
  button.setStepTimeout(100);
  
  displayNumbers(rndNumbers);
  motorsVibe(100);
}

void loop(){  
  button.tick();
  
  switch(button.getClicks()){
    case 1: 
      displayNumbers(rndNumbers); 
      break;
    case 2:
      motorsVibe(100);
      delay(100);
      motorsVibe(100);
      displayNumbers(getRandomNumbers());
      break;
    case 3:
      displayVcc();
      break;
  }

  if (button.isStep(1)) {
    lightTimer = millis();
    if(brightness + BRIGHTNESS_STEP <= MAX_BRIGHTNESS) brightness += BRIGHTNESS_STEP;
  }
  else if (button.isStep(2)) {
    lightTimer = millis();
    if(brightness - BRIGHTNESS_STEP >= MIN_BRIGHTNESS) brightness -= BRIGHTNESS_STEP;
  }

  shiftRegisterPWM(brightness);
  
  if(abs(millis() - lightTimer) >= LIGHT_PERIOD) sleep();
}

void shiftRegisterPWM(byte pwm){
  displayArray(displayedNumbers);
  delayMicroseconds(1);
  clearDisplay();
  delayMicroseconds(20000 - pwm * 80);
}

byte* getRandomNumbers(){
  rndNumbers[0] = random(1, 7);
  rndNumbers[1] = random(1, 7);

  return rndNumbers;
}

void motorsVibe(int vibesPeriod){
  digitalWrite(MOTOR_PIN, HIGH);
  delay(vibesPeriod);
  digitalWrite(MOTOR_PIN, LOW);
}

void displayArray(byte array[]){
  uint8_t pinValues[] = {symbols[array[0]], symbols[array[1]]};
  shiftRegister.setAll(pinValues);
  displayedNumbers[0] = array[0];
  displayedNumbers[1] = array[1];
}

void clearDisplay(){
  uint8_t pinValues[] = {symbols[0], symbols[0]};
  shiftRegister.setAll(pinValues);
}

void displayNumbers(byte array[]){
  displayArray(array);
  lightTimer = millis();
}

void displayVcc(){
  motorsVibe(100);
  delay(100);
  motorsVibe(100);
  delay(100);
  motorsVibe(100);
  
  byte batteryLevel = constrain(map(readVcc(), 4200, 3000, 6, 0), 0, 6);

  for(byte i = 6; i >= batteryLevel; i--){
    byte batteryArray[2];
    if(i <= 3){
      batteryArray[0] = 0;
      batteryArray[1] = i + 7;
    }
    else{
      batteryArray[0] = (i - 3) + 7;
      batteryArray[1] = 10; 
    }
    displayArray(batteryArray);
    
    unsigned long batteryPointTimer = millis();
    while((abs(millis() - batteryPointTimer) < 300)){
      shiftRegisterPWM(brightness);
    }
  }
  lightTimer = millis();
}

long readVcc(){ // універсальна функція для обчислення опорної напруги
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif
  
  delay(2);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC));
  uint8_t low  = ADCL;
  uint8_t high = ADCH;
  long result = (high << 8) | low;
  result = MY_VCC_CONST * 1023 * 1000 / result; // розрахунок реального VCC
  
  return result;
}

void wakeUp(){
  cli();                                  // Disable interrupts
  sleep_disable();                        // Clear SE bit
  adc_enable();                           // ADC on
  sei();                                  // Enable interrupts

  lightTimer = millis();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
    
  randomSeed(millis());
}

void sleep(){
  clearDisplay();
  displayedNumbers[0] = symbols[0];
  displayedNumbers[1] = symbols[0];
  
  for(byte pin = 0; pin <= 5; pin++){
    pinMode(pin, INPUT);
  }
  
  cli();                                  // Disable interrupts
  adc_disable();                          // ADC off
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement

  sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
  sei();                                  // Enable interrupts
  sleep_cpu();                            // sleep
  // ----------- sleep ------------


  // ---------- wake up! ----------
  wakeUp();
}
