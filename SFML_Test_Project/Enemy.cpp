#include "Pch.h"
#include "Enemy.h"


Enemy::Enemy(const float x, const float y, const sf::Texture* texture) : Entity(x, y, texture)
{

}

void Enemy::update(const float deltaTime)
{

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

Enemy::~Enemy()
{
}
