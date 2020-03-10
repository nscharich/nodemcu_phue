#include "Button2.h";           // used for rotary encoder button in addition to hardware LPF
#include <ESP8266WiFi.h>        // required for ESPhue.h
#include <SPI.h>                // used for talking to screen, maybe ADC if project changes to ESP-01
#include <WiFiClient.h>         // required for ESPhue.h
#include <Wire.h>               // needed for screen/spi?
#include <Adafruit_GFX.h>       // graphics library
#include <Adafruit_SSD1306.h>   // OLED IC library
#include <HueScreen.h>          // Used to update screen, calls from Adafruit_SSD1306 and prepares data for ESPHue
#include <ESPHue.h>             // Handy library to talk to PHue, added custom function for sending string based request

// if you forget this, the board will reset forever
void ICACHE_RAM_ATTR ISR_direction();

// pins, change if needed
const byte RE_button = 13;
const byte RE_left = 12;
const byte RE_right = 2;
volatile unsigned long int last_interrupt_time = 0; // used for rotary encoder debouncing
int progress[2] = {0,0};  // used for direction sensing rotary encoder in main loop
const char* ssid     = "";
const char* password = "";

// need to fine tune debounce, but for now it works
#define debounce_time_scroll 20
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    15

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // screen
Button2 button = Button2(RE_button);  // rotary encoder button
HueScreen screen(&display,1,17,125,13); // interface for screen and getting values to send phue
WiFiClient client; 
ESPHue myHue = ESPHue(client, "API_KEY", "Bridge-IP", 80);

void setup() {
  Serial.begin(115200);
  // rotary encoder pins and attach ISR
  pinMode(RE_left, INPUT_PULLUP);
  pinMode(RE_right, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RE_left), ISR_direction, FALLING);

  // used from Button2 lib
  button.setClickHandler(handler);
  button.setLongClickHandler(handler);
  button.setDoubleClickHandler(handler);
  button.setTripleClickHandler(handler);

  // init the OLED screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("Failed to init screen");
    while(1) {Serial.println("ASF");}
  }
  display.clearDisplay();
  screen.drawText();
  screen.updateProgress(0);
  display.display();
}

void ISR_direction(){
  // debounce
  if(millis() - last_interrupt_time > debounce_time_scroll){
    // depending on direction of rotary encoder, at the time the
    // ISR is called check the status of the other pin that did not
    // call the ISR to determine which direction it is going
  if(digitalRead(RE_right)){
    progress[0] -= 1;
  }else{
    progress[0] += 1;
  }
  last_interrupt_time = millis();
  }else if(millis() < last_interrupt_time){
    // this is used in case the timer rolls over
    last_interrupt_time = 0;
  }
}

void handler(Button2& btn) {
    switch (btn.getClickType()) {
        case SINGLE_CLICK:
        // TODO: need to build home setup from groups API call and store results in memory
        // for now, I have manually switched the attached group number in the switch
            int group_num;
            switch(screen.getGroup()){
              case 0: group_num = 1; break;
              case 1: group_num = 2; break;
              case 2: group_num = 3; break;
              case 3: group_num = 6; break;
            }
            // Calls custom ESPHue method (I edited the lib so that i can make a custom request)
            // The function takes in the group_num (converted above) that is used in the URL
            // The other two arguments go into the command which are then formatted to JSON
            // examples from my library for config state are: on, bri, hue, sat
            // be careful, these values have max limits, but my lib takes care of that
            myHue.setGroupString(group_num,screen.getConfigState(),screen.getSendVal());
            break;
        case DOUBLE_CLICK:
            // this increments the value you are changing (on, bri, hue sat) and updates the screen
            screen.incrementConfig();
            break;
        case TRIPLE_CLICK:
            // TODO: Related to the feature on single click, needs to auto populate based on initial
            // cont: API call for room type name, currently hard coded in my lib
            // this increments the group that is shown on the screen
            screen.incrementGroup();
            break;
        case LONG_CLICK:
            break;
    }
}

void loop() {
  // this loop is required from Button2
  button.loop();
  // TODO: have the values reset to zero after being called, easy fix but am not home to test
  // this will sense the direction in which to update the screen using my lib
  // updateProgress(1) increments the progress and will saturate at the parameters max value
  // these max values are in my lib, but are set from the documentation of PHue API
  // updateProgress(0) decrements, and each has a zero limit
  if(progress[0] != progress[1]){
    if(progress[0] > progress[1]){
      screen.updateProgress(1);
    }else{
      screen.updateProgress(0);
    }
    progress[1] = progress[0];
  }
}
