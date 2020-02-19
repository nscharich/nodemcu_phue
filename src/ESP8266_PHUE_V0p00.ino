void ICACHE_RAM_ATTR ISR_direction();
void ICACHE_RAM_ATTR ISR_button();
const byte RE_button = 13;
const byte RE_left = 12;
const byte RE_right = 2;
volatile unsigned long int last_interrupt_time = 0;

#define debounce_time_scroll 50
#define debounce_time_button 1000

void setup() {
  Serial.begin(115200);
  pinMode(RE_button, INPUT);
  pinMode(RE_left, INPUT_PULLUP);
  pinMode(RE_right, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RE_button), ISR_button, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RE_left), ISR_direction, FALLING);
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

void ISR_button(){
  if(millis() - last_interrupt_time > debounce_time_button){
    Serial.println("Button Tapped");
    last_interrupt_time = millis();
  }else if(millis() < last_interrupt_time){
    last_interrupt_time = 0;
  }
}

void loop() {

}
