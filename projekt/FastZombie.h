#pragma once

#include "Zombie.h"

class FastZombie : public Zombie
{
public:
    FastZombie(float x, float y);

    std::string getType() const override
    {
        return "FastZombie";
    }
};