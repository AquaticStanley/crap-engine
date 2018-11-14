#include "Bullet.h"

void BulletPhysicsComponent::update(World& world)
{
  m_data->activeFrames--;
  if(m_data->activeFrames <= 0)
  {
    m_data->m_toBeRemoved = true;
  }

  // Set bullet's position due to velocity
  m_data->m_position += m_data->m_velocity;

  // Resolve world collisions
  world.resolveBulletCollision(m_data);

  return;
}

void BulletGraphicsComponent::update(Graphics& graphics, double frameProgress)
{
  sf::Vector2f predictedPosition = m_data->m_position + sf::Vector2f(m_data->m_velocity.x * frameProgress, m_data->m_velocity.y * frameProgress);

  graphics.draw(predictedPosition, m_data->m_hitbox, sf::Color::Yellow);

  return;
}

void BulletInputComponent::update()
{

}