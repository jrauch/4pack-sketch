#include <HID-Project.h>
#include <HID-Settings.h>

//debounce milliseconds
const int debounce = 5;
//Switch Pins
const byte k[4] = { 4, 5, 6, 7 };
//Switch status
boolean s[4] = { 0, 0, 0, 0 };

//Keycodes
const KeyboardKeycode kcode[][2] = { 
   {KEY_LEFT_CTRL, KEY_SPACE},
   {KEY_LEFT_SHIFT, KEY_B},
   {KEY_LEFT_SHIFT, KEY_C},
   {KEY_LEFT_CTRL, KEY_ENTER}
};

void setup() {
  Keyboard.begin();
  Consumer.begin();
  //setup inputs, turn on pullups
  for (int i = 0; i < 4; i++) {
    pinMode(k[i], INPUT);
    digitalWrite(k[i], 1);
  }
}

void loop() {
  CheckKeys();
  delay(debounce);
}

void CheckKeys() {
  for (int i = 0; i < (sizeof(kcode)/sizeof(kcode[0])); i++) {
    if (digitalRead(k[i]) == 0) {
      if (s[i] == 0) {
        for(int j = 0 ; j < sizeof(kcode[i]) ; j++) {
          if(kcode[i][j] != 0)
            Keyboard.press(kcode[i][j]);
        }
        s[i] = 1;
      }
    }
    else {
      if (s[i] == 1) {
        s[i] = 0;
        for(int j = 0 ; j < sizeof(kcode[i]) ; j++) {
          if(kcode[i][j] != 0)
            Keyboard.release(kcode[i][j]);
        }
      }
    }  
  }
}
