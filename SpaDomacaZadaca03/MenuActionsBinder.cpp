#include "MenuActionsBinder.h"

#include <thread>
#include "DijkstrasAlgorithm.h"
#include "DepthFirstSearch.h"
#include "GreedyBestFirstSearch.h"
#include "AStarSearch.h"

void MenuActionsBinder::bindActions() {
	menu->connectMenuItem("Run", "Run/Pause Search (SPACE)", [this]() {
		if (canvas.searchNotRunning()) {
			grid.clearPath();
			grid.resetTileCosts();
			gui.getWindow()->setTitle("Using " + algoHandler.getCurrentSearch()->getIdentifier() + " - RUNNING (Options disabled)");
			std::thread([this]() {
				algoHandler.getCurrentSearch()->run();
				gui.getWindow()->setTitle("Using " + algoHandler.getCurrentSearch()->getIdentifier());
				}).detach();
		} else {
			canvas.togglePauseRunningSearch();
		}
		});

	menu->connectMenuItem("Run", "Terminate Search (X)", [this]() {
		canvas.setStopRunningSearch(true);
		});

	menu->connectMenuItem("Options", "Use Dijkstra's Algorithm (1)", [this]() {
		if (canvas.searchNotRunning()) {
			algoHandler.setCurrentSearch(new DijkstrasAlgorithm(grid, canvas, soundPlayer));
			gui.getWindow()->setTitle("Using " + algoHandler.getCurrentSearch()->getIdentifier());
		}
		});

	menu->connectMenuItem("Options", "Use Depth-First Search (2)", [this]() {
		if (canvas.searchNotRunning()) {
			algoHandler.setCurrentSearch(new DepthFirstSearch(grid, canvas, soundPlayer));
			gui.getWindow()->setTitle("Using " + algoHandler.getCurrentSearch()->getIdentifier());
		}
		});

	menu->connectMenuItem("Options", "Use Greedy Best-First Search (3)", [this]() {
		if (canvas.searchNotRunning()) {
			algoHandler.setCurrentSearch(new GreedyBestFirstSearch(grid, canvas, soundPlayer));
			gui.getWindow()->setTitle("Using " + algoHandler.getCurrentSearch()->getIdentifier());
		}
		});
	
	menu->connectMenuItem("Options", "Use A* (A-Star) Search (4)", [this]() {
		if (canvas.searchNotRunning()) {
			algoHandler.setCurrentSearch(new AStarSearch(grid, canvas, soundPlayer));
			gui.getWindow()->setTitle("Using " + algoHandler.getCurrentSearch()->getIdentifier());
		}
		});

	menu->connectMenuItem("Options", "Generate maze - Kruskal's Algorithm (Q)", [this]() {
		if (canvas.searchNotRunning()) {
			grid.clearAll();
			grid.randomMaze(MazeAlgo::KRUSKAL);
		}
		});

	menu->connectMenuItem("Options", "Generate maze - Recursive Backtracking (E)", [this]() {
		if (canvas.searchNotRunning()) {
			grid.clearAll();
			grid.randomMaze(MazeAlgo::REC_BACK);
		}
		});

	menu->connectMenuItem("Options", "Clear Path (W)", [this]() {
		if (canvas.searchNotRunning()) {
			grid.clearPath();
		}
		});

	menu->connectMenuItem("Options", "Clear Solid Tiles (S)", [this]() {
		if (canvas.searchNotRunning()) {
			grid.clearSolid();
		}
		});

	menu->connectMenuItem("Options", "Clear All Tiles (C)", [this]() {
		if (canvas.searchNotRunning()) {
			grid.clearAll();
		}
		});

	menu->connectMenuItem("Options", "Reset Grid (R)", [this]() {
		if (canvas.searchNotRunning()) {
			grid.reset(gui.getWindow()->getSize().x, gui.getWindow()->getSize().y);
		}
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
