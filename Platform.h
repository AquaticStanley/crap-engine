#pragma once

#include "ComponentDependency.h"

class PlatformDataComponent : public DataComponent
{
public:
  PlatformDataComponent(sf::Vector2f position, sf::Vector2f hitbox) : DataComponent(position, sf::Vector2f(0.0, 0.0), hitbox, EntityType::Platform, false) {}
};


class PlatformPhysicsComponent : public PhysicsComponent
{
public:
  virtual void update(World& world);
};




class PlatformGraphicsComponent : public GraphicsComponent
{
private:
  PlatformDataComponent* m_data;
public:
  PlatformGraphicsComponent(PlatformDataComponent* data) : m_data(data) {}

  virtual void update(Graphics& graphics, double frameProgress);
};





class PlatformInputComponent : public InputComponent
{
public:
  virtual void update();
};