#pragma once

#include "Plant.h"

class Peashooter : public Plant
{
public:
    Peashooter(float x, float y);

    void attack() override;
};