#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MenuActionsBinder {
private:
	tgui::Gui& gui;
	tgui::MenuBar::Ptr menu;

	void showMouseUsageMessageBox();
	void showAlgorithmsMessageBox();

public:
	MenuActionsBinder(tgui::Gui& gui, tgui::MenuBar::Ptr menu) : gui(gui), menu(menu) {};
	void bindActions();
};
