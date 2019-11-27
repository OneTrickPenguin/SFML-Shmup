#include "Pch.h"
#include "Enemy.h"


Enemy::Enemy(const float x, const float y, Scene* s) : Entity(x, y, s)
{
	spr.setTexture(Scene::getTexture(2), true);
}

void Enemy::update(const float deltaTime)
{
	if (red_timer > 0)
	{
		red_timer -= deltaTime;

		float lerp = red_timer / red_recovery;

		if (health <= 0)
		{
			spr.setColor(sf::Color((flash_colour.r - 160) * lerp + 160, (flash_colour.g - 160) * lerp + 160, (flash_colour.b - 160) * lerp + 160));

			if (red_timer <= 0)
			{
				die();
			}
		}
		else
		{
			spr.setColor(sf::Color((flash_colour.r - 255) * lerp + 255, (flash_colour.g - 255) * lerp + 255, (flash_colour.b - 255) * lerp + 255));
		}
	}
}

void Enemy::collided(Entity & other)
{

}

int Enemy::layersSelf() const
{
	return Enemy::layers;
}

int Enemy::layersOther() const
{
	return Enemy::collides;
}

void Enemy::hit(const int damage)
{
	red_timer = red_recovery;

	float lerp = (health / (float)max_health);
	flash_colour = flash_colour_weak + sf::Color(flash_colour_diff.r * lerp, flash_colour_diff.g * lerp, flash_colour_diff.b * lerp);

	health -= damage;

	if (health <= 0)
	{
		canCollide = false;
	}

	spr.setColor(flash_colour);
}

Enemy::~Enemy()
{
}
