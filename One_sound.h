#pragma once
#include <SFML/Audio.hpp>

class One_sound {//���� ����
private:
	sf::SoundBuffer shootBuffer;//������ ����� ��� �����
	sf::Sound audio;//������� ���� � ��������� � ���� ���� �� ������
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