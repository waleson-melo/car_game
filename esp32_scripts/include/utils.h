#include <Arduino.h>

int deBounce(int state, int pin){
  int current_state = digitalRead(pin);

  if(state != current_state){
    delay(10);
    current_state = digitalRead(pin);
  }
  
  return current_state;
}