#include "Pch.h"
#include "Player.h"
#include "Bullet.h"

Player::Player(const float x, const float y) : Entity(x, y)
{
	bbox_origin = sf::Vector2f(64.0f, 22.0f);
	setBBoxSize(128.0f, 48.0f);
	spr.setOrigin(96.0f, 32.0f);
	//spr.setTexture(Scene::getTexture(0), true);
	spr.setTextureRect(sf::IntRect(0, 0, 192, 64));

	facing = sf::Vector2f(-1.0f, 0.0f);
}

void Player::update(const float deltaTime)
{
	last_pos = getPosition();
	sf::Vector2f input;
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

		facing = input;
	}

	movePosition(input * moveSpeed * deltaTime);

	if (getBBoxLeft() < 0)
	{
		movePosition(-getBBoxLeft(), 0);
	}
	else if (getBBoxRight() > screen_bounds.x)
	{
		movePosition(screen_bounds.x - getBBoxRight(), 0);
	}

	if (getBBoxTop() < 0)
	{
		movePosition(0, -getBBoxTop());
	}
	else if (getBBoxBottom() > screen_bounds.y)
	{
		movePosition(0, screen_bounds.y - getBBoxBottom());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (!shooting)
		{
			sf::Vector2f bulletVel = sf::Vector2f(bulletSpeed, 0.0f);
			sf::Vector2f p = getPosition() + sf::Vector2f(47 + last_used_cannon * 45, 12); //(47 or 92, 12)
			last_used_cannon = !last_used_cannon;
			getParentScene()->addEntity(new Bullet(p.x, p.y, 1.5f, bulletVel.x, bulletVel.y));
		}
		shooting = true;
	}
	else
	{
		shooting = false;
	}
}

void Player::collided(Entity& other)
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
				push_vector.x = other.getBBoxLeft() - getBBoxRight() - 0.01f;
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
				push_vector.x = other.getBBoxRight() - getBBoxLeft() + 0.01f;
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
				push_vector.y = other.getBBoxTop() - getBBoxBottom() - 0.01f;
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
				push_vector.y = other.getBBoxBottom() - getBBoxTop() + 0.01f;
			}
		}
	}

	movePosition(push_vector);
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
