#include "Pellet.h"

void PelletGraphicsComponent::update(Graphics& graphics, double frameProgress)
{
  sf::Vector2f predictedPosition = m_data->m_position + sf::Vector2f(m_data->m_velocity.x * frameProgress, m_data->m_velocity.y * frameProgress);

  graphics.draw(predictedPosition, m_data->m_hitbox, sf::Color::Cyan);

  return;
}