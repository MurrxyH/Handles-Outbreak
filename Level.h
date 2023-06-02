#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include <string.h>
#include <iostream>
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"
#include "RightBulletManager.h"
#include "LeftBulletManager.h"
#include "ZombieManager.h"
#include "Background.h"
#include "Timer.h"
#include "PauseMenu.h"
#include "Framework/AudioManager.h"


class Level : public BaseLevel {
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Level();

	void handleInput(float dt) override; // Level handleInput function
	void update(float dt) override; // Level update function
	void render() override; // Level render

private:
	// Game objects
	Player playerObject;
	Zombie zombieObject;
	Bullet bulletObject;
	Background backgroundObject;
	Timer timer;
	PauseMenu pauseMenu;
	PauseMenu pauseMenuObject;

	// Managers
	LeftBulletManager leftManagerObject;
	RightBulletManager rightManagerObject;
	ZombieManager zombManagerObject;
	AudioManager audioManager;

	sf::Font font; // Font for text rendering

};