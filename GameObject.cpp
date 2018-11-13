#include "GameObject.h"

void GameObject::updateInput()
{
  m_input->update();
}

void GameObject::updatePhysics(World& world)
{
  m_physics->update(*this, world);
}

void GameObject::updateGraphics(World& world, Graphics& graphics, double frameProgress)
{
  (void)world;
  m_graphics->update(*this, graphics, frameProgress);
}