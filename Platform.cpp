#include "Platform.h"

void PlatformPhysicsComponent::update(World& world)
{
  (void)world;
  return;
}

void PlatformGraphicsComponent::update(Graphics& graphics, double frameProgress)
{
  (void)frameProgress;
  graphics.draw(m_data->m_position, m_data->m_hitbox, sf::Color::White);
  return;
}

void PlatformInputComponent::update()
{

}