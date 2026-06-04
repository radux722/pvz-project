#pragma once

#include "Plant.h"

class Sunflower : public Plant
{
public:
    Sunflower(float x, float y);

    bool canProduceSun();

    void attack() override;
private:
    float sunTimer;
};
