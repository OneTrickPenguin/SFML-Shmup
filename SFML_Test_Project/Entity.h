#pragma once
class Scene;

class Entity
{
private:
	sf::Vector2f pos;
	sf::Rect<float> bbox;
	bool alive = true;
	Scene* parentScene;
protected:
	sf::Sprite spr;
	sf::Vector2f bbox_origin;

	void setBBoxSize(const float width, const float height);
	void updateSprite();
	void updateBBox();
public:
	static enum Layers
	{
		wall,
		player,
		enemy,
		bullet
	};

	bool isAlive() const;
	void die();
	bool canCollide = true;
	bool isVisible = true;

	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void movePosition(sf::Vector2f delta);
	void movePosition(float dx, float dy);

	float getBBoxLeft() const;
	float getBBoxRight() const;
	float getBBoxTop() const;
	float getBBoxBottom() const;
	sf::Rect<float> getBBoxBounds() const;

	Entity(const float x, const float y, const sf::Texture* texture);

	void assignParentScene(Scene* scene);
	Scene* getParentScene() const;

	virtual void update(const float deltaTime) = 0;
	virtual void draw(sf::RenderTarget& renderTarget, const sf::RenderStates& renderStates = sf::RenderStates::Default) const;
	virtual void collided(Entity& other) = 0;
	virtual int layersSelf() const = 0;
	virtual int layersOther() const = 0;

	~Entity();
};

