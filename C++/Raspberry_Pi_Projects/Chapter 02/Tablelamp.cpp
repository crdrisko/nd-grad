// Name: Tablelamp.cpp
// Author: crdrisko
// Date: 01/26/2020-11:08:15
// Description: Use a button to alter the state of a LED

#include "../gpioObjects/ledLight.hpp"
#include "../gpioObjects/button.hpp" 

using namespace RaspberryPi::GPIO;

void tablelamp(const LEDLightPtr& LEDLight, const ButtonPtr& Button);

int main()
{
    std::cout << "Program is starting..." << std::endl;

    LEDLightPtr ledLight { std::make_shared<LEDLight>(17) };
    ButtonPtr button { std::make_shared<Button>(18) };

    tablelamp(ledLight, button);
}

void tablelamp(const LEDLightPtr& LEDLight, const ButtonPtr& Button)
{
    long lastChangeTime {}, captureTime {50};
    bool initialState {false}, lastButtonState {false};

    auto turnLEDLightOn = std::bind( &LEDLight::turnLEDLightOn, LEDLight, 0, "LED turned on." );
    auto turnLEDLightOff = std::bind( &LEDLight::turnLEDLightOff, LEDLight, 0, "LED turned off." );

	while (true)
	{
        initialState = Button->isButtonPressed();               // Get the initial state of the system

        if (initialState != lastButtonState)
            lastChangeTime = WiringPi::millis();
        
        if (WiringPi::millis() - lastChangeTime > captureTime)  // Ensure the change is not due to electrical noise
        {
            if (LEDLight->isLightOn())
                Button->pushButton(turnLEDLightOff);
            else
                Button->pushButton(turnLEDLightOn);
        }

        lastButtonState = initialState;
    }
}
