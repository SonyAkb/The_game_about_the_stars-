#pragma once
#include <SFML/Audio.hpp>
#include <string>

class Background_Music {//������� ������
	sf::Music music;//������� ������ ������
public:
	Background_Music(std::string name, const float& num = 100.f, bool flag = true) {
		music.openFromFile(name);//��������� ����
		music.setVolume(num);//��������� ������
		music.setLoop(flag);//������������ ������
	}
	~Background_Music() {};

	void play() {
		music.play();//������������� ������
	}

	void pause() {//�����
		music.pause();
	}

	void stop() {//��������� � ��������� �����
		music.stop();
	}
};