#include "Pch.h"
#include "Pilot.h"

Pilot::Pilot(const float x, const float y) : Entity(x, y, 1, 3, true)
{
	spr.setTextureRect(sf::IntRect(192 + 158 * sword_side, 0, 158, 88));
}

void Pilot::update(const float deltaTime)
{
	if (sword_timer <= 0)
	{
		// can attack
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (!sword_pressed)
			{
				sword_side = !sword_side;
				sword_timer = sword_cooldown[0] + sword_cooldown[1];
				sword_pressed = true;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
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
			sword_pressed = false;
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
