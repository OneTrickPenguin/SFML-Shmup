#pragma once
#include "Entity.h"
#include "Player.h"

class Player;

class Pilot :
	public Entity
{
private:
	const static int layers = (1 << player);
	const static int collides = (1 << wall) | (1 << enemy);

	Player* player;

	sf::Vector2f vel;
	const float acceleration = 1200;
	const float max_speed = 400;

	float sword_timer = 0.0f;
	const float sword_cooldown[2] = { 0.07f, 0.37f };
	bool sword_side = true; // true = right side, false = left side
	bool sword_pressed = false;
	bool sword_buffering = false;
	bool down_buffering = false;
public:
	Pilot(const float x, const float y, Player* p);
	
	void update(const float deltaTime);
	void collided(Entity& other);

	int layersSelf() const;
	int layersOther() const;

	~Pilot();
};

