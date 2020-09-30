// Name: button.hpp
// Author: crdrisko
// Date: 01/25/2020-20:12:41
// Description: A wrapper for a button using the WiringPi API

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include "wiringPiObject.hpp"

namespace RaspberryPi::GPIO
{
    class Button : public WiringPiObject
    {
    private:
        const bool RELEASED { HIGH };
        const bool PRESSED { LOW };

    public:
        Button(int GPIO_PinNumber) : WiringPiObject{GPIO_PinNumber}
        {
            // Set the buttonPin to input mode
            WiringPi::pinMode(this->getWiringPi_PinNumber(), INPUT);

            // Pull up to HIGH level
	        WiringPi::pullUpDnControl(this->getWiringPi_PinNumber(), PUD_UP);		
        }

        bool isButtonPressed() { return ( this->getObjectStatus() ) ? PRESSED : RELEASED; }

        void pushButton(std::function<void(int)> operationOnButtonPress)
        {
            int count {};

            while ( this->isButtonPressed() )
            {
                if (count++ == 0)
                {
                    std::cout << "Button is pressed, ";
                    operationOnButtonPress(0);
                }
            }
        }

        void releaseButton(std::function<void(int)> operationOnButtonRelease)
        {
            int count {};

            while ( !this->isButtonPressed() )
            {
                if (count++ == 0)
                {
                    std::cout << "Button is released, ";
                    operationOnButtonRelease(0);
                }
            }
        }
    };

    using ButtonPtr = std::shared_ptr<Button>;
}

#endif
