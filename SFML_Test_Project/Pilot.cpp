#include "Pch.h"
#include "Pilot.h"

//Pilot::Pilot(const float x, const float y) : Entity(x, y)
//{
//	spr.setTextureRect(sf::IntRect(192 + 158 * sword_side, 0, 158, 88));
//}

Pilot::Pilot(const float x, const float y, Player* p) : Entity(x, y), player(p)
{
	spr.setTextureRect(sf::IntRect(192 + 158 * sword_side, 0, 158, 88));
}

void Pilot::update(const float deltaTime)
{
	sf::Vector2f input = sf::Vector2f();
	if (!player->isInShip())
	{
		input = player->getInput() * max_speed;

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
