#pragma once

#include "Plant.h"

class DoomShroom : public Plant
{
private:
    float fuseTimer;
    bool exploded;

public:
    DoomShroom(float x, float y);

    void attack() override;
    void update(float dt) override;

    bool shouldExplode() const;
};
