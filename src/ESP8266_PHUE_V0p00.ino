#include "Button2.h";
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ADS1015.h>

void ICACHE_RAM_ATTR ISR_direction();
const byte RE_button = 13;
const byte RE_left = 12;
const byte RE_right = 2;
volatile unsigned long int last_interrupt_time = 0;

#define debounce_time_scroll 50
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    15 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Button2 button = Button2(RE_button);

void setup() {
  Serial.begin(115200);
  pinMode(RE_left, INPUT_PULLUP);
  pinMode(RE_right, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RE_left), ISR_direction, FALLING);
  button.setClickHandler(handler);
  button.setLongClickHandler(handler);
  button.setDoubleClickHandler(handler);
  button.setTripleClickHandler(handler);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("Failed to init screen");
    while(1) {Serial.println("ASF");}
  }
  drawText();
}

void ISR_direction(){
  if(millis() - last_interrupt_time > debounce_time_scroll){
  Serial.print("ISR Direction: ");
  if(digitalRead(RE_right)){
    Serial.println("Left");
  }else{
    Serial.println("Right");
  }
  last_interrupt_time = millis();
  }else if(millis() < last_interrupt_time){
    last_interrupt_time = 0;
  }
}

void handler(Button2& btn) {
    switch (btn.getClickType()) {
        case SINGLE_CLICK:
            break;
        case DOUBLE_CLICK:
            Serial.print("double ");
            break;
        case TRIPLE_CLICK:
            Serial.print("triple ");
            break;
        case LONG_CLICK:
            Serial.print("long");
            break;
    }
    Serial.print("click");
    Serial.print(" (");
    Serial.print(btn.getNumberOfClicks());    
    Serial.println(")");
}


void drawText(void){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE); // draw white text
  display.setCursor(0,0);
  display.println("Hello Nate");
  display.display();
}


void loop() {
  button.loop();
}
