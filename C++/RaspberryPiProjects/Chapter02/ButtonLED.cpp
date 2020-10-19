// Name: ButtonLED.cpp
// Author: crdrisko
// Date: 01/25/2020-18:11:50
// Description: Use a button to alter the state of a LED

#include "../gpioObjects/ledLight.hpp"
#include "../gpioObjects/button.hpp" 

using namespace RaspberryPi::GPIO;

void buttonLED(const LEDLightPtr& LEDLight, const ButtonPtr& Button);

int main()
{
    std::cout << "Program is starting..." << std::endl;

    LEDLightPtr ledLight { std::make_shared<LEDLight>(17) };
    ButtonPtr button { std::make_shared<Button>(18) };

    buttonLED(ledLight, button);
}

void buttonLED(const LEDLightPtr& LEDLight, const ButtonPtr& Button)
{
    auto turnLEDLightOn = std::bind( &LEDLight::turnLEDLightOn, LEDLight, 0, "LED turned on." );
    auto turnLEDLightOff = std::bind( &LEDLight::turnLEDLightOff, LEDLight, 0, "LED turned off." );

	while (true)
	{
        Button->pushButton(turnLEDLightOn);
        Button->releaseButton(turnLEDLightOff);
	}
}
