#pragma once

#include "Entity/Entity.hpp"

class Asteroid : public Entity
{
public:
    using Entity::Entity;
public:
    void Update(float deltaTime) override; 
    void OnDestroy();
};

