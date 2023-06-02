#pragma once
#include "Bullet.h"
#include "Framework/GameObject.h"
#include <math.h>
#include <Vector>
#include "Framework/Animation.h"
#include <SFML/Audio.hpp>
#include "Framework/AudioManager.h"

class LeftBulletManager
{
public:
	LeftBulletManager();
	~LeftBulletManager();

	void spawn(sf::Vector2f playerPos); // Function to spawn a bullet at the player's position
	void update(float dt); // Update function to update the bullets
	void deathCheck(); // Function to check if bullets have gone off-screen
	void render(sf::RenderWindow* window); // Function to render the bullets

	std::vector<Bullet>* get_left_bullets() { return &bullets; } // Function to get a pointer to the vector of bullets

private:

	std::vector <Bullet> bullets; // Vector to store the bullets
	sf::Vector2f spawnPoint;  // Spawn point for the bullets
	sf::Texture bulletTexture; // Texture for the bullets
	Animation shot; // Animation for the bullets
	Animation* currentAnimation; 

	sf::SoundBuffer shootingBuffer; // Sound buffer for shooting sound
	sf::Sound shootingSound; // Sound for shooting

	void addFrames(Animation* anim, float speed, int xSize, int ySize, int spriteAmount, int columnStart, int rowStart) // CREDIT TO JACK WOOD FOR ANIM CODE HERE
	{
		for (int i = 1; i <= spriteAmount; i++) {
			anim->addFrame(sf::IntRect(
				(rowStart + i - 2) * xSize,
				(columnStart - 1) * ySize,
				xSize,
				ySize
			));
		}
		anim->setFrameSpeed(speed);
	}
};
