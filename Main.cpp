// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include "Level.h"
#include "MainMenu.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace sf;

void windowProcess(sf::RenderWindow* window, Input* in)
{
	// Handle window events.
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
			break;
		case sf::Event::KeyPressed:
			// update input class
			in->setKeyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			//update input class
			in->setKeyUp(event.key.code);
			break;
		case sf::Event::MouseMoved:
			//update input class
			in->setMousePosition(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
				in->setLeftMouse(Input::MouseState::PRESSED);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setRightMouse(Input::MouseState::PRESSED);
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
				in->setLeftMouse(Input::MouseState::UP);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setRightMouse(Input::MouseState::UP);
			}
			break;
		default:
			// don't handle other events
			break;
		}
	}
}
int main()
{
	//Create the window for the menu
	sf::RenderWindow MENU(sf::VideoMode(1200, 600), "Main Menu");
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

	//Menu Music
	sf::Music menuMusic;
	menuMusic.openFromFile("sfx/MainMenuMusic.wav");
	menuMusic.setLoop(true);
	menuMusic.setVolume(50.f);
	menuMusic.play();

	//Set the background
	RectangleShape background;
	background.setSize(Vector2f(1200, 600));
	Texture MainTexture;
	MainTexture.loadFromFile("gfx/MenuBackground.png");
	background.setTexture(&MainTexture);

	// Photo that appears when you select Options
	RectangleShape OBackround;
	OBackround.setSize(Vector2f(1200, 600));
	Texture Option_texture;
	Option_texture.loadFromFile("gfx/MenuBackground.png");
	OBackround.setTexture(&Option_texture);

	// Photo that appears when you select Controls
	RectangleShape ABackround;
	ABackround.setSize(Vector2f(1200, 600));
	Texture About_texture;
	About_texture.loadFromFile("gfx/Controls.png");
	ABackround.setTexture(&About_texture);

	// Window Loop
	while (MENU.isOpen())
	{
		// Set the gamestate to MENU
		GameState gameState;
		gameState.setCurrentState(State::MENU);

		Event event;
		while (MENU.pollEvent(event))
		{
			if (event.type == Event::Closed) // If window close event
			{
				MENU.close(); // Close the MENU window
			}
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::W) // If the W key is released
				{
					mainMenu.MoveUp(); // Call the MainMenu class moveUp function
					break;
				}
				if (event.key.code == Keyboard::S) // If the S key is released
				{
					mainMenu.MoveDown(); // Call the MainMenu class moveDown function
					break;
				}
				if (event.key.code == Keyboard::Return) // If return key is pressed
				{

					// Setup every window
					sf::RenderWindow window(sf::VideoMode(1200, 600), "CMP105_Coursework_Handles Outbreak");
					sf::RenderWindow OPTIONS(sf::VideoMode(1200, 600), "OPTIONS");
					sf::RenderWindow ABOUT(sf::VideoMode(1200, 600), "CONTROLS");
					
					// Initialise input and level objects.
					AudioManager audioManager;
					Input input;
					GameState gameState;
					Level level(&window, &input, &gameState, &audioManager);

					gameState.setCurrentState(State::LEVEL); // Set the current gamestate to LEVEL

					
					menuMusic.stop(); // Stop the Menu Music

					// Initialise objects for delta time
					sf::Clock clock;
					float deltaTime;

					int x = mainMenu.MainMenuPressed();
					if (x == 0) // If the option mainMenu selected was the first ( play game )
					{
						while (window.isOpen()) // While the game window is open
						{
							menuMusic.stop(); // Stop the menuMusic from playing

							//Process window events
							windowProcess(&window, &input);

							// Calculate delta time. How much time has passed 
							// since it was last calculated (in seconds) and restart the clock.
							deltaTime = clock.restart().asSeconds();
							// Call standard game loop functions (input, update and render)
							level.handleInput(deltaTime);
							level.update(deltaTime);
							level.render();
							// Update input class, handle pressed keys
							// Must be done last.
							input.update();

							// Make sure the other windows are closed
							OPTIONS.close(); 
							ABOUT.close();
						}
					}

					menuMusic.play(); // Since only the MENU window can be open here, play the Menu music again

					if (x == 1) // If the option mainMenu selected was the second ( controls )
					{
						while (ABOUT.isOpen()) // While the window is open
						{
							menuMusic.stop(); // stop playing the menu music again

							Event aevent;
							while (ABOUT.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed) // If the window should be closed
								{
									ABOUT.close(); // Close the window
								}
								if (aevent.type == Event::KeyPressed) 
								{
									if (aevent.key.code == Keyboard::Escape) // If escape is pressed
									{
										ABOUT.close(); // Close the window
									}
								}
							}

							// Ensure any other windows are closed,draw the background image for the about(controls) window and then display the window
							window.close();
							OPTIONS.close();
							ABOUT.clear();
							ABOUT.draw(ABackround);
							ABOUT.display();
						}

						menuMusic.play(); // Since only the MENU window can be open here, play the Menu music again

					}
					if (x == 2) // If the option mainMenu selected was the third ( exit )
					{
						MENU.close(); // Close the MENU window
						break;
					}
				
				}
			}
		}

		//Display the menu window and load its background image
		MENU.clear();
		MENU.draw(background);
		mainMenu.draw(MENU);
		MENU.display();
	}
}
