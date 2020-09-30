// Name: wiringPiObject.hpp
// Author: crdrisko
// Date: 01/25/2020-20:14:57
// Description: A wrapper for an object that uses the WiringPi API

#ifndef WIRINGPIOBJECT_HPP
#define WIRINGPIOBJECT_HPP

#include <map>
#include <memory>
#include <iostream>

// Wrap the wiringPi and softPwm functionality in separate namespaces
namespace WiringPi
{ 
    #include <wiringPi.h>

    namespace SoftPwm
    {
        #include <softPwm.h>
    }

    namespace SoftTone
    {
        #include <softTone.h>
    }
}

namespace RaspberryPi::GPIO
{
    class WiringPiObject
    {
    private:
        int gpio_PinNumber;
        static inline bool initializedWiringPi {false};

        static inline std::map<int, int> gpio_to_wPi_mapping 
        {
            { 0, 30}, { 1, 31}, { 2,  8}, { 3,  9}, { 4,  7}, { 5, 21}, { 6, 22},
            { 7, 11}, { 9, 13}, { 8, 10}, {10, 12}, {11, 14}, {12, 26}, {13, 23},
            {14, 15}, {15, 16}, {16, 27}, {17,  0}, {18,  1}, {19, 24}, {20, 28},
            {21, 29}, {22,  3}, {23,  4}, {24,  5}, {25,  6}, {26, 25}, {27,  2}
        };

    public:
        explicit WiringPiObject(int GPIO_PinNumber) : gpio_PinNumber{GPIO_PinNumber}
        {
            if ( !initializedWiringPi )
            {
                WiringPi::wiringPiSetup();
                initializedWiringPi = true;
            }
        }

        int getWiringPi_PinNumber() const { return gpio_to_wPi_mapping[gpio_PinNumber]; }

        bool getObjectStatus() const
        {
            return WiringPi::digitalRead(this->getWiringPi_PinNumber()) ? HIGH : LOW;
        }
    };

    using WiringPiObjectPtr = std::shared_ptr<WiringPiObject>;
}

#endif
