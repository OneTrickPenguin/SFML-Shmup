#pragma once
#include "Entity.h"
#include "Ship.h"
#include "Pilot.h"
class Player : public Entity
{
private:
	const static int layers = 0;
	const static int collides = 0;

	const static sf::Keyboard::Key change = sf::Keyboard::Space;
	const static sf::Keyboard::Key attack = sf::Keyboard::D;

	Ship* ship;
	Pilot* pilot;
	bool defined = false;

	bool change_pressed = false;
	bool in_ship = true;
	sf::Vector2f input;
public:
	Player(const float x, const float y);
	
	bool isInShip();
	sf::Vector2f getInput();

	void update(const float deltaTime);
	void collided(Entity& other);

	int layersSelf() const;
	int layersOther() const;

	~Player();
};

