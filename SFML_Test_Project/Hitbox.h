#pragma once
#include "Entity.h"
class Hitbox :
	public Entity
{
private:
	const static int layers = (1 << bullet);
	const static int collides = (1 << wall) | (1 << enemy);

	float life;
public:
	Hitbox(const float x, const float y, const float width, const float height, const float lifetime, Scene* scene);

	void update(const float deltaTime);
	void collided(Entity& other);

	int layersSelf() const;
	int layersOther() const;

	~Hitbox();
};

