#pragma once
#include "Entity.h"
#include "Ship.h"
#include "Pilot.h"
class Player : public Entity
{
private:
	const static int layers = 0;
	const static int collides = 0;

	const sf::Keyboard::Key key_attack_l = sf::Keyboard::Q;
	const sf::Keyboard::Key key_attack_h = sf::Keyboard::W;
	const sf::Keyboard::Key key_dash = sf::Keyboard::E;
	const sf::Keyboard::Key key_change = sf::Keyboard::Space;

	Ship* ship;
	Pilot* pilot;

	const float call_cooldown = 3.0f;
	float call_timer = 0.0f;
	bool change_pressed = false;
	char state = 's'; // s: in ship,
					  // p: pilot (out of ship)
					  // a: in animation (entering ship)
	sf::Vector2f input_axes;
	char input_buttons = false;
	char prev_buttons = false;
public:
	Player(const float x, const float y, Scene* scene = nullptr);
	
	char getState();
	sf::Vector2f getInputAxes();
	char getInputButtons();			// bit 0: light (kick) attack (might not be implemented, but I don't need to worry about running out of bits)
	char getInputButtonsPressed();	// bit 1: heavy (sword) attack
	char getInputButtonsReleased();	// bit 2-3: unused
									// bit 4: dash
									// bit 5-6: unused
									// bit 7: switch between pilot and ship

	void update(const float deltaTime);
	void collided(Entity& other);

	int layersSelf() const;
	int layersOther() const;

	~Player();
};

