#include "Pch.h"
#include "Player.h"
//#include "Ship.h"
//#include "Pilot.h"
#include "Bullet.h"

Player::Player(const float x, const float y, Scene* s) : Entity(x, y, s), ship(new Ship(x, y, this, s)), pilot(new Pilot(x, y, this, s))
{
	canCollide = false;
	isVisible = false;

	pilot->isVisible = false;
	pilot->canCollide = false;
}

char Player::getState()
{
	return state;
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
		//getParentScene()->addEntity(ship);
		//getParentScene()->addEntity(pilot);
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
			if (state == 's')
			{	// if in ship, become pilot (eject from ship)
				state = 'p';
				call_timer = call_cooldown;

				ship->canCollide = false;
				ship->setVelocity(sf::Vector2f(-800.0f, 0.0f));

				pilot->isVisible = true;
				pilot->canCollide = true;
				pilot->setPosition(ship->getPosition());
				pilot->setVelocity(sf::Vector2f(400.0f, -400.0f));
			}
			else if (state == 'p' && call_timer <= 0)
			{	// if not in ship, play animation to enter ship
				state = 'a';

				ship->isVisible = true;
				sf::Vector2f start_pos = pilot->getPosition();
				start_pos.x = 0.0f;
				ship->setPosition(start_pos);
				ship->setVelocity(sf::Vector2f(600.0f, 0.0f));

				pilot->canCollide = false;
			}
		}
		change_pressed = true;
	}
	else
	{
		change_pressed = false;
	}

	if (call_timer > 0)
	{
		call_timer -= deltaTime;
	}

	if (state == 'a')
	{
		if (ship->getPosition().x + 64.0f > pilot->getPosition().x)
		{
			state = 's';

			ship->canCollide = true;

			pilot->isVisible = false;
		}
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
