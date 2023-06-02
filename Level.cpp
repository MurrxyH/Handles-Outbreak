#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) : playerObject(hwnd, in), zombManagerObject(hwnd)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	// initialise game objects
	playerObject.setInput(in);
	zombieObject.setInput(in);

	// initialise audio stuff
	audioManager.addMusic("sfx/MainMenuMusic.wav", "MainMenuMusic");
	audioManager.addMusic("sfx/GameMusic.wav", "GameMusic");

	audioManager.addSound("sfx/PlayerShooting.wav", "PlayerShooting");
	audioManager.addSound("sfx/Glass_Break.ogg", "PlayerDeath");

}

Level::~Level()
{
}


// Update game objects
void Level::update(float dt)
{
	// Check for game being paused
	bool isGamePaused = gameState->getCurrentState() == State::PAUSE;

	if (isGamePaused)
	{
		pauseMenu.update(dt); // Update the pause menu using its update function
	}
	else
	{

		// Update game objects
		playerObject.update(dt);
		zombieObject.update(dt, playerObject.getPosition(), zombieObject.getPosition());

		timer.update(dt);

		// Update bullet managers
		rightManagerObject.update(dt, bulletObject.getSize());
		leftManagerObject.update(dt);

		// Call Spawn and Update zombie manager funcitons
		zombManagerObject.spawn(window);
		zombManagerObject.update(dt, playerObject.getPosition(), zombieObject.getPosition(), zombieObject.getSize(), &rightManagerObject, &leftManagerObject, &playerObject);

	}
}

// handle user input1
void Level::handleInput(float dt)
{
	// Check for game being paused
	bool isGamePaused = gameState->getCurrentState() == State::PAUSE;

	if (input->isPressed(sf::Keyboard::Escape)) // If escape is pressed
	{
		if (gameState->getCurrentState() == State::PAUSE) // If the game is already paused
		{
			gameState->setCurrentState(State::LEVEL); // Set the game state back to level
		}
		else // Else if the game was not paused
		{
			gameState->setCurrentState(State::PAUSE); // Pause the game

		}
	}
	if (!isGamePaused) // If the game is not currently paused
	{
		// Handle input for the player
		playerObject.handleInput(dt);

		// Handle Input for shooting to the left
		if (input->isLeftMousePressed()) // If left-click
		{
			leftManagerObject.spawn(playerObject.getPosition()); //Spawn a bullet at the players position, going left

			audioManager.playSoundbyName("PlayerShooting"); // Play the sound of a bullet being fired
		}

		//Handle Input for shooting to the right

		if (input->isRightMousePressed()) // If right-click
		{
			rightManagerObject.spawn(playerObject.getPosition()); //Spawn a bullet at the players position, going right

			audioManager.playSoundbyName("PlayerShooting"); // Play the sound of a bullet being fired
		}
	}

}

// Render level
void Level::render()
{
	// Check for game being paused
	bool isGamePaused = gameState->getCurrentState() == State::PAUSE;

	if (isGamePaused) // If the game is currently paused
	{
		// Draw the paused image only, to the window
		beginDraw();
		window->draw(pauseMenu); 
		endDraw();
	}
	else // If the game is not paused
	{
		// Draw everything else
		beginDraw();

		window->draw(backgroundObject);
		window->draw(playerObject);
		window->draw(zombieObject);
		timer.render(*window);
		leftManagerObject.render(window);
		rightManagerObject.render(window);
		zombManagerObject.render(window);

		endDraw();
	}

}
