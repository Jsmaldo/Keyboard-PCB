#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define rotary_press 14 //rotary encoder press input
#define rotary_A 6 //rotary encoder A channel
#define rotary_B 5 //rotary encoder B channel
#define slider A3 //slider analog input

unsigned long screenTimeMillis = 0; // monitor screen active time
unsigned long screenUpdateMillis; // only write to the screen at a set rate
bool screenIdle;

bool increase, lastIncrease, deb_increase;
bool decrease, lastDecrease, deb_decrease;
bool press, lastPress, deb_press;

bool _A, _B;
bool last_A;

unsigned long rotateDebounce;
unsigned long pressDebounce;

int slideValue, lastSlideValue;
int volume, lastVolume; 

int channel, lastChannel;

String channels[] ={ //Setup user defined channel names, refer to deej config.yaml file.
  "MAIN",
  "MIC",
  "DISCORD",
  "FIREFOX",
  "GAME",
  "SYSTEM",
  "MUSIC"
};
int channelVolumes[6];

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { //initalize display
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  display.clearDisplay();
  display.setRotation(0);  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);

  //initialize input/output pins
  pinMode(rotary_press, INPUT_PULLUP);
  pinMode(rotary_A, INPUT_PULLUP);
  pinMode(rotary_B, INPUT_PULLUP);
  pinMode(slider, INPUT);
}
void loop() {
  DigitalInputMonitoring();
  AnalogInputMonitoring();
  ScreenUpdates();
}
void ScreenUpdates(){
  if(millis() - screenTimeMillis < 5000){
    if(millis() - screenUpdateMillis > 250){
      display.clearDisplay();
      display.setCursor(10, 0);
      display.println(channels[channel]);
      display.setCursor(10,18);
      display.println((channelVolumes[channel]) + String("%"));
      display.display();
      screenIdle = 0;
      lastChannel = channel;
    }
  }
  else{
    display.clearDisplay();
    display.display();
    screenIdle = 1;
  }
}
void DigitalInputMonitoring(){
  _A = digitalRead(rotary_A);
  _B = digitalRead(rotary_B);
  press = digitalRead(rotary_press);

  if(_A != last_A && _A == 0){
    if(millis() - rotateDebounce >= 150){
      if(_B != _A){
        screenTimeMillis = millis();
        if(screenIdle == 0) channel--;
        if(channel <= -1) channel = 6;
        return;
      }
      else{
        screenTimeMillis = millis();
        if(screenIdle == 0) channel++;
        if(channel > 6) channel = 0;
        return;
      }
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
void AnalogInputMonitoring(){
  slideValue = analogRead(slider); //read pot voltage
  channelVolumes[channel] = map(slideValue, 0, 1024, 100, 0);
  if(channelVolumes[channel] != lastVolume){
    screenTimeMillis = millis();
  }
  lastVolume = channelVolumes[channel];
}













