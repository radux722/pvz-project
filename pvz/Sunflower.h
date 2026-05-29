#pragma once

#include "Plant.h"

class Sunflower : public Plant
{
public:
    Sunflower(float x, float y);

    void attack() override;
};