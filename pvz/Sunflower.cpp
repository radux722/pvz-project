#include "Sunflower.h"

Sunflower::Sunflower(float x, float y)
    : Plant(x, y)
{
    shape.setFillColor(sf::Color::Yellow);
    sunTimer= 0.f;
}

void Sunflower::attack()
{
}

void Sunflower::update(float dt)
{
    sunTimer += dt;
    for (auto& plant : plants)
    {
        plant->update(dt);
    }

    for(auto& plant : plants)
    {
        Sunflower* sunflower = dynamic_cast<Sunflower*>(plant.get());

        if(sunflower && sunflower->canProduceSun())
        {
            sunPoints += 25;
        }
    }
}

bool Sunflower::canProduceSun()
{
    if(sunTimer >= 5.f)
    {
        sunTimer = 0.f;
        return true;
    }
    return false;
}
