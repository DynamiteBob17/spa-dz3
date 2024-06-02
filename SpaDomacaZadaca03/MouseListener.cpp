#include "MouseListener.h"

static float map(float val, float valLow, float valHigh, float returnValLow, float returnValHigh) {
    float ratio = (val - valLow) / (valHigh - valLow);
	return ratio * (returnValHigh - returnValLow) + returnValLow;
}

int MouseListener::mapMouseXToColumn(const sf::Event::MouseMoveEvent& event) {
	return (int)map(event.x, 0, window.getSize().x, 0, grid.getColumns());
}

int MouseListener::mapMouseYToRow(const sf::Event::MouseMoveEvent& event) {
    if (event.y <= grid.getYOffset()) return -1;
	return (int)map(event.y, grid.getYOffset(), window.getSize().y, 0, grid.getRows());
}

Tile* MouseListener::getTileFromMouse(const sf::Event::MouseMoveEvent& event, bool isStartOrGoal) {
    int x = mapMouseXToColumn(event);
    int y = mapMouseYToRow(event);

    if (isStartOrGoal) {
        if (x >= grid.getColumns())
            x = grid.getColumns() - 1;
        else if (x < 0)
            x = 0;
        if (y >= grid.getRows())
            y = grid.getRows() - 1;
        else if (y < 0)
            y = 0;
    } else {
        if (x >= grid.getColumns())
            x = -1;
        else if (x < 0)
            x = -1;
        if (y >= grid.getRows())
            y = -1;
        else if (y < 0)
            y = -1;
    }

    return (x < 0 || y < 0) ? nullptr : grid.getTile(x, y);
}

int MouseListener::mapMouseXToColumn(const sf::Event::MouseButtonEvent& event) {
    return (int)map(event.x, 0, window.getSize().x, 0, grid.getColumns());
}

int MouseListener::mapMouseYToRow(const sf::Event::MouseButtonEvent& event) {
    if (event.y <= grid.getYOffset()) return -1;
    return (int)map(event.y, grid.getYOffset(), window.getSize().y, 0, grid.getRows());
}

Tile* MouseListener::getTileFromMouse(const sf::Event::MouseButtonEvent& event, bool isStartOrGoal) {
    int x = mapMouseXToColumn(event);
    int y = mapMouseYToRow(event);

    if (isStartOrGoal) {
        if (x >= grid.getColumns())
            x = grid.getColumns() - 1;
        else if (x < 0)
            x = 0;
        if (y >= grid.getRows())
            y = grid.getRows() - 1;
        else if (y < 0)
            y = 0;
    } else {
        if (x >= grid.getColumns())
            x = -1;
        else if (x < 0)
            x = -1;
        if (y >= grid.getRows())
            y = -1;
        else if (y < 0)
            y = -1;
    }

    return (x < 0 || y < 0 ) ? nullptr : grid.getTile(x, y);
}

void MouseListener::setTileState(const sf::Event::MouseButtonEvent& event, bool calledOnMousePressed) {
    Tile* tile = getTileFromMouse({ event.x, event.y }, startPressed || goalPressed);

    if (tile == nullptr) return;
    
    if (calledOnMousePressed) {
        if (tile->isStart())
            startPressed = true;
        if (tile->isGoal())
            goalPressed = true;
    }

    if (startPressed) {
        grid.uiSetStartTile(tile);
    } else if (goalPressed) {
        grid.uiSetGoalTile(tile);
    } else if (event.button == sf::Mouse::Left) {
        tile->setSolid(true);
    } else if (event.button == sf::Mouse::Right) {
        tile->setSolid(false);
    }
}

void MouseListener::setTileState(const sf::Event::MouseMoveEvent& event) {
    Tile* tile = getTileFromMouse(event, startPressed || goalPressed);

    if (tile == nullptr) return;

    if (startPressed) {
        grid.uiSetStartTile(tile);
    }
    else if (goalPressed) {
        grid.uiSetGoalTile(tile);
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        tile->setSolid(true);
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        tile->setSolid(false);
    }
}

MouseListener::MouseListener(Grid& grid, Canvas& canvas, sf::RenderWindow& window) : grid(grid), canvas(canvas), window(window) {
    startPressed = false;
    goalPressed = false;
}

void MouseListener::handleEvent(const sf::Event& event) {
    if (!canvas.searchNotRunning()) return;

    switch (event.type) {
    case sf::Event::MouseButtonPressed:
        setTileState(event.mouseButton, true);
        break;
    case sf::Event::MouseButtonReleased:
        if (startPressed || goalPressed) {
            getTileFromMouse(event.mouseButton, startPressed || goalPressed)->setSolid(false);
        }
        startPressed = goalPressed = false;
        break;
    case sf::Event::MouseMoved:
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            setTileState(event.mouseMove);
        }
        break;
    case sf::Event::MouseWheelScrolled:
        if (event.mouseWheelScroll.delta > 0) {
            grid.decrement(window.getSize().x, window.getSize().y);
        } else if (event.mouseWheelScroll.delta < 0) {
            grid.increment(window.getSize().x, window.getSize().y);
        }
        break;
    default:
        break;
    }
}
