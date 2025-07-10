#pragma once
#include <SFML/Audio.hpp>

class One_sound {//один звук
private:
	sf::SoundBuffer shootBuffer;//создаём буфер для звука
	sf::Sound audio;//создаем звук и загружаем в него звук из буфера
public:
	One_sound(std::string name, float num = 100.f) {
		shootBuffer.loadFromFile(name);
		audio = sf::Sound(shootBuffer);
		audio.setVolume(num);
	}
	~One_sound() {};

	void play() {
		audio.play();
	}

	void stop() {
		audio.stop();
	}
};