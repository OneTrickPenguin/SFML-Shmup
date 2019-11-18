#pragma once
#include "Entity.h"
#include "Ship.h"
#include "Pilot.h"
class Player : public Entity
{
private:
	const static int layers = 0;
	const static int collides = 0;

	const sf::Keyboard::Key change = sf::Keyboard::Space;
	const sf::Keyboard::Key attack = sf::Keyboard::D;

	Ship* ship;
	Pilot* pilot;
	bool defined = false;

	const float call_cooldown = 3.0f;
	float call_timer = 0.0f;
	bool change_pressed = false;
	char state = 's'; // s: in ship,
					  // p: pilot (out of ship)
					  // a: in animation (entering ship)
	sf::Vector2f input;
public:
	Player(const float x, const float y);
	
	char getState();
	sf::Vector2f getInput();

	void update(const float deltaTime);
	void collided(Entity& other);

	int layersSelf() const;
	int layersOther() const;

	~Player();
};

