#include "Pch.h"
#include "Player.h"
//#include "Ship.h"
//#include "Pilot.h"
#include "Bullet.h"

Player::Player(const float x, const float y) : Entity(x, y), ship(new Ship(x, y, this)), pilot(new Pilot(x, y, this))
{
	canCollide = false;
	isVisible = false;
}

bool Player::isInShip()
{
	return in_ship;
}

sf::Vector2f Player::getInput()
{
	return input;
}

void Player::update(const float deltaTime)
{
	input = sf::Vector2f();

	if (!defined)
	{
		defined = true;
		getParentScene()->addEntity(ship);
		getParentScene()->addEntity(pilot);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		input.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		input.x++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		input.y--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		input.y++;
	
	float hyp = sqrt(input.x * input.x + input.y * input.y);
	if (hyp != 0)
	{
		if (hyp > 1)
		{
			input.x /= hyp;
			input.y /= hyp;
		}
	}

	if (sf::Keyboard::isKeyPressed(change))
	{
		if (!change_pressed)
		{
			in_ship = !in_ship;
		}
		change_pressed = true;
	}
	else
	{
		change_pressed = false;
	}
}

void Player::collided(Entity& other)
{
	
}

int Player::layersSelf() const
{
	return Player::layers;
}

int Player::layersOther() const
{
	return Player::collides;
}

Player::~Player()
{
}
