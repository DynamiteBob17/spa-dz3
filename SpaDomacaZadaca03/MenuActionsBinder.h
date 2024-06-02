#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "Grid.h"
#include "Canvas.h"
#include "AlgoHandler.h"
#include "MouseListener.h"

class MenuActionsBinder {
private:
	tgui::Gui& gui;
	tgui::MenuBar::Ptr menu;
	Grid& grid;
	Canvas& canvas;
	AlgoHandler& algoHandler;
	SoundPlayer& soundPlayer;
	MouseListener& mouseListener;

	void showMouseUsageMessageBox();
	void showAlgorithmsMessageBox();

public:
	MenuActionsBinder(
		tgui::Gui& gui,
		tgui::MenuBar::Ptr menu,
		Grid& grid,
		Canvas& canvas,
		AlgoHandler& algoHandler,
		SoundPlayer& soundPlayer,
		MouseListener& mouseListener
	) : gui(gui),
		menu(menu),
		grid(grid),
		canvas(canvas),
		algoHandler(algoHandler),
		soundPlayer(soundPlayer),
		mouseListener(mouseListener) {};
	void bindActions();
};
