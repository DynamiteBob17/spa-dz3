#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "Grid.h"
#include "Canvas.h"
#include "AlgoHandler.h"

class KeyListener {
private:
	tgui::Gui& gui;
	tgui::MenuBar::Ptr menu;
	Grid& grid;
	Canvas& canvas;
	AlgoHandler& algoHandler;
	SoundPlayer& soundPlayer;

public:
	KeyListener(
		tgui::Gui& gui,
		tgui::MenuBar::Ptr menu,
		Grid& grid,
		Canvas& canvas,
		AlgoHandler& algoHandler,
		SoundPlayer& soundPlayer
	) : gui(gui),
		menu(menu),
		grid(grid),
		canvas(canvas),
		algoHandler(algoHandler),
		soundPlayer(soundPlayer) {};
	void handleEvent(sf::Event event);
};
