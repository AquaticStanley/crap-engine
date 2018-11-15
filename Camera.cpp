#include "Camera.h"

void CameraPhysicsComponent::update(World& world)
{
  (void)world;
  m_data->m_velocity = m_data->m_dataToFollow->m_position - m_data->m_position;

  if(m_data->m_velocity.x > MAX_CAMERA_SPEED)
  {
    m_data->m_velocity.x = MAX_CAMERA_SPEED;
  }

  if(m_data->m_velocity.x < (MAX_CAMERA_SPEED*-1))
  {
    m_data->m_velocity.x = (MAX_CAMERA_SPEED*-1);
  }

  if(m_data->m_velocity.y > MAX_CAMERA_SPEED)
  {
    m_data->m_velocity.y = MAX_CAMERA_SPEED;
  }

  if(m_data->m_velocity.y < (MAX_CAMERA_SPEED*-1))
  {
    m_data->m_velocity.y = (MAX_CAMERA_SPEED*-1);
  }

  m_data->m_position += m_data->m_velocity;

  return;
}

void CameraGraphicsComponent::update(Graphics& graphics, double frameProgress)
{
  (void)graphics;
  (void)frameProgress;
  return;
}

void CameraInputComponent::update()
{
  return;
}