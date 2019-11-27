#pragma once
#include "Entity.h"
class Enemy : public Entity
{
private:
	const static int layers = (1 << enemy);
	const static int collides = (1 << wall) | (1 << bullet) | (1 << player);

	int health = 15;
	const int max_health = 15;
	float red_timer = 0;		
	float red_recovery = 0.75;	// time the enemy will flash for

	const sf::Color flash_colour_weak = sf::Color(187, 62, 35);
	const sf::Color flash_colour_diff = sf::Color(72, 155, 136); // this is added to weak, strong colour is (249, 217, 171)
	sf::Color flash_colour;
public:
	Enemy(const float x, const float y, Scene* scene = nullptr);

	void update(const float deltaTime);
	void collided(Entity& other);

	int layersSelf() const;
	int layersOther() const;

	void hit(const int damage);

	~Enemy();
};

