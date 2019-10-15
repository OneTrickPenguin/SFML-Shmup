#include "Pch.h"
#include "Bullet.h"


Bullet::Bullet(const float x, const float y, const sf::Texture* texture, const float lifetime, const float dx, const float dy) : Entity(x, y, texture)
{
	life = lifetime;
	vel = sf::Vector2f(dx, dy);

	bbox_origin = sf::Vector2f(32.0f, 32.0f);
	spr.setOrigin(64.0f, 64.0f);

	spr.setScale(0.5f, 0.5f);
	setBBoxSize(64.0f, 64.0f);
}

void Bullet::update(const float deltaTime)
{
	movePosition(vel * deltaTime);

	life -= deltaTime;
	if (life < 0)
	{
		die();
	}
}

void Bullet::collided(Entity & other)
{

}

int Bullet::layersSelf() const
{
	return Bullet::layers;
}

int Bullet::layersOther() const
{
	return Bullet::collides;
}

Bullet::~Bullet()
{
}
