#pragma once

#include "ComponentDependency.h"
#include <cmath>

class BulletDataComponent : public DataComponent
{
public:
  int activeFrames;
  BulletDataComponent(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f hitbox) : DataComponent(position, velocity, hitbox, EntityType::PlayerProjectile, false), activeFrames(100) {}
};

class BulletPhysicsComponent : public PhysicsComponent
{
private:
  BulletDataComponent* m_data;
public:
  virtual void update(World& world);

  BulletPhysicsComponent(BulletDataComponent* data) : m_data(data) {}
};

class BulletGraphicsComponent : public GraphicsComponent
{
private:
  BulletDataComponent* m_data;
public:
  BulletGraphicsComponent(BulletDataComponent* data) : m_data(data) {}

  virtual void update(Graphics& graphics, double frameProgress);
};

class BulletInputComponent : public InputComponent
{
public:
  virtual void update();
};