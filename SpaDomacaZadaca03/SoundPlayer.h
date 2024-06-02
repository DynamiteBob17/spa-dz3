#pragma once

#include <SFML/Audio.hpp>

class SoundPlayer {
private:
	std::vector<char> fileData;
	sf::SoundBuffer startBuffer;
	sf::SoundBuffer foundBuffer;
	sf::Sound startSound;
	sf::Sound foundSound;
	float volume;
	int maxHCost;

	void loadSoundData();

public:
	SoundPlayer();
	void play(int hCost);
	void setMaxHCost(int maxHCost);
	void playStartSound();
	void playFoundSound();
};
