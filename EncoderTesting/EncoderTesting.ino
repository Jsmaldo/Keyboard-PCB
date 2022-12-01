#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define rotary_press 14
#define rotary_A 6
#define rotary_B 5

unsigned long screenTimeMillis = 0; // monitor screen active time
unsigned long screenUpdateMillis;

bool increase, lastIncrease, deb_increase;
bool decrease, lastDecrease, deb_decrease;
bool press, lastPress, deb_press;

bool _A, _B;
bool last_A;

unsigned long rotateDebounce;
unsigned long pressDebounce;

int count;

void setup() {
  //initalize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  display.clearDisplay();
  display.setRotation(0);  
  display.setTextSize(3); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);

  //initialize input/output pins
  pinMode(rotary_press, INPUT_PULLUP);
  pinMode(rotary_A, INPUT_PULLUP);
  pinMode(rotary_B, INPUT_PULLUP);
}
void loop() {

  InputMonitoring();
  ScreenUpdates();
  math();

}
void math(){
  if(deb_increase == 1){
    count++;
  }
  if(deb_decrease == 1){
    count--;
  }
  if(deb_press == 1){
    count = count + 10;
  }
}
void ScreenUpdates(){
  if(millis() - screenTimeMillis < 5000){
    if(millis() - screenUpdateMillis > 250){
      display.setCursor(10, 10);
      display.println(count);
      display.display();
    }
  }
  else{
    display.clearDisplay();
    display.display();
  }
}
void InputMonitoring(){
  _A = digitalRead(rotary_A);
  _B = digitalRead(rotary_B);
  press = digitalRead(rotary_press);

  if(_A != last_A && _A == 0){
    if(_B != _A){
      count--;
      screenTimeMillis = millis();
    }
    else{
      count++;
      screenTimeMillis = millis();
    }
  }
  last_A = _A;

  if((press != lastPress) && (digitalRead(rotary_press) == 0)){
    if(millis() - pressDebounce > 100){
      screenTimeMillis = millis();
      pressDebounce = millis();
      deb_press = 1;
      return;
    }
    else{
      deb_press = 0;
    }
  }

  lastIncrease = increase;
  lastDecrease = decrease;
  lastPress = press;
}















