#include <Arduino.h>
#include <Keyboard.h>
#include <Bounce2.h>

#if !defined(BUTTON1_PIN) || !defined(BUTTON2_PIN) || !defined(BUTTON3_PIN)
#error "Missing BUTTON1_PIN, BUTTON2_PIN, and/or BUTTON3_PIN"
#endif

#define NUM_BUTTONS 3
#define DEBOUNCE_MS 1

Bounce debouncer[NUM_BUTTONS];
uint8_t buttonPins[3] = {BUTTON1_PIN, BUTTON2_PIN, BUTTON3_PIN};
uint8_t buttonMap[3] = {KEY_F17, KEY_F18, KEY_F19};

void setup() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    debouncer[i].attach(buttonPins[i]);
    debouncer[i].interval(DEBOUNCE_MS);
  }
  Keyboard.begin();
}

bool lastButtonState[3] = {false, false, false};
bool stop = false;
bool currentState;
int buttonIndex = 0;

void loop() {
  for (buttonIndex = 0; buttonIndex < NUM_BUTTONS; buttonIndex++) {
    debouncer[buttonIndex].update();
    currentState = debouncer[buttonIndex].read() == LOW;
    if (currentState != lastButtonState[buttonIndex]) {
      lastButtonState[buttonIndex] = currentState;
      if (currentState) {
        Keyboard.press(buttonMap[buttonIndex]);
      } else {
        Keyboard.release(buttonMap[buttonIndex]);
      }
    }
  }
}