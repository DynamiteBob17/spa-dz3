#include "KeyListener.h"

#include <thread>
#include "DijkstrasAlgorithm.h"
#include "DepthFirstSearch.h"
#include "GreedyBestFirstSearch.h"
#include "AStarSearch.h"

void KeyListener::handleEvent(sf::Event event) {
	if (event.type != sf::Event::KeyReleased) return;

	switch (event.key.code) {
	case sf::Keyboard::Key::Space:
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
		break;
	case sf::Keyboard::Key::X:
		canvas.setStopRunningSearch(true);
		break;
	case sf::Keyboard::Key::Num1:
		if (canvas.searchNotRunning()) {
			algoHandler.setCurrentSearch(new DijkstrasAlgorithm(grid, canvas, soundPlayer));
			gui.getWindow()->setTitle("Using " + algoHandler.getCurrentSearch()->getIdentifier());
		}
		break;
	case sf::Keyboard::Key::Num2:
		if (canvas.searchNotRunning()) {
			algoHandler.setCurrentSearch(new DepthFirstSearch(grid, canvas, soundPlayer));
			gui.getWindow()->setTitle("Using " + algoHandler.getCurrentSearch()->getIdentifier());
		}
		break;
	case sf::Keyboard::Key::Num3:
		if (canvas.searchNotRunning()) {
			algoHandler.setCurrentSearch(new GreedyBestFirstSearch(grid, canvas, soundPlayer));
			gui.getWindow()->setTitle("Using " + algoHandler.getCurrentSearch()->getIdentifier());
		}
		break;
	case sf::Keyboard::Key::Num4:
		if (canvas.searchNotRunning()) {
			algoHandler.setCurrentSearch(new AStarSearch(grid, canvas, soundPlayer));
			gui.getWindow()->setTitle("Using " + algoHandler.getCurrentSearch()->getIdentifier());
		}
		break;
	case sf::Keyboard::Key::Q:
		if (canvas.searchNotRunning()) {
			grid.clearAll();
			grid.randomMaze(MazeAlgo::KRUSKAL);
		}
		break;
	case sf::Keyboard::Key::E:
		if (canvas.searchNotRunning()) {
			grid.clearAll();
			grid.randomMaze(MazeAlgo::REC_BACK);
		}
		break;
	case sf::Keyboard::Key::W:
		if (canvas.searchNotRunning()) {
			grid.clearPath();
		}
		break;
	case sf::Keyboard::Key::S:
		if (canvas.searchNotRunning()) {
			grid.clearSolid();
		}
		break;
	case sf::Keyboard::Key::C:
		if (canvas.searchNotRunning()) {
			grid.clearAll();
		}
		break;
	case sf::Keyboard::Key::R:
		if (canvas.searchNotRunning()) {
			grid.reset(gui.getWindow()->getSize().x, gui.getWindow()->getSize().y);
		}
		break;
	default:
		break;
	}
}
