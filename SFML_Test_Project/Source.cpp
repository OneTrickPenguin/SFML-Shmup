#include "Pch.h"
#include "Pilot.h"
#include "Ship.h"
#include <string>
#include <iostream>
#include <fstream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Window lol", sf::Style::Fullscreen);
	sf::RenderTexture game_render;
	game_render.create(1920, 1080);
	sf::Sprite game_sprite(game_render.getTexture());
	game_sprite.setScale(1, 1);
	// Entity list, storing references to all the game objects. It needs to store references, when it was storing Entities, polymorphism was lost
	std::vector<Entity *> entities;
	sf::Clock deltaTimeClock;

	{
		std::ifstream fin;
		fin.open("../AssetConfig.txt");

		if (!fin.fail())
		{
			std::string directory = "../";
			bool loaded_texture_page = false;

			while (!fin.eof())
			{
				char op; // operator character
				fin >> op;
				switch (op)
				{
				case '@': // enter folder operator
				{
					std::string folder;
					fin >> folder;
					directory += folder + "/";
					std::cout << "Current load path: " << directory << "\n";
					break;
				}

				case '+': // add asset operator
				{
					char type; // what type of asset to add to the project
					std::string filename;
					fin >> type;
					fin >> filename;
					switch (type)
					{
					case 'i': // image type
						Scene::addTexture(directory + filename);
						break;

					case 'f': // font type

						break;

					case 'p': // texture page
						if (!loaded_texture_page)
						{
							Entity::loadTexturePage(directory + filename);
							loaded_texture_page = true;
						}
						break;
					}
					std::cout << "Loading asset: " << directory << filename << "\n";
					break;
				}

				case '^': // up/exit folder operator
					directory.pop_back();
					while (directory.back() != '/')
					{
						directory.pop_back();
					}
					std::cout << "Current load path: " << directory << "\n";
					break;
				}
			}
		}
		else
		{
			std::cout << "Failed to find assets\n\n";
		}
	}

	sf::Font arialFont;
	arialFont.loadFromFile("../Assets/Fonts/arial.ttf");
	sf::Text debugText("", arialFont);

	// This should also be changed at some point, to load entities from a scene file. later :)
	Scene gameScene;
	gameScene.addEntity(new Enemy(300.0f, 300.0f));
	//gameScene.addEntity(new Ship(600.0f, 300.0f));
	gameScene.addEntity(new Enemy(900.0f, 300.0f));
	//gameScene.addEntity(new Pilot(1200, 300.0f));
	gameScene.addEntity(new Player(600.0f, 600.0f));

	std::cout << "Running game\n\n";

	// Game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
		}

		// deltaTime is used to adjust movement based on how long the frame takes to process
		// This ensures things move at a constant speed, independent from framerate
		float deltaTime = deltaTimeClock.getElapsedTime().asSeconds();
		deltaTimeClock.restart();

		// update() loop - update all entities
		gameScene.update(deltaTime);

		// Collided() loop - check collisions between all entities
		gameScene.checkCollision();

		// Clear window first, otherwise the last frame won't be removed from the window
		game_render.clear();
		window.clear();

		// draw() loop - draw all entities
		// It's safe to assume we won't be creating or destroying anything in draw(), so we can store the size to avoid calculating it every iteration
		//gameScene.draw(window);
		gameScene.draw(game_render);
		game_render.display();
		window.draw(game_sprite);
		debugText.setString("Approx FPS: " + std::to_string(1/deltaTime) + "\nEntity count: " + std::to_string(gameScene.entityCount()));
		window.draw(debugText);
		// Actually display what's been drawn
		window.display();
	}

	window.close();

	Scene::destroyTextures();

	return 0;
}