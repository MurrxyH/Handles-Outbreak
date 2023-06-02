#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Zombie.h"
#include "Framework/Collision.h"


class Player : public GameObject
{
public:
	Player(sf::RenderWindow* hwnd, Input* in);
	~Player();
	void update(float dt) override;
	void handleInput(float dt);
	void render();

protected:
	
	Animation moveFwd;
	Animation moveDown;
	Animation moveUp;

	Animation* currentAnimation;
	sf::Texture playerTexture;
};






