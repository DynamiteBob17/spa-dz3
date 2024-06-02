#include "SearchAlgorithm.h"

#include <chrono>

bool SearchAlgorithm::commonMiddleStep(Tile* current) {
    current->setChecked(true);
    soundPlayer.play(current->getHCost());

    while (canvas.isPauseRunningSearch() && !canvas.isStopRunningSearch())
        sleep();

    if (current->isGoal())
        soundPlayer.playFoundSound();

    return current->isGoal() || canvas.isStopRunningSearch();
}

void SearchAlgorithm::trackAndFillPath() {
    Tile* current = goalTile;

    while (current->hasParent()) {
        current->setPath(true);
        soundPlayer.play(current->getHCost());
        sleep();
        current = current->getParent();
    }

    current->setPath(true);
    soundPlayer.play(current->getHCost());
}

void SearchAlgorithm::sleep() {
    long nano = long(sleepMs * 1'000'000.0);
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start;
    while (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < nano) {
        end = std::chrono::high_resolution_clock::now();
    }
}

static double map(double val, double valLow, double valHigh, double returnValLow, double returnValHigh) {
    double ratio = (val - valLow) / (valHigh - valLow);
    return ratio * (returnValHigh - returnValLow) + returnValLow;
}

void SearchAlgorithm::precalculateSleep() {
    sleepMs = (long)(map(grid.getSteps(), 0, Grid::MAX_STEPS, sleepMax(), sleepMin()));
}

SearchAlgorithm::SearchAlgorithm(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer)
    : grid(grid), canvas(canvas), soundPlayer(soundPlayer), startTile(nullptr), goalTile(nullptr), sleepMs(0L) {}

void SearchAlgorithm::run() {
    precalculateSleep();

    canvas.setSearchRunning(true);
    canvas.setStopRunningSearch(false);
    canvas.turnOffPauseRunningSearch();

    startTile = grid.getStartTile();
    goalTile = grid.getGoalTile();
    grid.calculateHCosts();
    soundPlayer.setMaxHCost(grid.calculateMaxHCost());

    soundPlayer.playStartSound();
    search();

    if (!canvas.isStopRunningSearch()) {
        trackAndFillPath();
    }

    canvas.setSearchRunning(false);
    canvas.setStopRunningSearch(false);
    canvas.turnOffPauseRunningSearch();
}
