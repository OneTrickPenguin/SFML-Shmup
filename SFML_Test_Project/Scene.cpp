#include "Pch.h"
#include "Scene.h"
#include <string>

std::vector<sf::Texture*> Scene::textures;

Scene::Scene()
{
}

void Scene::addTexture(const std::string& filePath)
{
	textures.push_back(new sf::Texture());
	textures.back()->loadFromFile(filePath);
}

sf::Texture* Scene::getTexture(const int id)
{
	return textures.at(id);
}

void Scene::destroyTextures()
{
	int count = textures.size();
	for (int i = 0; i < count; i++)
	{
		delete textures[i];
	}
}

void Scene::addEntity(Entity* entity)
{
	entities.push_back(entity);
	entity->assignParentScene(this);
}

int Scene::entityCount() const
{
	return entities.size();
}

void Scene::update(const float deltaTime)
{
	// update() loop - update all entities
	for (int i = 0; i < entities.size(); i++)
	{
		// Check if the entity is alive - if entities are dead, just skip over them here so the loop still functions correctly, and remove and destroy them after the loop
		if (entities[i]->isAlive())
		{
			// Classes inheriting from Entity can provide their own behaviour in update(), as it is a virtual function
			entities[i]->update(deltaTime);

			if (!entities[i]->isAlive())
			{
				delete entities[i];
				entities.erase(entities.begin() + i);
				i--;
			}
		}
	}
}

void Scene::checkCollision()
{
	// Collided() loop - check collisions between all entities
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->canCollide)
		{
			// starts at j = i + 1 since there's no point checking if the object would collide with itself (j = i)
			// it also means for a collision between, say, 1 & 3, i = 1 and j = 3 will be checked, but i = 3 and j = 1 will not, since we already know the result
			for (int j = i + 1; j < entities.size(); j++)
			{
				if (entities[j]->canCollide)
				{
					// check the entities share a common layer
					if ((entities[i]->layersSelf() & entities[j]->layersOther()) != 0 || (entities[j]->layersSelf() & entities[i]->layersOther()) != 0)
					{
						// get the sf::Rect bounding boxes from both entities involved and compare them
						if (entities[i]->getBBoxBounds().intersects(entities[j]->getBBoxBounds()))
						{
							// call collided() on both entities - i collides with j, and j collides with i
							// this is because, as mentioned above, these 2 entities won't be compared again this frame. 
							entities[i]->collided(*entities[j]);
							entities[j]->collided(*entities[i]);
						}
					}
				}
			}

			if (!entities[i]->isAlive())
			{
				delete entities[i];
				entities.erase(entities.begin() + i);
				i--;
			}
		}
	}
}

void Scene::draw(sf::RenderTarget & renderTarget, const sf::RenderStates & renderStates) const
{
	// draw() loop - draw all entities
	// It's safe to assume we won't be creating or destroying anything in draw(), so we can store the size to avoid calculating it every iteration
	int count = entities.size();
	for (int i = 0; i < count; i++)
	{
		if (entities[i]->isVisible)
		{
			entities[i]->draw(renderTarget);
		}
	}
}

Scene::~Scene()
{
	int count = entities.size();
	for (int i = 0; i < count; i++)
	{
		delete entities[i];
	}
}
