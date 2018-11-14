#pragma once

#include "ComponentDependency.h"

class BulletDataComponent;

class PelletGraphicsComponent : public GraphicsComponent
{
private:
  BulletDataComponent* m_data;
public:
  PelletGraphicsComponent(BulletDataComponent* data) : m_data(data) {}

  virtual void update(Graphics& graphics, double frameProgress);
};