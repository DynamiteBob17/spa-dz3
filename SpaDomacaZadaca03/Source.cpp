#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "MenuActionsBinder.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "TGUI window");
	window.setFramerateLimit(60);

	tgui::Gui gui(window);

	auto menu = tgui::MenuBar::create();

	menu->addMenu("Run");
	menu->addMenuItem("Run", "Run/Pause Search (SPACE)");
	menu->addMenuItem("Run", "Terminate Search (X)");

	menu->addMenu("Options");
	menu->addMenuItem("Options", "Use Dijkstra's Algorithm");
	menu->addMenuItem("Options", "Use Depth-First Search");
	menu->addMenuItem("Options", "Use Greedy Best-First Search");
	menu->addMenuItem("Options", "Use A*");
	menu->addMenuItem("Options", "Generate maze - Kruskal's Algorithm");
	menu->addMenuItem("Options", "Generate maze - Recursive Backtracking");
	menu->addMenuItem("Options", "Clear Path (W)");
	menu->addMenuItem("Options", "Clear Solid Tiles (S)");
	menu->addMenuItem("Options", "Clear All Tiles (C)");
	menu->addMenuItem("Options", "Reset Grid (R)");

	menu->addMenu("Info");
	menu->addMenuItem("Info", "Mouse Usage");
	menu->addMenuItem("Info", "Algorithms");

	gui.add(menu);

	MenuActionsBinder(gui, menu).bindActions();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			gui.handleEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		gui.draw();
		window.display();
	}

	return 0;
}