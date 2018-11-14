#pragma once

#include "ComponentDependency.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <functional>

const int PLAYER_BULLET_VELOCITY = 7.0;
const int PLAYER_BULLET_WIDTH = 6.0;
const int PLAYER_BULLET_HEIGHT = 3.0;

const double SHOTGUN_CONE_WIDTH = 3.0;
const int NUM_SHOTGUN_PELLETS = 7;

const double BLINK_DISTANCE = 50.0;

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
  bool facingRight;
  bool walkingRight;
  bool walkingLeft;
  bool jumping;
  bool floatingRight;
  bool floatingLeft;
  bool canMove;

  bool ab1Activated;
  bool ab2Activated;
  bool ab3Activated;
  bool ab4Activated;

  bool abilityIP;
  bool jumpIP;
  // sf::Vector2f positionMod;
  // bool walkingUp;
  // bool walkingDown;

  std::vector<std::function<std::vector<GameObject>(World&)>> abilities;

  // Ability functions
  // passives?
  std::vector<GameObject> bullet(World& world);

  std::vector<GameObject> shotgun(World& world);

  std::vector<GameObject> blink(World& world);

  // std::vector<GameObject> hookshot(World& world);

  // Generic functions

  bool isIdle();

  bool anyAbilitiesActivated();

  bool anyAbilitiesInProgress();

  void setWalkingRight();

  void setWalkingLeft();

  void setFloatingRight();

  void setFloatingLeft();

  void clearLeftRight();

  void clearAbilityActivatedFlags();

  sf::Vector2f getProjectileStartingPos(World& world);

  PlayerDataComponent(sf::Vector2f position, sf::Vector2f hitbox, EntityType::Type type, bool isOnGround) : 
  DataComponent(position, sf::Vector2f(0.0, 0.0), hitbox, type, isOnGround),
   m_hp(100),
   canMove(true),
   ab1Activated(false),
   ab2Activated(false),
   ab3Activated(false),
   ab4Activated(false),
   abilityIP(false)
   // positionMod(0.0, 0.0)
   {
     abilities.resize(4);

     abilities[0] = [&] (World& world) {
      return this->bullet(world);
     };

     abilities[1] = [&] (World& world) {
      return this->shotgun(world);
     };

     abilities[2] = [&] (World& world) {
      return this->blink(world);
     };
   }
};






class PlayerPhysicsComponent : public PhysicsComponent
{
private:
  PlayerDataComponent* m_data;

  // Player specific physics properties
  const double WALK_ACCELERATION_GROUND = 0.30;
  const double WALK_ACCELERATION_AIR = 0.30;
  const double IDLE_X_ACCELERATION_GROUND = 0.25;
  const double IDLE_X_ACCELERATION_AIR = 0.5;
  const double JUMP_VELOCITY = 3.0;

public:
  virtual void update(World& world);

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
    STANDING_TEXTURE.loadFromFile("grillStandingSprite.png");
    STANDING_SPRITE.setTexture(STANDING_TEXTURE);
    STANDING_SPRITE.setTextureRect(sf::IntRect(0, 0, 15, 30));
  }

  virtual void update(Graphics& graphics, double frameProgress);
};
