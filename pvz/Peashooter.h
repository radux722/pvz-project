#pragma once

#include "Plant.h"

class Peashooter : public Plant
{
private:
    float shootTimer;

public:
    Peashooter(float x, float y);

    void attack() override;

    bool canShoot(float dt);
};