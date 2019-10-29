#pragma once
class Scene;

class Entity
{
private:
	sf::Vector2f pos;
	sf::Rect<float> bbox;
	bool alive = true;
	Scene* parentScene;
	static sf::Texture texture_page;
protected:
	const sf::Vector2f screen_bounds = sf::Vector2f(960.0f, 540.0f);

	sf::Sprite spr = sf::Sprite(texture_page);
	sf::Vector2f bbox_origin;

	const float animation_speed = 0;
	float animation_progress = 0;
	const int animation_total_frames = 1;
	int animation_frame = 0;
	const bool animation_repeats = true;

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

	Entity(const float x, const float y);
	Entity(const float x, const float y, const int anim_speed, const int anim_frames, const bool anim_repeat = true);

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

	void assignParentScene(Scene* scene);
	Scene* getParentScene() const;

	virtual void update(const float deltaTime);
	virtual void draw(sf::RenderTarget& renderTarget, const sf::RenderStates& renderStates = sf::RenderStates::Default) const;
	virtual void collided(Entity& other) = 0;
	virtual int layersSelf() const = 0;
	virtual int layersOther() const = 0;

	static void loadTexturePage(const std::string& file_path);
	static sf::Texture* getTexturePage();

	~Entity();
};

