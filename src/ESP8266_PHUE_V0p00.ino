void ICACHE_RAM_ATTR ISR_button();
void ICACHE_RAM_ATTR ISR_direction();
const byte RE_button = 13;
const byte RE_left = 12;
const byte RE_right = 2;
volatile unsigned long int rot_interrupt_time = 0;
volatile unsigned long int but_interrupt_time = 0;
volatile bool long_hold = false;

int hold_buffer = 0;

#define debounce_time_scroll 50
#define debounce_time_button 800
#define button_time_hold_min 3000

void setup() {
  Serial.begin(115200);
  pinMode(RE_button, INPUT_PULLUP);
  pinMode(RE_left, INPUT_PULLUP);
  pinMode(RE_right, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RE_button), ISR_button, FALLING);
  attachInterrupt(digitalPinToInterrupt(RE_left), ISR_direction, FALLING);

}

void ISR_button(){
  if(millis() - but_interrupt_time > debounce_time_button){
    while(hold_buffer <= 5 && (millis() - but_interrupt_time < button_time_hold_min)){
        if(digitalRead(RE_button)){hold_buffer++;}
        delay(10);
      }
    if(hold_buffer <= 5 && (millis() - but_interrupt_time >= button_time_hold_min)){
      Serial.println("Button held");
    }else{
      Serial.println("Button tapped");
    }
    hold_buffer = 0;
    but_interrupt_time = millis();
  }else if(millis() < but_interrupt_time){
    but_interrupt_time = 0;
  }
}

void ISR_direction(){
  if(millis() - rot_interrupt_time > debounce_time_scroll){
  Serial.print("ISR Direction: ");
  if(digitalRead(RE_right)){
    Serial.println("Left");
  }else{
    Serial.println("Right");
  }
  rot_interrupt_time = millis();
  }else if(millis() < rot_interrupt_time){
    rot_interrupt_time = 0;
  }
}

void loop() {
}
