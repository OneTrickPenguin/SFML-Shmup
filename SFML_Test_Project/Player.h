#pragma once
#include "Entity.h"
class Player : public Entity
{
private:
	const static int layers = (1 << player);
	const static int collides = (1 << wall) | (1 << enemy);

	float moveSpeed = 512.0f; // pixels per second
	float bulletSpeed = 768.0f; // pixels per second
	bool shooting = false;
	sf::Vector2f last_pos;
	sf::Vector2f facing;
public:
	Player(const float x, const float y, const sf::Texture* texture);
	
	void update(const float deltaTime);
	void collided(Entity& other);

	int layersSelf() const;
	int layersOther() const;

	~Player();
};

