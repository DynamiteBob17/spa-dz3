#include "MenuActionsBinder.h"

void MenuActionsBinder::bindActions() {
	menu->connectMenuItem("Run", "Run/Pause Search (SPACE)", []() {
		std::cout << "Run/Pause Search action triggered" << std::endl;
		});

	menu->connectMenuItem("Run", "Terminate Search (X)", []() {
		std::cout << "Terminate Search action triggered" << std::endl;
		});

	menu->connectMenuItem("Options", "Use Dijkstra's Algorithm", []() {
		std::cout << "Use Dijkstra's Algorithm action triggered" << std::endl;
		});

	menu->connectMenuItem("Options", "Use Depth-First Search", []() {
		std::cout << "Use Depth-First Search action triggered" << std::endl;
		});

	menu->connectMenuItem("Options", "Use Greedy Best-First Search", []() {
		std::cout << "Use Greedy Best-First Search action triggered" << std::endl;
		});

	menu->connectMenuItem("Options", "Use A*", []() {
		std::cout << "Use A* action triggered" << std::endl;
		});

	menu->connectMenuItem("Options", "Generate maze - Kruskal's Algorithm", []() {
		std::cout << "Generate maze - Kruskal's Algorithm action triggered" << std::endl;
		});

	menu->connectMenuItem("Options", "Generate maze - Recursive Backtracking", []() {
		std::cout << "Generate maze - Recursive Backtracking action triggered" << std::endl;
		});

	menu->connectMenuItem("Options", "Clear Path (W)", []() {
		std::cout << "Clear Path action triggered" << std::endl;
		});

	menu->connectMenuItem("Options", "Clear Solid Tiles (S)", []() {
		std::cout << "Clear Solid Tiles action triggered" << std::endl;
		});

	menu->connectMenuItem("Options", "Clear All Tiles (C)", []() {
		std::cout << "Clear All Tiles action triggered" << std::endl;
		});

	menu->connectMenuItem("Options", "Reset Grid (R)", []() {
		std::cout << "Reset Grid action triggered" << std::endl;
		});

	menu->connectMenuItem("Info", "Mouse Usage", [this]() { showMouseUsageMessageBox(); });
	menu->connectMenuItem("Info", "Algorithms", [this]() { showAlgorithmsMessageBox(); });
}

void MenuActionsBinder::showMouseUsageMessageBox() {
	auto messageBox = tgui::MessageBox::create(
		"Mouse Usage",
		"Left-click to add a solid tile, right-click to remove it.\n\nDrag the start / goal tile to change its position.\n\nUse the scroll wheel to change the number of tiles.",
		{ "OK" }
	);
	messageBox->setSize({ "33%", "25%" });
	messageBox->setPosition({ "33%", "33%" });
	gui.add(messageBox);

	messageBox->getRenderer()->setTitleBarHeight(24);
	messageBox->getRenderer()->setBorders({ 2, 2, 2, 2 });
	messageBox->getRenderer()->setTitleBarColor(tgui::Color(160, 160, 160));
	messageBox->getRenderer()->setBackgroundColor(tgui::Color::White);
	messageBox->getRenderer()->setBorderColor(tgui::Color::Black);

	messageBox->onButtonPress([this, messageBox](const tgui::String& buttonText) {
		if (buttonText == "OK") {
			gui.remove(messageBox);
		}
		});
}

void MenuActionsBinder::showAlgorithmsMessageBox() {
	std::string description = R"(Colors:
    Red/green = start/goal tile
    White = non-solid tile
    Dark blue = solid tile
    Grayish blue = tile marked to be analyzed at some point in each algorithm
    Light blue = tile that has been analyzed

The tiles of the grid in this visualisation can be thought of
as nodes in a graph in which every non-solid tile is connected
to 4 or less neighboring tiles, depending on which of them are
also non-solid, and the cost/distance/weight of moving from one
to another is always 1. So, all edges/neighbors of connected
nodes/tiles have the same weight.

Dijkstra's Algorithm is weighted and does guarantee the shortest
path, but since all edges have the same weight in this particular
grid system of nodes, it works essentially the same as BFS.

Depth-First Search is unweighted and doesn't guarantee the shortest path.

Greedy Best-First Search is weighted, but doesn't guarantee
the shortest path.

A* Search is weighted and does guarantee the shortest path.
)";

	auto messageBox = tgui::MessageBox::create(
		"Algorithms",
		description,
		{ "OK" }
	);
	messageBox->setSize({ "42%", "62%" });
	messageBox->setPosition({ "30%", "20%" });
	gui.add(messageBox);

	messageBox->getRenderer()->setTitleBarHeight(24);
	messageBox->getRenderer()->setBorders({ 2, 2, 2, 2 });
	messageBox->getRenderer()->setTitleBarColor(tgui::Color(160, 160, 160));
	messageBox->getRenderer()->setBackgroundColor(tgui::Color::White);
	messageBox->getRenderer()->setBorderColor(tgui::Color::Black);

	messageBox->onButtonPress([this, messageBox](const tgui::String& buttonText) {
		if (buttonText == "OK") {
			gui.remove(messageBox);
		}
		});
}
