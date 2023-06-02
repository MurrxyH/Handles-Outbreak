#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "SFML\Audio.hpp"
#include "SFML/Audio.hpp"


using namespace std;
using namespace sf;
#define Max_main_menu 4

class MainMenu
{
public:

	MainMenu(float width, float height);
	~MainMenu();

	void draw(RenderWindow& window); // Draw the main menu on the given window
	void MoveUp(); // Move the selection up in the main menu
	void MoveDown(); // Move the selection down in the main menu

	int MainMenuPressed() // Return the index of the selected main menu item
	{
		return MainMenuSelected;
	}

private:
	int MainMenuSelected; // The index of the currently selected main menu item
	Font font; // The font used for the main menu items
	Text mainMenu[Max_main_menu]; // An array of Text objects representing the main menu items
};