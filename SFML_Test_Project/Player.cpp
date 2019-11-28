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

sf::Vector2f Player::getInputAxes()
{
	return input_axes;
}

char Player::getInputButtons()
{
	return input_buttons;
}

char Player::getInputButtonsPressed()
{
	return (input_buttons & ~prev_buttons);
	// prev_buttons	 | 0  0  1  1 |
	// input_buttons | 0  1  0  1 |
	// ~prev_buttons | 1  1  0  0 |
	// return		 | 0  1  0  0 |
}

char Player::getInputButtonsReleased()
{
	return (~input_buttons & prev_buttons);
	// prev_buttons	  | 0  0  1  1 |
	// input_buttons  | 0  1  0  1 |
	// ~input_buttons | 1  0  1  0 |
	// return		  | 0  0  1  0 |
}

void Player::update(const float deltaTime)
{
	prev_buttons = input_buttons;
	input_buttons = (sf::Keyboard::isKeyPressed(key_attack_l) << 0)
				  | (sf::Keyboard::isKeyPressed(key_attack_h) << 1)
				  | (sf::Keyboard::isKeyPressed(key_dash) << 4)
				  | (sf::Keyboard::isKeyPressed(key_change) << 7);
	input_axes = sf::Vector2f();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		input_axes.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		input_axes.x++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		input_axes.y--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		input_axes.y++;
	
	float hyp = sqrt(input_axes.x * input_axes.x + input_axes.y * input_axes.y);
	if (hyp != 0)
	{
		if (hyp > 1)
		{
			input_axes.x /= hyp;
			input_axes.y /= hyp;
		}
	}

	if (getInputButtonsPressed() & (1 << 7))
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
	else
	{
		
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
