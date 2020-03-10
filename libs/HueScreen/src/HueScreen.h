#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
class HueScreen{
private:
	int16_t _parameters[4];
	int _screenProgress = 0;
	Adafruit_SSD1306 *_disp;
	String _config[4] = {"on","bri","hue","sat"};
	String _groups[4] = {"Dining","Living","Bed","Bath"};
	uint16_t _configVal[4] = {0,0,0,0};
	uint16_t _configMax[4] = {1,254,65535,254};
	int16_t _configStepSize[4] = {1,8,1200,8};
	int _configState = 0;
	int _groupState = 0;
public:
	HueScreen(Adafruit_SSD1306 *disp, int x, int y, int w, int h);
    void drawText();
    int incrementGroup();
    int incrementConfig();
    void updateProgress(int i);
	int getGroup(){return _groupState;}
	String getConfigState(){return _config[_configState];}
	uint16_t getSendVal(){return _configVal[_configState];}
};