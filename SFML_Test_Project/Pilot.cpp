#include "Pch.h"
#include "Pilot.h"

Pilot::Pilot(const float x, const float y, Player* p) : Entity(x, y), player(p)
{
	bbox_origin = sf::Vector2f(10.0f, 24.0f);
	setBBoxSize(20.0f, 48.0f);
	spr.setOrigin(80.0f, 32.0f);

	spr.setTextureRect(sf::IntRect(192 + 158 * sword_side, 0, 158, 88));
}

void Pilot::setVelocity(sf::Vector2f velocity, bool relative)
{
	vel = (float)relative * vel + velocity;
}

void Pilot::update(const float deltaTime)
{
	sf::Vector2f input = sf::Vector2f();
	last_pos = getPosition();

	if (player->getState() == 'p')
	{
		input = player->getInput() * max_speed;

		vel.y += gravity * deltaTime;
		if (vel.y > terminal_velocity)
		{
			vel.y = terminal_velocity;
		}

		if (sword_pressed)
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				sword_pressed = false;
			}
		}
		else if (!sword_buffering)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				sword_buffering = true;
				down_buffering = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
			}
		}
	}
	else
	{
		vel.y = 0;
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

	if (sword_timer <= 0)
	{
		// can attack
		if (sword_buffering)
		{
			sword_side = !sword_side;
			sword_timer = sword_cooldown[0] + sword_cooldown[1];
			sword_pressed = true;
			sword_buffering = false;

			if (down_buffering)
			{
				spr.setTextureRect(sf::IntRect(192 + 158 * sword_side, 88, 158, 106));
			}
			else
			{
				spr.setTextureRect(sf::IntRect(192 + 158 * sword_side, 194, 158, 106));
			}
		}
	}
	else
	{
		// in attack animation - can't attack
		sword_timer -= deltaTime;
		if (sword_timer <= sword_cooldown[1])
		{
			if (sword_timer <= 0)
			{
				sword_timer = 0;
				spr.setTextureRect(sf::IntRect(192 + 158 * sword_side, 0, 158, 88));

				animation_frame = 0;
			}
			else if (animation_frame == 0)
			{
				sf::IntRect tr = spr.getTextureRect();
				tr.top += 212;
				spr.setTextureRect(tr);

				animation_frame = 1;
			}
		}
	}
}

void Pilot::collided(Entity& other)
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

int Pilot::layersSelf() const
{
	return Pilot::layers;
}

int Pilot::layersOther() const
{
	return Pilot::collides;
}

Pilot::~Pilot()
{
}
