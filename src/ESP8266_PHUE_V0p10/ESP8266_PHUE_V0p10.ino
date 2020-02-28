#include "Button2.h";
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HueScreen.h>

void ICACHE_RAM_ATTR ISR_direction();
const byte RE_button = 13;
const byte RE_left = 12;
const byte RE_right = 2;
volatile unsigned long int last_interrupt_time = 0;
int progress[2] = {0,0};

#define debounce_time_scroll 20
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    15 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Button2 button = Button2(RE_button);
HueScreen screen(&display,1,17,125,13);

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
  display.clearDisplay();
  screen.drawText();
  screen.updateProgress(0);
  display.display();
}

void ISR_direction(){
  if(millis() - last_interrupt_time > debounce_time_scroll){
  Serial.print("ISR Direction: ");
  if(digitalRead(RE_right)){
    Serial.println("Left");
    progress[0] -= 2;
  }else{
    Serial.println("Right");
    progress[0] += 2;
  }
  last_interrupt_time = millis();
  }else if(millis() < last_interrupt_time){
    last_interrupt_time = 0;
  }
}

void handler(Button2& btn) {
    switch (btn.getClickType()) {
        case SINGLE_CLICK:
            Serial.print("Send command: TODO");
            break;
        case DOUBLE_CLICK:
            Serial.print("Change config:");
            Serial.println(screen.incrementConfig());
            display.display();
            break;
        case TRIPLE_CLICK:
            Serial.print("Change group:");
            Serial.println(screen.incrementGroup());
            display.display();
            break;
        case LONG_CLICK:
            Serial.print("long boi!");
            break;
    }
    //Serial.print("click");
    //Serial.print(" (");
    //Serial.print(btn.getNumberOfClicks());    
    //Serial.println(")");
}

void loop() {
  button.loop();
  if(progress[0] != progress[1]){
    screen.updateProgress(progress[0]);
    display.display();
    progress[1] = progress[0];
  }
}
