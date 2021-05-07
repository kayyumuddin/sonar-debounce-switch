#include <Arduino.h>
#include <NewPing.h>
#include <SimpleTimer.h>

SimpleTimer timer;

bool switchVal;

const int ledPin = 13; 

// Variables will change:
int ledState = HIGH;       // the current state of the output pin
int buttonState;           // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin


unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 100;   

#define TRIGGER_PIN 10   
#define ECHO_PIN 9       
#define MAX_DISTANCE 40 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void take_data()
{
  int distance = sonar.ping_cm();
  if (distance > 5 && distance < 30)
  {
    switchVal = HIGH;
  }
  else
  {
    switchVal = LOW;
  }
}

void setup()
{
  timer.setInterval(50L, take_data);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void debounce()
{
  int reading = switchVal;

  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading != buttonState)
    {
      buttonState = reading;

      if (buttonState == HIGH)
      {
        ledState = !ledState;
      }
    }
  }

  digitalWrite(ledPin, ledState);

  lastButtonState = reading;
}
void loop()
{
  timer.run();
  debounce();
}