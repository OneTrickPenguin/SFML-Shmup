#pragma once
#include "Entity.h"
#include "Player.h"

class Player;

class Ship :
	public Entity
{
private:
	const static int layers = (1 << player);
	const static int collides = (1 << wall) | (1 << enemy);

	Player* player;

	sf::Vector2f last_pos;
	sf::Vector2f vel;
	const float acceleration = 1800;
	const float max_speed = 600;

	float bulletSpeed = 800.0f; // pixels per second
	float cannon_flash_timer = 0.0f;
	const float cannon_flash_cooldown = 0.12f;
	bool last_used_cannon = true; // true = left cannon (x = 10), false = right cannon (x = 55)
	bool shooting = false;
	sf::Vector2f facing;
public:
	Ship(const float x, const float y, Player* p, Scene* scene = nullptr);

	void setVelocity(sf::Vector2f velocity, bool relative = false);

	void update(const float deltaTime);
	void collided(Entity& other);

	int layersSelf() const;
	int layersOther() const;

	~Ship();
};

