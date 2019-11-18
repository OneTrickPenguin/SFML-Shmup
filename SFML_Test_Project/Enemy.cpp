#include "Pch.h"
#include "Enemy.h"


Enemy::Enemy(const float x, const float y, Scene* s) : Entity(x, y, s)
{
	spr.setTexture(Scene::getTexture(2), true);
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
