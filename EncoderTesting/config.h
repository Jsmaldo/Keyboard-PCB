#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define rotary_press 14 //rotary encoder press input
#define rotary_A 6 //rotary encoder A channel
#define rotary_B 5 //rotary encoder B channel

#define slider A3 //slider analog input
#define touch A2 //slider capacitive touch input

//use pins for TB6612FNG motor driver
#define pwmA 3 //driver PWM Channel
#define in1A 2 //driver CW Channel
#define in2A 4 //driver CCW Channel