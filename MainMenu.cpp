#include "MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("font/arial.ttf"))
	{
		cout << "There was no font here" << endl;
	}


	// Initialize the "START GAME" button
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::Yellow);
	mainMenu[0].setString("START GAME");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(725, 200);

	// Initialize the "CONTROLS" button
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::Yellow);
	mainMenu[1].setString("CONTROLS");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(800, 300);

	// Initialize the "EXIT" button
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::Yellow);
	mainMenu[2].setString("EXIT");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(1015, 500);

	MainMenuSelected = 0; // Set the default selected option to 0 (nothing)
}
MainMenu::~MainMenu()
{
}

// Draw MainMenu
void MainMenu::draw(RenderWindow& window)
{
	for (int i = 0; i < Max_main_menu; ++i)
	{
		window.draw(mainMenu[i]);
	}
}

//MoveUp
void MainMenu::MoveUp()
{
	// Calculate what is selected and change colour accordingly
	if (MainMenuSelected - 1 >= 0)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::Yellow); // Set the text colour to yellow if it isnt selected
		MainMenuSelected--;

		if (MainMenuSelected == -1)
		{
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::Blue); // Set the text colour to blue if it is selected
	}
}

//MoveDown
void MainMenu::MoveDown()
{
	// Calculate what is selected and change colour accordingly
	if (MainMenuSelected + 1 <= Max_main_menu)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::Yellow); // Set the text colour to yellow if it isnt selected
		MainMenuSelected++;
		if (MainMenuSelected == 4)
		{
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::Blue); // Set the text colour to blue if it is selected
	}
}