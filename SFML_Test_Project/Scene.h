#pragma once
class Scene
{
private:
	// Entity list, storing references to all the game objects. It needs to store references, when it was storing Entities, polymorphism was lost
	std::vector<Entity *> entities;
	static std::vector<sf::Texture*> textures;
public:
	Scene();

	static void addTexture(const std::string& finePath);
	static sf::Texture* getTexture(const int id);
	static void destroyTextures();

	void addEntity(Entity* entity);
	int entityCount() const;

	void update(const float deltaTime);
	void checkCollision();
	void draw(sf::RenderTarget& renderTarget, const sf::RenderStates& renderStates = sf::RenderStates::Default) const;

	~Scene();
};

