// Name: Instruction.hpp
// Author: crdrisko
// Date: 08/25/2023-15:58:22
// Description:

#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cassert>

enum Instruction
{
    INST_SET_HEALTH      = 0x00,
    INST_SET_WISDOM      = 0x01,
    INST_SET_AGILITY     = 0x02,
    INST_PLAY_SOUND      = 0x03,
    INST_SPAWN_PARTICLES = 0x04,
    INST_LITERAL         = 0x05,
    INST_GET_HEALTH      = 0x06,
    INST_GET_WISDOM      = 0x07,
    INST_GET_AGILITY     = 0x08,
    INST_ADD             = 0x09,
    INST_SUBTRACT        = 0x10,
    INST_MULTIPLY        = 0x11,
    INST_DIVIDE          = 0x12
};

enum Sounds
{
    SOUND_BANG
};

enum ParticleEffects
{
    PARTICLE_FLAME
};

void setHealth(int wizard, int ammount);
void setWisdom(int wizard, int ammount);
void setAgility(int wizard, int ammount);


void playSound(int soundId);
void spawnParticles(int particleType);

int getHealth(int wizard);
int getWisdom(int wizard);
int getAgility(int wizard);

class VM
{
public:
    VM() : stackSize_(0) {}

    void interpret(char bytecode[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            char instruction = bytecode[i];

            switch (instruction)
            {
            case INST_SET_HEALTH:
            {
                int amount = pop();
                int wizard = pop();
                setHealth(wizard, amount);
                break;
            }
            case INST_SET_WISDOM:
            {
                int amount = pop();
                int wizard = pop();
                setWisdom(wizard, amount);
                break;
            }
            case INST_SET_AGILITY:
            {
                int amount = pop();
                int wizard = pop();
                setAgility(wizard, amount);
                break;
            }
            case INST_PLAY_SOUND:
            {
                playSound(SOUND_BANG);
                break;
            }
            case INST_SPAWN_PARTICLES:
            {
                spawnParticles(PARTICLE_FLAME);
                break;
            }
            case INST_LITERAL:
            {
                // Read the next byte from the bytecode
                int value = bytecode[++i];
                push(value);
                break;
            }
            case INST_GET_HEALTH:
            {
                int wizard = pop();
                push(getHealth(wizard));
                break;
            }
            case INST_GET_WISDOM:
            {
                int wizard = pop();
                push(getWisdom(wizard));
                break;
            }
            case INST_GET_AGILITY:
            {
                int wizard = pop();
                push(getAgility(wizard));
                break;
            }
            case INST_ADD:
            {
                int b = pop();
                int a = pop();
                push(a + b);
                break;
            }
            case INST_SUBTRACT:
            {
                int b = pop();
                int a = pop();
                push(a - b);
                break;
            }
            case INST_MULTIPLY:
            {
                int b = pop();
                int a = pop();
                push(a * b);
                break;
            }
            case INST_DIVIDE:
            {
                int b = pop();
                int a = pop();
                push(a / b);
                break;
            }
            }
        }
    }

private:
    void push(int value)
    {
        // Check for stack overflow
        assert(stackSize_ < MAX_STACK);
        stack_[stackSize_++] = value;
    }

    int pop()
    {
        // Make sure the stack isn't empty
        assert(stackSize_ > 0);
        return stack_[--stackSize_];
    }

    static const int MAX_STACK = 128;
    int stackSize_;
    int stack_[MAX_STACK];
};


#endif
