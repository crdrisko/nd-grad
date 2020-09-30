// Name: BreathingLED.cpp
// Author: crdrisko
// Date: 01/26/2020-16:26:57
// Description: Use PWM to create a breathing LED

#include <numeric>
#include <algorithm>
#include "../gpioObjects/pwmAdjustableLight.hpp"

using namespace RaspberryPi::GPIO;

void breathingLEDLight(const PwmAdjustableLightPtr& AdjustableLight);

int main()
{
    std::cout << "Program is starting..." << std::endl;

    PwmAdjustableLightPtr adjustableLight { std::make_shared<PwmAdjustableLight>(18) };

    breathingLEDLight(adjustableLight);
}

void breathingLEDLight(const PwmAdjustableLightPtr& AdjustableLight)
{
    std::array<int, 100> ledLightPercentage;
    std::iota(ledLightPercentage.begin(), ledLightPercentage.end(), 0);

    while (true)
    {
        std::for_each( ledLightPercentage.begin(), ledLightPercentage.end(), 
            [AdjustableLight](const int& i) -> void { AdjustableLight->setIntensity(i); 
                WiringPi::delay(20); } );

        WiringPi::delay(300);

        std::reverse(ledLightPercentage.begin(), ledLightPercentage.end());
    }
}
