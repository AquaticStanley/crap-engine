#pragma once

#include "ComponentDependency.h"

const double MAX_CAMERA_SPEED = 5.0;

class CameraDataComponent : public DataComponent
{
public:
  DataComponent* m_dataToFollow;
  CameraDataComponent(DataComponent* dataToFollow) : DataComponent(dataToFollow->m_position, dataToFollow->m_velocity, sf::Vector2f(0.0, 0.0), EntityType::Camera, false), m_dataToFollow(dataToFollow) {}
};

class CameraPhysicsComponent : public PhysicsComponent
{
private:
  CameraDataComponent* m_data;
public:
  virtual void update(World& world);

  CameraPhysicsComponent(CameraDataComponent* data) : m_data(data) {}
};

class CameraGraphicsComponent : public GraphicsComponent
{
public:
  virtual void update(Graphics& graphics, double frameProgress);
};

class CameraInputComponent : public InputComponent
{
public:
  virtual void update();
};