#pragma once
#include "Entity.h"
class Bullet : public Entity
{
private:
	const static int layers = (1 << bullet);
	const static int collides = (1 << wall) | (1 << enemy);

	sf::Vector2f vel;
	float life;
public:
	Bullet(const float x, const float y, const sf::Texture* texture, const float lifetime, const float dx = 0, const float dy = 0);

	void update(const float deltaTime);
	void collided(Entity& other);

	int layersSelf() const;
	int layersOther() const;

	~Bullet();
};

