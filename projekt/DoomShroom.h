#pragma once

#include "Plant.h"

class DoomShroom : public Plant
{
private:
    bool exploded;

public:
    DoomShroom(float x, float y);

    void attack() override;
    void update(float dt) override;

    bool shouldExplode() const;
    void triggerExplosion();
    void onZombieContact(Zombie* zombie) override;
};
