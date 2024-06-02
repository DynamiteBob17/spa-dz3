#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "MenuActionsBinder.h"
#include "AlgoHandler.h"
#include "MouseListener.h"
#include "KeyListener.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(Canvas::INITIAL_WIDTH, Canvas::INITIAL_HEIGHT), "TGUI window");

	tgui::Gui gui(window);

	auto menu = tgui::MenuBar::create();

	menu->addMenu("Run");
	menu->addMenuItem("Run", "Run/Pause Search (SPACE)");
	menu->addMenuItem("Run", "Terminate Search (X)");

	menu->addMenu("Options");
	menu->addMenuItem("Options", "Use Dijkstra's Algorithm (1)");
	menu->addMenuItem("Options", "Use Depth-First Search (2)");
	menu->addMenuItem("Options", "Use Greedy Best-First Search (3)");
	menu->addMenuItem("Options", "Use A* (A-Star) Search (4)");
	menu->addMenuItem("Options", "Generate maze - Kruskal's Algorithm (Q)");
	menu->addMenuItem("Options", "Generate maze - Recursive Backtracking (E)");
	menu->addMenuItem("Options", "Clear Path (W)");
	menu->addMenuItem("Options", "Clear Solid Tiles (S)");
	menu->addMenuItem("Options", "Clear All Tiles (C)");
	menu->addMenuItem("Options", "Reset Grid (R)");

	menu->addMenu("Info");
	menu->addMenuItem("Info", "Mouse Usage");
	menu->addMenuItem("Info", "Algorithms");
	

	gui.add(menu);

	Grid grid(8, menu->getSize().y);
	Canvas canvas(window, grid);
	SoundPlayer soundPlayer;
	AlgoHandler algoHandler(grid, canvas, soundPlayer);
	MouseListener mouseListener(grid, canvas, window);
	MenuActionsBinder(gui, menu, grid, canvas, algoHandler, soundPlayer, mouseListener).bindActions();
	KeyListener keyListener(gui, menu, grid, canvas, algoHandler, soundPlayer);

	window.setTitle("Using " + algoHandler.getCurrentSearch()->getIdentifier());

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			gui.handleEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized) {
				float w = window.getSize().x;
				float h = window.getSize().y;
				grid.setTileSizes(w, h);
				window.setView(sf::View(sf::FloatRect(0, 0, w, h)));
			}

			keyListener.handleEvent(event);
			mouseListener.handleEvent(event);
		}

		window.clear();
		canvas.draw();
		gui.draw();
		window.display();
	}

	return 0;
}