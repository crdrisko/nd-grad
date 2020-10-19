// Name: pwmAdjustableLight.hpp
// Author: crdrisko
// Date: 01/27/2020-22:06:43
// Description: A wrapper for an adjustable LED light using the WiringPi API

#ifndef PWMADJUSTABLELIGHT_HPP
#define PWMADJUSTABLELIGHT_HPP

#include "ledLight.hpp"
#include <utilities-api/math.hpp>
#include <utilities-api/errors.hpp>

namespace RaspberryPi::GPIO
{
    class PwmAdjustableLight : public LEDLight
    {
    private:
        int minIntensity;
        int maxIntensity;

    public:
        PwmAdjustableLight(int GPIO_PinNumber, int MinIntensity = 0, int MaxIntensity = 100) 
            : LEDLight{GPIO_PinNumber}, minIntensity{MinIntensity}, maxIntensity{MaxIntensity}
        {
            WiringPi::SoftPwm::softPwmCreate(this->getWiringPi_PinNumber(), minIntensity, maxIntensity);
        }

        void setIntensity(const int& intensity) const
        {
            if ( Utilities_API::Math::withinRange(intensity, minIntensity, maxIntensity) )
                WiringPi::SoftPwm::softPwmWrite(this->getWiringPi_PinNumber(), intensity); 
            else
                Utilities_API::Errors::printFatalErrorMessage(1, "The intensity supplied must be within the given range.");
        }
    };

    using PwmAdjustableLightPtr = std::shared_ptr<PwmAdjustableLight>;
}

#endif
