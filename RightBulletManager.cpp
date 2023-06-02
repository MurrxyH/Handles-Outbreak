#include "RightBulletManager.h"

RightBulletManager::RightBulletManager()
{
	spawnPoint = sf::Vector2f(350, 250); // Set the spawn point for the bullets
	bulletTexture.loadFromFile("gfx/bulletSheet.png"); // Load the bullet texture

	for (int i = 0; i < 10; i++)
	{
		bullets.push_back(Bullet()); // Add bullets to the vector
		bullets[i].setAlive(false); // Set the bullets as not alive
		bullets[i].setTexture(&bulletTexture); // Set the texture for the bullets to the loaded bulletTexture
		bullets[i].setSize(sf::Vector2f(25, 25)); // Set the size of the bullets
		bullets[i].setCollisionBox(sf::FloatRect(0, 0, 25, 25)); // Set the collision box for the bullets
	}

	addFrames(&shot, 1.0f / 10.f, 32, 32, 9, 1, 1); // Use the addFrames function to add all the needed frames and set the speed
	currentAnimation = &shot; // Set the current animation to the shot animation
}

RightBulletManager::~RightBulletManager()
{
}

void RightBulletManager::update(float dt, sf::Vector2f bulletSize) // call update on all ALIVE bullets
{
	// call update on all ALIVE balls
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			// set collision box

			// Animations
			bullets[i].setTextureRect(currentAnimation->getCurrentFrame());
			bullets[i].update(dt); // Update the bullets using the Bullet class update function
		}
	}
	// Animations again
	if (shot.getFlipped())
	{
		shot.setFlipped(false); // Dont flip the animation because the bullet is being fired right
	}
	currentAnimation->animate(dt);
	deathCheck(); // Check for bullets going off-screen
}


// Spawn new bullet
// Find a dead bullet, make alive, move to spawn point, set Velocity
void RightBulletManager::spawn(sf::Vector2f playerPos)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (!bullets[i].isAlive())
		{
			bullets[i].setAlive(true);
			bullets[i].setVelocity(600, 0);
			bullets[i].setPosition(playerPos);

			return;
		}
	}
}


// Check all ALIVE bullets to see if outscreen/range, if so make dead
void RightBulletManager::deathCheck()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			if (bullets[i].getPosition().x < 0)
			{
				(bullets[i].setAlive(false));
			}
			if (bullets[i].getPosition().x > 1200)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y < 0)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y > 600)
			{
				bullets[i].setAlive(false);
			}
		}
	}
}


// Render all alive bullets
void RightBulletManager::render(sf::RenderWindow* window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			window->draw(bullets[i]);
		}
	}
}
