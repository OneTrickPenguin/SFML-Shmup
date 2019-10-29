#include "Pch.h"
#include "Entity.h"

sf::Texture Entity::texture_page;

Entity::Entity(const float x, const float y)
{
	//bbox.width = 128.0f;
	//bbox.height = 128.0f;
	bbox_origin = sf::Vector2f();
	setPosition(x, y);
}

Entity::Entity(const float x, const float y, const int anim_speed, const int anim_frames) : 
	animation_speed(anim_speed), animation_total_frames(anim_frames)
{
	bbox_origin = sf::Vector2f();
	setPosition(x, y);
}

bool Entity::isAlive() const
{
	return alive;
}

void Entity::die()
{
	alive = false;
}

void Entity::setBBoxSize(const float width, const float height)
{
	bbox.width = width;
	bbox.height = height;
}

void Entity::updateSprite()
{
	spr.setPosition(pos);
}

void Entity::updateBBox()
{
	bbox.left = pos.x - bbox_origin.x;
	bbox.top = pos.y - bbox_origin.y;
}

sf::Vector2f Entity::getPosition() const
{
	return pos;
}

void Entity::setPosition(sf::Vector2f position)
{
	pos = position;

	updateSprite();
	updateBBox();
}

void Entity::setPosition(float x, float y)
{
	pos.x = x;
	pos.y = y;

	updateSprite();
	updateBBox();
}

void Entity::movePosition(sf::Vector2f delta)
{
	pos += delta;
	
	updateSprite();
	updateBBox();
}

void Entity::movePosition(float dx, float dy)
{
	pos += sf::Vector2f(dx, dy);
	
	updateSprite();
	updateBBox();
}

float Entity::getBBoxLeft() const { return bbox.left; }
float Entity::getBBoxRight() const { return bbox.left + bbox.width; }
float Entity::getBBoxTop() const { return bbox.top; }
float Entity::getBBoxBottom() const { return bbox.top + bbox.height; }
sf::Rect<float> Entity::getBBoxBounds() const { return bbox; }

void Entity::assignParentScene(Scene* scene)
{
	parentScene = scene;
}

Scene* Entity::getParentScene() const
{
	return parentScene;
}

void Entity::update(const float deltaTime)
{
	animation_progress += (animation_speed * deltaTime);
	if (animation_progress >= 1)
	{
		animation_progress--;
		animation_frame++;

		sf::IntRect textureRect(spr.getTextureRect());
		textureRect.top += textureRect.height;

		if (animation_frame >= animation_total_frames)
		{
			animation_frame = 0;
			textureRect.top -= (textureRect.height * animation_total_frames);
		}

		spr.setTextureRect(textureRect);
	}
}

void Entity::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	/*
	sf::RectangleShape rect(sf::Vector2f(bbox.width, bbox.height));
	rect.setPosition(sf::Vector2f(bbox.left, bbox.top));
	rect.setFillColor(sf::Color(30, 150, 240, 90));
	target.draw(rect, states);/**/

	target.draw(spr, states);
}

void Entity::loadTexturePage(const std::string & file_path)
{
	texture_page.loadFromFile(file_path);
}

sf::Texture* Entity::getTexturePage()
{
	return &texture_page;
}

Entity::~Entity()
{

}
