// Name: rgbLight.hpp - Version 1.0.0
// Author: crdrisko
// Date: 01/27/2020-21:55:30
// Description: A wrapper for an adjustable RGB-LED light using the WiringPi API

#ifndef RGBLIGHT_HPP
#define RGBLIGHT_HPP

#include "pwmAdjustableLight.hpp"

namespace RaspberryPi::GPIO
{
    class RGBLight
    {
    private:
        PwmAdjustableLightPtr redLight;
        PwmAdjustableLightPtr greenLight;
        PwmAdjustableLightPtr blueLight;
    
    public:
        RGBLight(int RedPinNumber, int GreenPinNumber, int BluePinNumber)
        {
            redLight = std::make_shared<PwmAdjustableLight>(RedPinNumber);
            greenLight = std::make_shared<PwmAdjustableLight>(GreenPinNumber);
            blueLight = std::make_shared<PwmAdjustableLight>(BluePinNumber);
        }

        void setRGBIntensities(const int& redIntensity, const int& greenIntensity, 
            const int& blueIntensity) const
        {
            redLight->setIntensity(redIntensity);
            greenLight->setIntensity(greenIntensity);
            blueLight->setIntensity(blueIntensity);
        }
    };

    using RGBLightPtr = std::shared_ptr<RGBLight>;
}

#endif
