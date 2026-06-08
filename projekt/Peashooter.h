#pragma once

#include "Plant.h"

class Peashooter : public Plant
{
private:
    float shootTimer;

public:
    Peashooter(float x, float y);

    void attack() override;

    void update(float dt) override;

    bool canShoot() const;
    void resetShootTimer();
};