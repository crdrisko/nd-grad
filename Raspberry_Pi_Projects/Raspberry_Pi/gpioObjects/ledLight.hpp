// Name: ledLight.hpp - Version 1.0.0
// Author: crdrisko
// Date: 01/25/2020-20:12:32
// Description: A wrapper for a LED light using the WiringPi API

#ifndef LEDLIGHT_HPP
#define LEDLIGHT_HPP

#include <string_view>
#include "wiringPiObject.hpp"

namespace RaspberryPi::GPIO
{
    class LEDLight : public WiringPiObject
    {
    private:
        const bool ON { HIGH };
        const bool OFF { LOW };

    public:
        explicit LEDLight(int GPIO_PinNumber) : WiringPiObject{GPIO_PinNumber}
        {
            // Set the LED Pin number to output mode
            WiringPi::pinMode(this->getWiringPi_PinNumber(), OUTPUT);	            
		
		    std::cout << "Using pin" << this->getWiringPi_PinNumber() << std::endl;
        }

        bool isLightOn() const { return ( this->getObjectStatus() ) ? ON : OFF; }

        void turnLEDLightOn(int delayFactor = 0, std::string_view message = "")
        {
            WiringPi::digitalWrite(this->getWiringPi_PinNumber(), ON);

            if ( !message.empty() )
                std::cout << message << std::endl;
            
            WiringPi::delay(delayFactor);
        }

        void turnLEDLightOff(int delayFactor = 0, std::string_view message = "")
        {
            WiringPi::digitalWrite(this->getWiringPi_PinNumber(), OFF);

            if ( !message.empty() )
                std::cout << message << std::endl;
            
            WiringPi::delay(delayFactor);
        }
    };

    using LEDLightPtr = std::shared_ptr<LEDLight>;
}

#endif
