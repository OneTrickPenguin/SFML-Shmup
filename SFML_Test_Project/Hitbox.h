#pragma once
#include "Entity.h"
class Hitbox :
	public Entity
{
private:
	const static int layers = (1 << bullet);
	const static int collides = (1 << wall) | (1 << enemy);

	float life;
	int type;
	Pilot* parent;
public:
	Hitbox(const float x, const float y, const float width, const float height, const float lifetime, const int type, Pilot* parent, Scene* scene = nullptr);

	void update(const float deltaTime);
	void collided(Entity& other);

	int layersSelf() const;
	int layersOther() const;

	~Hitbox();
};

