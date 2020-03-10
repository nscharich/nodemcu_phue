# nodemcu_phue
This is a project that uses a NodeMCU (ESP8266) to communicate via a digital rotary encoder with push button to change the state, brightness, hue and saturation of Philips hue groups. The settings for the group, config and a status bar are displayed on a small screen. Please refer to the parts in this build. I do plan on making boards for this soon, when I do I will add the hardware schematic. For the rotary encoder button, I created a hardware lowpass filter to prevent debouncing.


Main parts (all ordered from Amazon, you can find them cheaper other places) each board averages $12-$13

• [NodeMCU - $19 for 5](https://www.amazon.com/gp/product/B07S5Z3VYZ/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1)

•	[128x32 OLED Screen (SSD1306) $11 for 2](https://www.amazon.com/gp/product/B0761LV1SD/ref=ppx_yo_dt_b_asin_title_o08_s03?ie=UTF8&psc=1)

•	[Digital rotary encoder with pushbutton $9 for 5](https://www.amazon.com/gp/product/B07DM2YMT4/ref=ppx_od_dt_b_asin_title_s03?ie=UTF8&psc=1)

I included a copy of all the libraries I used. I created my own called “HueScreen” that takes care of updating the screen and stores/has get methods for sending commands via the hue library.

Included libraries:

•	[Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library): Main graphics library

•	[Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306): Used to talk to the OLED display

•	[Button2](https://github.com/LennartHennigs/Button2): Used in addition to hardware LPF for button debouncing

•	[ESP Hue](https://github.com/circuitsforfun/ESP_Hue): This library was modified! New method added for sending command via string and uint16_t data type over Philips hue

•	Hue Screen: This library takes care of updating the screen via the SSD1306 library and then prepares values for the modified ESP Hue library.


Things to work on:

•	Better initialization of the system

•	Increase power saving for later battery version (current version consumes around 70mA)



[Philips hue API documentation](https://developers.meethue.com/develop/get-started-2/)


[Youtube video](https://www.youtube.com/watch?v=gNUWG1cN9SE)

<a href="https://www.youtube.com/watch?v=gNUWG1cN9SE"><img src="https://i.imgur.com/bu5txPu.gif" title="source: imgur.com" /></a>
