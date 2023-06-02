#pragma once
#include "Framework/GameObject.h"

class PauseMenu : public GameObject
{
public:
	PauseMenu(); 
	~PauseMenu();

protected:
	sf::Texture PauseMenuTexture; // Texture for the pause menu object
};
