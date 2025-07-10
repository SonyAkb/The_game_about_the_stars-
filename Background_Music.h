#pragma once
#include <SFML/Audio.hpp>
#include <string>

class Background_Music {//фоновая музыка
	sf::Music music;//создаем объект музыки
public:
	Background_Music(std::string name, const float& num = 100.f, bool flag = true) {
		music.openFromFile(name);//загружаем файл
		music.setVolume(num);//громкость музыки
		music.setLoop(flag);//зацикливание музыки
	}
	~Background_Music() {};

	void play() {
		music.play();//воспроизводим музыку
	}

	void pause() {//пауза
		music.pause();
	}

	void stop() {//остановка и перемотка назад
		music.stop();
	}
};