#pragma once

#include "ComponentDependency.h"
#include <algorithm>
#include <vector>
#include <cmath>

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

  // Flags for what buttons are held
  bool walkingRight;
  bool walkingLeft;
  bool jumping;
  bool floatingRight;
  bool floatingLeft;
  bool usingAb1;
  bool usingAb2;
  bool usingAb3;
  bool usingAb4;
  // bool walkingUp;
  // bool walkingDown;

  bool isIdle();

  bool usingAbility();

  void setWalkingRight();

  void setWalkingLeft();

  void setFloatingRight();

  void setFloatingLeft();

  void clearLeftRight();

  PlayerDataComponent(sf::Vector2f position, sf::Vector2f hitbox, EntityType::Type type, bool isOnGround) : DataComponent(position, sf::Vector2f(0.0, 0.0), hitbox, type, isOnGround), m_hp(100) {}
};






class PlayerPhysicsComponent : public PhysicsComponent
{
private:
  PlayerDataComponent* m_data;

  // Player specific physics properties
  const double WALK_ACCELERATION_GROUND = 0.01;
  const double WALK_ACCELERATION_AIR = 0.25;
  const double IDLE_X_ACCELERATION_GROUND = 0.25;
  const double IDLE_X_ACCELERATION_AIR = 0.1;
  const double JUMP_VELOCITY = 2.0;

public:
  virtual void update(GameObject& object, World& world);

  PlayerPhysicsComponent(PlayerDataComponent* data) : m_data(data) {}
};







class PlayerInputComponent : public InputComponent
{
private:
  // Key bindings
  sf::Keyboard::Key key_right;
  sf::Keyboard::Key key_left;
  // sf::Keyboard::Key key_up;
  // sf::Keyboard::Key key_down;
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
  // key_up(sf::Keyboard::Key::Up), 
  // key_down(sf::Keyboard::Key::Down), 
  key_space(sf::Keyboard::Key::Space),
  key_ab1(sf::Keyboard::Key::Z),
  key_ab2(sf::Keyboard::Key::X),
  key_ab3(sf::Keyboard::Key::C),
  key_ab4(sf::Keyboard::Key::V),
  m_data(data) {}

  virtual void update();
};







class PlayerGraphicsComponent : public GraphicsComponent
{
private:
  PlayerDataComponent* m_data;

  // Player specific animations and sprites
  // PlayerSpriteSheet m_spriteSheet;
  sf::Texture STANDING_TEXTURE;
  sf::Sprite STANDING_SPRITE;

public:
  PlayerGraphicsComponent(PlayerDataComponent* data) : m_data(data)
  {
    bool loaded = STANDING_TEXTURE.loadFromFile("grillStandingSprite.png");
    STANDING_SPRITE.setTexture(STANDING_TEXTURE);
    STANDING_SPRITE.setTextureRect(sf::IntRect(0, 0, 15, 30));
  }

  virtual void update(Graphics& graphics, double frameProgress);
};
