#include "Pch.h"
#include "Ship.h"
#include "Bullet.h"

Ship::Ship(const float x, const float y, Player* p, Scene* s) : Entity(x, y, s), player(p)
{
	bbox_origin = sf::Vector2f(64.0f, 22.0f);
	setBBoxSize(128.0f, 48.0f);
	spr.setOrigin(96.0f, 32.0f);
	//spr.setTexture(Scene::getTexture(0), true);
	spr.setTextureRect(sf::IntRect(0, 0, 192, 64));

	//facing = sf::Vector2f(-1.0f, 0.0f);
}

void Ship::setVelocity(sf::Vector2f velocity, bool relative)
{
	vel = (float)relative * vel + velocity;
}

void Ship::update(const float deltaTime)
{
	sf::Vector2f input = sf::Vector2f();
	last_pos = getPosition();

	if (player->getState() == 's')
	{
		input = player->getInput() * max_speed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (!shooting)
			{
				sf::Vector2f bulletVel = sf::Vector2f(bulletSpeed, input.y * 120.0f);
				sf::Vector2f p = getPosition() + sf::Vector2f(10 + last_used_cannon * 45, 12); //(10 or 55, 12)
				spr.setTextureRect(sf::IntRect(0, 64 + 64 * last_used_cannon, 192, 64));
				last_used_cannon = !last_used_cannon;

				cannon_flash_timer = cannon_flash_cooldown;

				getParentScene()->addEntity(new Bullet(p.x, p.y, 1.5f, bulletVel.x, bulletVel.y));
			}
			shooting = true;
		}
		else
		{
			shooting = false;
		}
	}
	else if (player->getState() == 'a')
	{
		vel.x = max_speed * 1.75f;
	}
	else if (getBBoxLeft() > 0)
	{
		vel.x = max_speed * -1.75f;
	}
	else
	{
		isVisible = false;
	}

	if (vel.x != input.x)
	{
		if (vel.x < input.x)
		{
			vel.x += acceleration * deltaTime;
			if (vel.x > input.x)
			{
				vel.x = input.x;
			}
		}
		else
		{
			vel.x -= acceleration * deltaTime;
			if (vel.x < input.x)
			{
				vel.x = input.x;
			}
		}
	}
	if (vel.y != input.y)
	{
		if (vel.y < input.y)
		{
			vel.y += acceleration * deltaTime;
			if (vel.y > input.y)
			{
				vel.y = input.y;
			}
		}
		else
		{
			vel.y -= acceleration * deltaTime;
			if (vel.y < input.y)
			{
				vel.y = input.y;
			}
		}
	}
	movePosition(vel * deltaTime);

	if (getBBoxLeft() < 0)
	{
		movePosition(-getBBoxLeft(), 0);
		if (vel.x < 0)
		{
			vel.x = 0;
		}
	}
	else if (getBBoxRight() > screen_bounds.x)
	{
		movePosition(screen_bounds.x - getBBoxRight(), 0);
		if (vel.x > 0)
		{
			vel.x = 0;
		}
	}

	if (getBBoxTop() < 0)
	{
		movePosition(0, -getBBoxTop());
		if (vel.y < 0)
		{
			vel.y = 0;
		}
	}
	else if (getBBoxBottom() > screen_bounds.y)
	{
		movePosition(0, screen_bounds.y - getBBoxBottom());
		if (vel.y > 0)
		{
			vel.y = 0;
		}
	}

	if (cannon_flash_timer > 0)
	{
		cannon_flash_timer -= deltaTime;
		if (cannon_flash_timer <= 0)
		{
			cannon_flash_timer = 0.0f;
			spr.setTextureRect(sf::IntRect(0, 0, 192, 64));
		}
	}
}

void Ship::collided(Entity & other)
{
	sf::Vector2f move_delta = getPosition() - last_pos;
	sf::Vector2f push_vector;

	if (move_delta.x > 0)
	{
		if (getBBoxRight() > other.getBBoxLeft())
		{
			if (getBBoxRight() - move_delta.x <= other.getBBoxLeft())
			{
				//push_vector.x = -move_delta.x;
				push_vector.x = other.getBBoxLeft() - getBBoxRight() - 0.1f;
				vel.x = 0;
			}
		}
	}
	else if (move_delta.x < 0)
	{
		if (getBBoxLeft() < other.getBBoxRight())
		{
			if (getBBoxLeft() - move_delta.x >= other.getBBoxRight())
			{
				//push_vector.x = -move_delta.x;
				push_vector.x = other.getBBoxRight() - getBBoxLeft() + 0.1f;
				vel.x = 0;
			}
		}
	}

	if (move_delta.y > 0)
	{
		if (getBBoxBottom() > other.getBBoxTop())
		{
			if (getBBoxBottom() - move_delta.y <= other.getBBoxTop())
			{
				//push_vector.y = -move_delta.y;
				push_vector.y = other.getBBoxTop() - getBBoxBottom() - 0.1f;
				vel.y = 0;
			}
		}
	}
	else if (move_delta.y < 0)
	{
		if (getBBoxTop() < other.getBBoxBottom())
		{
			if (getBBoxTop() - move_delta.y >= other.getBBoxBottom())
			{
				//push_vector.y = -move_delta.y;
				push_vector.y = other.getBBoxBottom() - getBBoxTop() + 0.1f;
				vel.y = 0;
			}
		}
	}

	movePosition(push_vector);
}

int Ship::layersSelf() const
{
	return Ship::layers;
}

int Ship::layersOther() const
{
	return Ship::collides;
}

Ship::~Ship()
{
}
