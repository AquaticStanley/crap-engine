#pragma once

#include "ComponentDependency.h"
#include <algorithm>

class PlayerSpriteSheet : public SpriteSheet
{
private:
  static std::map<std::string, std::string> s_spriteMap;

public:
  std::string operator [](std::string spriteName);
};





class PlayerDataComponent : public DataComponent
{
public:
  int m_hp;
  bool isOnGround;

  PlayerDataComponent(sf::Vector2f position, sf::Vector2f hitbox, EntityType::Type type) : DataComponent(position, sf::Vector2f(0.0, 0.0), hitbox, type), m_hp(100), isOnGround(false) {}
};






class PlayerPhysicsComponent : public PhysicsComponent
{
private:
  PlayerDataComponent* m_data;

public:
  virtual void update(GameObject& object, World& world);

  PlayerPhysicsComponent(PlayerDataComponent* data) : m_data(data) {}
};







class PlayerInputComponent : public InputComponent
{
private:
  // Player specific physics properties
  const double WALK_ACCELERATION_GROUND = 0.5;
  const double WALK_ACCELERATION_AIR = 0.25;
  const double IDLE_X_ACCELERATION_GROUND = 0.25;
  const double IDLE_X_ACCELERATION_AIR = 0.1;
  const double JUMP_VELOCITY = 2.0;

  // Key bindings
  sf::Keyboard::Key key_right;
  sf::Keyboard::Key key_left;
  sf::Keyboard::Key key_up;
  sf::Keyboard::Key key_down;
  sf::Keyboard::Key key_space;
  sf::Keyboard::Key key_ab1;
  sf::Keyboard::Key key_ab2;
  sf::Keyboard::Key key_ab3;
  sf::Keyboard::Key key_ab4;

  PlayerDataComponent* m_data;

public:
  PlayerInputComponent(PlayerDataComponent* data) : 
  key_right(sf::Keyboard::Key::Right), 
  key_left(sf::Keyboard::Key::Left), 
  key_up(sf::Keyboard::Key::Up), 
  key_down(sf::Keyboard::Key::Down), 
  key_space(sf::Keyboard::Key::Space),
  key_ab1(sf::Keyboard::Key::Z),
  key_ab2(sf::Keyboard::Key::X),
  key_ab3(sf::Keyboard::Key::C),
  key_ab4(sf::Keyboard::Key::V),
  m_data(data) {}

  virtual void update(GameObject& object);
};







class PlayerGraphicsComponent : public GraphicsComponent
{
private:
  PlayerDataComponent* m_data;

  // Player specific animations and sprites
  PlayerSpriteSheet m_spriteSheet;

public:
  PlayerGraphicsComponent(PlayerDataComponent* data) : m_data(data)
  {

  }

  virtual void update(GameObject& object, Graphics& graphics, double frameProgress);
};
