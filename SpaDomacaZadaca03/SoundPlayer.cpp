#include "SoundPlayer.h"

#include <iostream>
#include <fstream>
#include <thread>

static float map(float val, float valLow, float valHigh, float returnValLow, float returnValHigh) {
	float ratio = (val - valLow) / (valHigh - valLow);
	return ratio * (returnValHigh - returnValLow) + returnValLow;
}

void SoundPlayer::loadSoundData() {
	std::ifstream file("advance.wav", std::ios::binary | std::ios::ate);
	if (!file) {
		std::cerr << "Error loading advance.wav" << std::endl;
		return;
	}
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	fileData.resize(size);
	if (!file.read(fileData.data(), size)) {
		std::cerr << "Error reading advance.wav" << std::endl;
	}
}

SoundPlayer::SoundPlayer() {
	maxHCost = 1;
	volume = 30.f;

    if (!startBuffer.loadFromFile("start.wav")) {
        std::cerr << "Error loading start.wav" << std::endl;
    }
    if (!foundBuffer.loadFromFile("found.wav")) {
        std::cerr << "Error loading found.wav" << std::endl;
    }
    startSound.setBuffer(startBuffer);
    foundSound.setBuffer(foundBuffer);
    startSound.setVolume(volume);
    foundSound.setVolume(volume);

	loadSoundData();
}

void SoundPlayer::play(int hCost) {
    float pitch = map(hCost, 0, maxHCost, 1.8f, 0.2f);

    sf::Music* music = new sf::Music();
    if (!music->openFromMemory(fileData.data(), fileData.size())) {
        std::cerr << "Error playing sound from memory" << std::endl;
        delete music;
        return;
    }
    music->setVolume(volume);
    music->setPitch(pitch);
    music->play();

    music->setLoop(false);
    sf::Music* musicPtr = music;
    music->setPlayingOffset(sf::seconds(0));

    std::thread([musicPtr]() {
        while (musicPtr->getStatus() == sf::Music::Playing) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        delete musicPtr;
        }).detach();
}

void SoundPlayer::setMaxHCost(int maxHCost) {
	this->maxHCost = maxHCost;
}

void SoundPlayer::playStartSound() {
    startSound.play();
    while (startSound.getStatus() == sf::Sound::Playing) {
        sf::sleep(sf::milliseconds(10));
    }
}

void SoundPlayer::playFoundSound() {
    foundSound.play();
}
