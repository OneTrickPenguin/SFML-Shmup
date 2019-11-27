#include "Pch.h"
#include "Bullet.h"

Bullet::Bullet(const float x, const float y, const float lifetime, const float dx, const float dy) : Entity(x, y, 30, 6, false)
{
	life = lifetime;
	vel = sf::Vector2f(dx, dy);

	/*
	bbox_origin = sf::Vector2f(32.0f, 32.0f);
	spr.setOrigin(64.0f, 64.0f);
	spr.setTexture(Scene::getTexture(1), true);

	spr.setScale(0.5f, 0.5f);
	setBBoxSize(64.0f, 64.0f);/**/
	/*
	spr.setOrigin(32.0f, 32.0f);
	spr.setTextureRect(sf::IntRect(0, 0, 64, 64));

	setBBoxSize(64.0f, 64.0f);

	animation_speed = 5;
	animation_total_frames = 4;/**/

	spr.setOrigin(8.0f, 5.0f);
	//spr.setTextureRect(sf::IntRect(64, 64, 16, 10));
	spr.setTextureRect(sf::IntRect(16, 192, 64, 7));

	setBBoxSize(64.0f, 12.0f);
	bbox_origin = sf::Vector2f(8.0f, 7.0f);

	//animation_speed = 18;
	//animation_total_frames = 6;
}

void Bullet::update(const float deltaTime)
{
	Entity::update(deltaTime);

	movePosition(vel * deltaTime);

	life -= deltaTime;
	if (life < 0)
	{
		die();
	}
}

void Bullet::collided(Entity& other)
{
	Enemy* enemy_ptr = dynamic_cast<Enemy*>(&other);
	if (enemy_ptr)
	{
		enemy_ptr->hit(2);
	}

	die();
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
