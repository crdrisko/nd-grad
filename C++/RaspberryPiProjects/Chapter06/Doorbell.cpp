// Name: Doorbell.cpp
// Author: crdrisko
// Date: 01/27/2020-23:25:37
// Description: Use a button to alter the state of an active buzzer

#include "../gpioObjects/buzzer.hpp"
#include "../gpioObjects/button.hpp" 

using namespace RaspberryPi::GPIO;

void doorbell(const BuzzerPtr& Buzzer, const ButtonPtr& Button);

int main()
{
    std::cout << "Program is starting..." << std::endl;

    BuzzerPtr buzzer { std::make_shared<Buzzer>(17) };
    ButtonPtr button { std::make_shared<Button>(18) };

    doorbell(buzzer, button);
}

void doorbell(const BuzzerPtr& Buzzer, const ButtonPtr& Button)
{
    auto turnBuzzerOn = std::bind( &Buzzer::turnBuzzerOn, Buzzer, 0, "Buzzer turned on." );
    auto turnBuzzerOff = std::bind( &Buzzer::turnBuzzerOff, Buzzer, 0, "Buzzer turned off." );

	while (true)
	{
        Button->pushButton(turnBuzzerOn);
        Button->releaseButton(turnBuzzerOff);
	}
}
