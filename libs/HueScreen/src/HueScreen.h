#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
class HueScreen{
private:
	int16_t _parameters[4];
	int _progress = 0;
	Adafruit_SSD1306 *_disp;
	String _config[4] = {"on","bri","hue","sat"};
	String _groups[4] = {"Dining","Living","Bed","Bath"};
	int _configState = 0;
	int _groupState = 0;
public:
	HueScreen(Adafruit_SSD1306 *disp, int x, int y, int w, int h);
    void drawText();
    int incrementGroup();
    int incrementConfig();
    void updateProgress(int i);
    int getProgress(){return _progress;}
};