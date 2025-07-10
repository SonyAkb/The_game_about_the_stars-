#pragma once
#include <vector>
#include "One_sound.h"

class Sounds {
private:
	std::vector<One_sound*> Types_of_sound;//все возможные звуки

public:
	Sounds(std::vector<std::pair<std::string, float>>& all_sounds) {
		add_several(all_sounds);
	}
	~Sounds() {};

	void add_one(std::string name, const float& num = 100) {//добавляю один звук в вектор
		One_sound* noise = new One_sound(name, num);
		Types_of_sound.push_back(noise);
	}

	void add_several(std::vector<std::pair<std::string, float>>& all_sounds) {	//добавляю несколько звуков
		for (int i = 0; i < all_sounds.size(); i++) {
			add_one(all_sounds[i].first, all_sounds[i].second);
		}
	}

	void play_random() {//проигрываю случайный звук из вектора
		Types_of_sound[rand() % Types_of_sound.size()]->play();
	}

};