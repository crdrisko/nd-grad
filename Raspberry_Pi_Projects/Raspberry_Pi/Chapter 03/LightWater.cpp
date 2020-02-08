// Name: LightWater.cpp - Version 1.0.0
// Author: crdrisko
// Date: 01/26/2020-12:04:21
// Description: Simulate flowing water using a LED bar graph

#include <algorithm>
#include "../gpioObjects/ledBarGraph.hpp"

using namespace RaspberryPi::GPIO;

void flowLEDLights(const LEDBarGraphPtr& LEDLights);

int main()
{
    std::cout << "Program is starting..." << std::endl;

    std::array<int, 10> gpioPinsUsed {17, 18, 27, 22, 23, 24, 25, 2, 3, 8}; 
    
    LEDBarGraphPtr ledLights { std::make_shared<LEDBarGraph>(gpioPinsUsed) };

    flowLEDLights(ledLights);
}

void flowLEDLights(const LEDBarGraphPtr& LEDLights)
{
    std::array<LEDLightPtr, 10> LEDLightArray { LEDLights->getLEDLights() };

    while (true)
    {
        std::for_each( LEDLightArray.begin(), LEDLightArray.end(), 
            [](const LEDLightPtr& LEDLight) -> void { LEDLight->turnLEDLightOff(100); 
                LEDLight->turnLEDLightOn(); } );

        std::reverse(LEDLightArray.begin(), LEDLightArray.end());
    }
}
