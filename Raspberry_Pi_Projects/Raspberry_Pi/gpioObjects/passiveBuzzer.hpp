// Name: passiveBuzzer.hpp - Version 1.0.0
// Author: crdrisko
// Date: 01/28/2020-08:16:56
// Description: 

#ifndef PASSIVEBUZZER_HPP
#define PASSIVEBUZZER_HPP

#include <cmath>
#include <utilities-api/utilities-api.hpp>
#include "buzzer.hpp"

namespace RaspberryPi::GPIO
{
    class PassiveBuzzer : public Buzzer
    {
    private:
        static inline const double resonanceFrequency {2000.0};

    public:
        explicit PassiveBuzzer(int GPIO_PinNumber) : Buzzer{GPIO_PinNumber}
        {
            WiringPi::SoftTone::softToneCreate(this->getWiringPi_PinNumber());
        }

        void setTone(const int& toneValue, int delayFactor = 0, std::string_view message = "") const
        {
            WiringPi::SoftTone::softToneWrite(this->getWiringPi_PinNumber(), toneValue);

            if ( !message.empty() )
                std::cout << message << std::endl;
            
            WiringPi::delay(delayFactor);
        }

        void alertor(int delayFactor = 0, std::string_view message = "") const
        {
            using namespace Utilities_API::PhysicalQuantities;

            Frequency toneValue;
            Frequency ResonanceFrequency(resonanceFrequency);
            Angle thetaInRadians;

            for (Angle theta = 0.0_deg; theta < 360.0_deg; theta += 1.0_deg)
            {
                thetaInRadians = theta.convertQuantity(Conversions::getAngleConversionFactor("deg", "rad"));

                // Weight the value of the sine and add the resonance frequency
                toneValue = ( DimensionlessQuantity(std::sin(thetaInRadians.getMagnitude())) * Frequency(500.0) )
                    + ResonanceFrequency;

                this->setTone(toneValue.getMagnitude(), delayFactor, message);
            }
        }
    };

    using PassiveBuzzerPtr = std::shared_ptr<PassiveBuzzer>;
}

#endif
