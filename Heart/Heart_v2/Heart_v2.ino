#define F_CPU 1200000UL

#define LED PB0   //PWM
#define MOTOR PB1
#define BUTTON PB4

#define DIASTOLE 750
#define ATRIAL_SYSTOLE 100
#define ATRIAL_DIASTOLE 50
#define VENTRICULAR_SYSTOLE 150

#define DIASTOLE_BRIGHTNESS 20
#define ATRIAL_SYSTOLE_BRIGHTNESS 100
#define VENTRICULAR_SYSTOLE_BRIGHTNESS 255

#define DIASTOLE_FREQUENCY 0
#define ATRIAL_SYSTOLE_FREQUENCY 100
#define VENTRICULAR_SYSTOLE_FREQUENCY 200

#define SPEED 95

bool vibration = true;
byte counter = 0;

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>

ISR(PCINT0_vect)
{
  delay(50);
  if((PINB & (1 << BUTTON)) == 0)
  {
    counter++;

    if(counter > 2)
      counter = 0;

    if(counter == 0 || counter == 1)
      vibration = !vibration;

    analogWrite(MOTOR, DIASTOLE_FREQUENCY);

    while((PINB & (1 << BUTTON)) == 0);
  }
}

void setup() 
{
  DDRB &= ~(1 << BUTTON);  //pinMode(BUTTON, INPUT_PULLUP);
  PORTB |= (1 << BUTTON);

  DDRB |= (1 << LED)|(1 << MOTOR);
  PORTB &= ~((1 << LED)|(1 << MOTOR));

  GIMSK |= (1 << PCIE);
  PCMSK |= (1 << BUTTON);
  sei();
}

void loop()
{
  switch(counter)
  {
    case 0: Palpitation(); 
      break;
    case 1: Palpitation(); 
      break;
    case 2: Breathing(); 
      break;
  }
}

void Palpitation()
{ 
  Beat(DIASTOLE_BRIGHTNESS, DIASTOLE_FREQUENCY, DIASTOLE);
  Beat(ATRIAL_SYSTOLE_BRIGHTNESS, ATRIAL_SYSTOLE_FREQUENCY, ATRIAL_SYSTOLE);
  Beat(DIASTOLE_BRIGHTNESS, DIASTOLE_FREQUENCY, ATRIAL_DIASTOLE);
  Beat(VENTRICULAR_SYSTOLE_BRIGHTNESS, VENTRICULAR_SYSTOLE_FREQUENCY, VENTRICULAR_SYSTOLE);
}

void Beat(byte BRIGHTNESS, byte FREQUENCY, int pause)
{
  if(counter != 0 && counter != 1)
    return;
    
  analogWrite(LED, BRIGHTNESS);
  if(vibration)
    analogWrite(MOTOR, FREQUENCY);
  delay(pause);
}

void Breathing()
{
  for(byte i = 1; i <= 14; i++)
  {
    if(counter != 2)
      return;
      
    analogWrite(LED, i*i);
    delay(SPEED);
  }

  for(byte i = 14; i >= 1; i--)
  {
    if(counter != 2)
      return;
      
    analogWrite(LED, i*i);
    delay(SPEED);
  }
}

