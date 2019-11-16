#pragma once
#include "Entity.h"
class Pilot :
	public Entity
{
private:
	const static int layers = (1 << player);
	const static int collides = (1 << wall) | (1 << enemy);

	float sword_timer = 0.0f;
	const float sword_cooldown[2] = { 0.07f, 0.23f };
	bool sword_side = true; // true = right side, false = left side
	bool sword_pressed = false;
public:
	Pilot(const float x, const float y);
	
	void update(const float deltaTime);
	void collided(Entity& other);

	int layersSelf() const;
	int layersOther() const;

	~Pilot();
};

