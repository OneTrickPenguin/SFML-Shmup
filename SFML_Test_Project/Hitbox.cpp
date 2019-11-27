#include "Pch.h"
#include "Hitbox.h"

Hitbox::Hitbox(const float x, const float y, const float w, const float h, const float lifetime, const int t, Pilot* p, Scene* s) : Entity(x, y, s), life(lifetime), type(t), parent(p)
{
	spr.setTextureRect(sf::IntRect(0, 0, 0, 0));

	setBBoxSize(w, h);
}

void Hitbox::update(const float deltaTime)
{
	life -= deltaTime;
	if (life < 0)
	{
		die();
	}
}

void Hitbox::collided(Entity& other)
{
	parent->swordHit(type, false);

	Enemy* enemy_ptr = dynamic_cast<Enemy*>(&other);
	if (enemy_ptr)
	{
		enemy_ptr->hit(3);
	}
	
	die();
}

int Hitbox::layersSelf() const
{
	return layers;
}

int Hitbox::layersOther() const
{
	return collides;
}

Hitbox::~Hitbox()
{
}
