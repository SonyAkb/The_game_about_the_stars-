#pragma once
#include "Entity.h"
#include "others_functions.h"

class Temporary_Entity : public Entity {
private:
	int time_of_life;//сколько будет жить всего
	int current_time;//сколько уже прожил
public:
	Temporary_Entity(std::string name_img, sf::Vector2f new_coords, float size_, float fast = 0) : Entity(name_img, new_coords, size_, fast) {
		time_of_life = random_int(600, 100);
		current_time = 0;
	}
	~Temporary_Entity() {};

	bool One_more_moment_has_been_lived(int time) {//меняю время жизни, проверяю будет ли еще жить
		current_time += time;//увеличиваю прожитое время
		if (current_time >= time_of_life) {
			return true;
		}
		return false;
	}

	int get_time_of_life(){//сколько всего будет жить
		return time_of_life;
	}

	int get_time_current_life() {//сколько УЖЕ живет
		return current_time;
	}

	void set_time_now(float time){
		current_time += time;
	}
};