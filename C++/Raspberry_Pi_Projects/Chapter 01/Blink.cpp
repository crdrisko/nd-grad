// Name: Blink.cpp
// Author: crdrisko
// Date: 01/25/2020-17:15:11
// Description: Repeatedly turn a LED light in position GPIO 17 on and off

#include "../gpioObjects/ledLight.hpp"

using namespace RaspberryPi::GPIO;

void blinkingLEDLight(const LEDLightPtr& ledLight);

int main()
{	
	std::cout << "Program is starting..." << std::endl;

    LEDLightPtr ledLight { std::make_shared<LEDLight>(17) };

	blinkingLEDLight(ledLight);
}

void blinkingLEDLight(const LEDLightPtr& ledLight)
{
    while (true)
    {
        ledLight->turnLEDLightOn(1000, "LED turned on.");
        ledLight->turnLEDLightOff(1000, "LED turned off.");   
    }
}
