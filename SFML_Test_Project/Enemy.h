#pragma once
#include "Entity.h"
class Enemy : public Entity
{
private:
	const static int layers = (1 << enemy);
	const static int collides = (1 << wall) | (1 << bullet) | (1 << player);
public:
	Enemy(const float x, const float y, const sf::Texture* texture);

	void update(const float deltaTime);
	void collided(Entity& other);

	int layersSelf() const;
	int layersOther() const;

	~Enemy();
};

