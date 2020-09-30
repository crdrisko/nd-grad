// Name: buzzer.hpp
// Author: crdrisko
// Date: 01/28/2020-07:59:08
// Description: A wrapper for a buzzer using the WiringPi API

#ifndef BUZZER_HPP
#define BUZZER_HPP

#include <string_view>
#include "wiringPiObject.hpp"

namespace RaspberryPi::GPIO
{
    class Buzzer : public WiringPiObject
    {
    private:
        const bool ON { HIGH };
        const bool OFF { LOW };

    public:
        explicit Buzzer(int GPIO_PinNumber) : WiringPiObject{GPIO_PinNumber}
        {
            // Set the Buzzer Pin number to output mode
            WiringPi::pinMode(this->getWiringPi_PinNumber(), OUTPUT);	            
        }

        bool isBuzzerOn() const { return ( this->getObjectStatus() ) ? ON : OFF; }

        void turnBuzzerOn(int delayFactor = 0, std::string_view message = "")
        {
            WiringPi::digitalWrite(this->getWiringPi_PinNumber(), ON);

            if ( !message.empty() )
                std::cout << message << std::endl;
            
            WiringPi::delay(delayFactor);
        }

        void turnBuzzerOff(int delayFactor = 0, std::string_view message = "")
        {
            WiringPi::digitalWrite(this->getWiringPi_PinNumber(), OFF);

            if ( !message.empty() )
                std::cout << message << std::endl;
            
            WiringPi::delay(delayFactor);
        }
    };

    using BuzzerPtr = std::shared_ptr<Buzzer>;
}

#endif
