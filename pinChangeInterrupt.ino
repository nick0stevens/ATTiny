/*
 * Pin Change Interrupt Example
 * Version: 1.0
 * Author: Alex from Inside Gadgets (http://www.insidegadgets.com)
 * Created: 25/02/2011
 *
 * Demonstration of the pin change interrupt
 *led on pin 0
 * Interrupt on digital pin 4
 
 *
 */
 
#include <avr/sleep.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int led = 0;
long startTime , currentTime;
long wakePeriod = 5000;

void setup(){
 pinMode(1,INPUT);
  
  sbi(GIMSK,PCIE); // Turn on Pin Change interrupt
  sbi(PCMSK,PCINT1); // Which pins are affected by the interrupt

}

void loop(){
 currentTime = millis();
 
 if (currentTime >startTime + wakePeriod){

   system_sleep();
  }

  
digitalWrite(led,HIGH);
delay(100);
digitalWrite(led,LOW);
delay(100);
}

// From http://interface.khm.de/index.php/lab/experiments/sleep_watchdog_battery/
void system_sleep() {
  cbi(ADCSRA,ADEN); // Switch Analog to Digital converter OFF
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode
  sleep_mode(); // System sleeps here
  sbi(ADCSRA,ADEN);  // Switch Analog to Digital converter ON
}

ISR(PCINT0_vect) { // this is the interrupt routine that runs when pin D4 experiences a change in input, from high to low or vice versa
startTime = millis();
  
}
