#pragma once
#include <memory>
#include <string>
#include "BasicZombie.h"
#include "FastZombie.h"
#include "TankZombie.h"
#include "BossZombie.h"
#include "BerserkerZombie.h"

// Wzorzec Projektowy
class ZombieFactory {
public:
    static std::unique_ptr<Zombie> createZombie(const std::string& type, float x, float y) {
        if (type == "BasicZombie") return std::make_unique<BasicZombie>(x, y);
        if (type == "FastZombie") return std::make_unique<FastZombie>(x, y);
        if (type == "TankZombie") return std::make_unique<TankZombie>(x, y);
        if (type == "BossZombie") return std::make_unique<BossZombie>(x, y);
        if (type == "BerserkerZombie") return std::make_unique<BerserkerZombie>(x, y);
        return nullptr;
    }
};