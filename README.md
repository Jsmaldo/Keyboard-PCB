# Keyboard-PCB
 Keyboard PCB Including F1-F24 & arduino with attached encoders & OLED screen

![image](https://user-images.githubusercontent.com/31356222/204018447-56d170ef-e58a-4541-87a8-dc0ef5a1fe3d.png)
http://www.keyboard-layout-editor.com/#/gists/6a09a1fa51d7aa38f726f7da2f79e6d3

Special parts include:
 https://www.digikey.com/en/products/detail/bourns-inc/PSM60-081A-103B2/5825441
 https://www.digikey.com/en/products/detail/bourns-inc/PEC11L-4115F-S0020/4699168
 https://www.amazon.com/MakerFocus-Display-SSD1306-3-3V-5V-Arduino/dp/B079BN2J8V/ref=sr_1_5?crid=3C69TWMUGOQP3&keywords=oled+screen+i2c&qid=1669393383&sprefix=oled+screen+i2c%2Caps%2C93&sr=8-5

The OLED, slide pot, and rotary encoder will be controlled by a seperate processor, utilizing the deej project: https://github.com/omriharel/deej

Rotary encoder for selecting specific volume channel to adjust, and press-in to save slider value.
Motorized slide pot for adjusting specific channel volume
OLED for displaying current channel, and volume percentage.
