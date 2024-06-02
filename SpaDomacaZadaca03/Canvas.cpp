#include "Canvas.h"
#include "util.h"

const int Canvas::INITIAL_WIDTH = (int)(1280 * Util::SCALE);
const int Canvas::INITIAL_HEIGHT = (int)(720 * Util::SCALE);

Canvas::Canvas(sf::RenderWindow& window, Grid& grid)
    : window(window), grid(grid), pauseRunningSearch(false), searchRunning(false), stopRunningSearch(false) {
}

void Canvas::draw() {
    grid.draw(window);
}

bool Canvas::searchNotRunning() {
    return !searchRunning;
}

bool Canvas::isPauseRunningSearch() {
    return pauseRunningSearch;
}

bool Canvas::isStopRunningSearch() {
    return stopRunningSearch;
}

void Canvas::setSearchRunning(bool searchRunning) {
    this->searchRunning = searchRunning;
}

void Canvas::togglePauseRunningSearch() {
    this->pauseRunningSearch = !pauseRunningSearch;
}

void Canvas::turnOffPauseRunningSearch() {
    pauseRunningSearch = false;
}

void Canvas::setStopRunningSearch(bool stopRunningSearch) {
    this->stopRunningSearch = stopRunningSearch;
}
