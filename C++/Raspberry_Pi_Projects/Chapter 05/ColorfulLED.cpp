// Name: ColorfulLED.cpp
// Author: crdrisko
// Date: 01/27/2020-22:32:45
// Description: Use PWM to create a random set of RGB colors

#include <cstdlib>
#include "../gpioObjects/rgbLight.hpp"

using namespace RaspberryPi::GPIO;

void colorfulLEDLight(const RGBLightPtr& RGBLight);

int main()
{
    std::cout << "Program is starting..." << std::endl;

    RGBLightPtr rgbLight { std::make_shared<RGBLight>(17, 18, 27) };

    colorfulLEDLight(rgbLight);
}

void colorfulLEDLight(const RGBLightPtr& RGBLight)
{
    while (true)
    {
        int randomRedIntensity {std::rand() % 100};
        int randomGreenIntensity {std::rand() % 100};
        int randomBlueIntensity {std::rand() % 100};

        RGBLight->setRGBIntensities(randomRedIntensity, randomGreenIntensity, randomBlueIntensity);
        
        std::cout << "Red: "   << randomRedIntensity   << ", "
                  << "Green: " << randomGreenIntensity << ", "
                  << "Blue: "  << randomBlueIntensity  << std::endl;

        WiringPi::delay(300);
    }
}
