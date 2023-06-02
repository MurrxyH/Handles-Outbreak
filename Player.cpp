#include "Player.h"
#include <iostream>

Player::Player(sf::RenderWindow* hwnd, Input* in)
{
	setWindow(hwnd);
	setInput(in);

	playerTexture.loadFromFile("gfx/playerSheetFULL.png");
	setSize(sf::Vector2f(50, 50));
	setPosition(500, 200);
	setTexture(&playerTexture);
	setCollisionBox(sf::FloatRect(0, 0, 25, 25));

	velocity = sf::Vector2f(350.0f, 350.0f);

	
	// RIGHT AND LEFT
	moveFwd.addFrame(sf::IntRect(11, 72, 54, 64)); //
	moveFwd.addFrame(sf::IntRect(75, 72, 54, 64)); //
	moveFwd.addFrame(sf::IntRect(139, 72, 54, 64)); //
	moveFwd.addFrame(sf::IntRect(203, 72, 54, 64)); //
	moveFwd.addFrame(sf::IntRect(267, 72, 54, 64)); //
	moveFwd.addFrame(sf::IntRect(331, 72, 54, 64)); //
	moveFwd.addFrame(sf::IntRect(395, 72, 54, 64)); //
	moveFwd.addFrame(sf::IntRect(459, 72, 54, 64)); //
	moveFwd.addFrame(sf::IntRect(523, 72, 54, 64)); //
	moveFwd.setFrameSpeed(1.f / 10.f);
	// DOWN
	moveDown.addFrame(sf::IntRect(19, 329, 54, 64)); //
	moveDown.addFrame(sf::IntRect(83, 329, 54, 64)); //
	moveDown.addFrame(sf::IntRect(147, 329, 54, 64)); //
	moveDown.addFrame(sf::IntRect(211, 329, 54, 64)); //
	moveDown.addFrame(sf::IntRect(275, 329, 54, 64)); //
	moveDown.addFrame(sf::IntRect(339, 329, 54, 64)); //
	moveDown.addFrame(sf::IntRect(403, 329, 54, 64)); //
	moveDown.addFrame(sf::IntRect(467, 329, 54, 64)); //
	moveDown.addFrame(sf::IntRect(531, 329, 54, 64)); //
	moveDown.setFrameSpeed(1.f / 10.f);
	// UP
	moveUp.addFrame(sf::IntRect(21, 393, 54, 64)); //
	moveUp.addFrame(sf::IntRect(85, 393, 54, 64)); //
	moveUp.addFrame(sf::IntRect(149, 393, 54, 64)); //
	moveUp.addFrame(sf::IntRect(213, 393, 54, 64)); //
	moveUp.addFrame(sf::IntRect(277, 393, 54, 64)); //
	moveUp.addFrame(sf::IntRect(341, 393, 54, 64)); //
	moveUp.addFrame(sf::IntRect(405, 393, 54, 64)); //
	moveUp.addFrame(sf::IntRect(469, 393, 54, 64)); //
	moveUp.addFrame(sf::IntRect(533, 393, 54, 64)); //
	moveUp.setFrameSpeed(1.f / 10.f);

	currentAnimation = &moveFwd;
}


Player::~Player()
{
}


void Player::update(float dt)
{
	// Update animations
	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());

	// PREVENT PLAYER FROM GOING OUT OF BOUNDS : BOTTOM OF SCREEN
	if ((getPosition().y) > window->getSize().y - getSize().y)
	{
		setPosition(getPosition().x, window->getSize().y - getSize().y);
	}

	//// PREVENT PLAYER FROM GOING OUT OF BOUNDS : TOP OF SCREEN
	if ((getPosition().y) < 0)
	{
		setPosition(getPosition().x, 0);
	}

	//// PREVENT PLAYER FROM GOING OUT OF BOUNDS : LEFT OF SCREEN
	if ((getPosition().x) < 0)
	{
		setPosition(0, getPosition().y);
	}

	//// PREVENT PLAYER FROM GOING OUT OF BOUNDS : RIGHT OF SCREEN
	if ((getPosition().x) > window->getSize().x - getSize().x)
	{
		setPosition(window->getSize().x - getSize().x, getPosition().y);
	}

}


void Player::handleInput(float dt)
{
	// Move up
	if (input->isKeyDown(sf::Keyboard::W))
	{
		currentAnimation = &moveUp;  // Set the current animation to moveUp
		moveUp.setPlaying(true);  // Start playing the moveUp animation
		move(0 * dt, -velocity.y * dt);  // Move the player upward based on velocity
	}
	else
	{
		moveUp.setPlaying(false);  // Stop playing the moveUp animation
	}

	// Move down
	if (input->isKeyDown(sf::Keyboard::S))
	{
		currentAnimation = &moveDown;  // Set the current animation to moveDown
		moveDown.setPlaying(true);  // Start playing the moveDown animation
		move(0 * dt, velocity.y * dt);  // Move the player downward based on velocity
	}
	else
	{
		moveDown.setPlaying(false);  // Stop playing the moveDown animation
	}

	// Move left
	if (input->isKeyDown(sf::Keyboard::A))
	{
		currentAnimation = &moveFwd;  // Set the current animation to moveFwd
		moveFwd.setPlaying(true);  // Start playing the moveFwd animation
		move(-velocity.x * dt, 0 * dt);  // Move the player to the left based on velocity

		// Check if the animation is not flipped, then flip it
		if (!moveFwd.getFlipped())
		{
			moveFwd.setFlipped(true);
		}
	}
	else
	{
		moveFwd.setPlaying(false);  // Stop playing the moveFwd animation
	}

	// Move right
	if (input->isKeyDown(sf::Keyboard::D))
	{
		currentAnimation = &moveFwd;  // Set the current animation to moveFwd
		moveFwd.setPlaying(true);  // Start playing the moveFwd animation
		move(velocity.x * dt, 0 * dt);  // Move the player to the right based on velocity

		if (moveFwd.getFlipped())
		{
			moveFwd.setFlipped(false);  // If the animation is flipped, unflip it
		}
	}
}



void Player::render()
{
}