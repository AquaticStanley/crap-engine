#include "GameObject.h"

void GameObject::updateInput()
{
  m_input->update();
}

void GameObject::updatePhysics(World& world)
{
  m_physics->update(world);
}

void GameObject::updateGraphics(World& world, Graphics& graphics, double frameProgress)
{
  (void)world;
  m_graphics->update(graphics, frameProgress);
}