// Name: ledBarGraph.hpp
// Author: crdrisko
// Date: 01/26/2020-12:24:52
// Description: A wrapper for a LED light bar using the WiringPi API

#ifndef LEDBARGRAPH_HPP
#define LEDBARGRAPH_HPP

#include <array>
#include "ledLight.hpp"

namespace RaspberryPi::GPIO
{
    class LEDBarGraph
    {
    private:
        std::array<LEDLightPtr, 10> ledLights;

    public:
        explicit LEDBarGraph(std::array<int, 10> GPIO_PinNumbers)
        { 
            for (std::size_t i {}; i < 10; ++i)
                ledLights[i] = std::make_shared<LEDLight>(GPIO_PinNumbers[i]); 
        }

        std::array<LEDLightPtr, 10> getLEDLights() const { return this->ledLights; }
    };

    using LEDBarGraphPtr = std::shared_ptr<LEDBarGraph>;
}

#endif
