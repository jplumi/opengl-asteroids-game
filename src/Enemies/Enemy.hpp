#pragma once

#include "Entity/Entity.hpp"

class Enemy : public Entity
{
public:
    using Entity::Entity;
public:
    void Update(float deltaTime) override; 
    void OnDestroy();
};

