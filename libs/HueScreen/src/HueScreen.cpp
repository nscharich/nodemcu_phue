#include<HueScreen.h>
HueScreen::HueScreen(Adafruit_SSD1306 *disp, int x, int y, int w, int h):_disp(disp){
    _parameters[0] = x;
    _parameters[1] = y;
    _parameters[2] = w;
    _parameters[3] = h;
    }
void HueScreen::drawText(){
    _disp->fillRect(0,0,127,16,SSD1306_BLACK);
    _disp->setTextSize(2);
    _disp->setTextColor(SSD1306_WHITE);
    _disp->setCursor(0,0);
    _disp->print(_groups[_groupState]);
    _disp->print(':');
    _disp->print(_config[_configState]);
	_disp->display();
}
int HueScreen::incrementGroup(){
    if(_groupState >= 3){_groupState = 0;}
    else{_groupState++;}
    this->drawText();
    return _groupState;
}

int HueScreen::incrementConfig(){
    if(_configState >= 3){_configState = 0;}
    else{_configState++;}
    this->drawText();
	this->updateProgress(-1);
    return _configState;
}

void HueScreen::updateProgress(int i){
	if(i == 1 && (_configVal[_configState] + _configStepSize[_configState]) <= _configMax[_configState]){
		_configVal[_configState] += _configStepSize[_configState];
	}else if(i == 0 && (_configVal[_configState] - _configStepSize[_configState]) >= 0){
		_configVal[_configState] -= _configStepSize[_configState];
	}
    _screenProgress = (_configVal[_configState]*100)/_configMax[_configState];
    int16_t temp = (((_parameters[2]-3)*_screenProgress)/100) + _parameters[0]+1;
    _disp->fillRect(_parameters[0],_parameters[1],_parameters[2],_parameters[3],SSD1306_BLACK);
	_disp->drawRect(_parameters[0],_parameters[1],_parameters[2],_parameters[3],SSD1306_WHITE);
    _disp->fillRect(_parameters[0]+1,_parameters[1]+1,temp,_parameters[3]-2,SSD1306_WHITE);
	_disp->display();
}