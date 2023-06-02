#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
	PauseMenuTexture.loadFromFile("gfx/PauseMenuBackground.png"); // Load the texture from file
	setSize(sf::Vector2f(1200, 600)); // Set the size
	setPosition(0, 0); // Set the position
	setTexture(&PauseMenuTexture); // Set the texture
}

PauseMenu::~PauseMenu()
{

}
