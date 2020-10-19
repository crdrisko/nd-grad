// Name: Alertor.cpp
// Author: crdrisko
// Date: 01/28/2020-08:09:38
// Description: Use a button to alter the state of a passive buzzer

#include "../gpioObjects/passiveBuzzer.hpp"
#include "../gpioObjects/button.hpp" 

using namespace RaspberryPi::GPIO;

void createAlertor(const PassiveBuzzerPtr& Buzzer, const ButtonPtr& Button);

int main()
{
    std::cout << "Program is starting..." << std::endl;

    PassiveBuzzerPtr buzzer { std::make_shared<PassiveBuzzer>(17) };
    ButtonPtr button { std::make_shared<Button>(18) };

    createAlertor(buzzer, button);
}

void createAlertor(const PassiveBuzzerPtr& Buzzer, const ButtonPtr& Button)
{
    long lastChangeTime {}, captureTime {50};
    bool initialState {false}, lastButtonState {false};

    auto turnBuzzerOn = std::bind( &PassiveBuzzer::alertor, Buzzer, 1, "Alertor turned on." );
    auto turnBuzzerOff = std::bind( &PassiveBuzzer::setTone, Buzzer, 0, 0, "Alertor turned off." );

	while (true)
	{
        initialState = Button->isButtonPressed();               // Get the initial state of the system

        if (initialState != lastButtonState)
            lastChangeTime = WiringPi::millis();
        
        if (WiringPi::millis() - lastChangeTime > captureTime)  // Ensure the change is not due to electrical noise
        {
            if (Buzzer->isBuzzerOn())
                Button->pushButton(turnBuzzerOff);
            else
                Button->pushButton(turnBuzzerOn);
        }

        lastButtonState = initialState;
    }
}
