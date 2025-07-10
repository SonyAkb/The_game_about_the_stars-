#pragma once
#include "Entity_Group.h"
#include "Temporary_Entity.h"

class Player;
class Sounds;

class Stars : public Entity_Group {
private:
	std::vector<Temporary_Entity*> All_entity;
public:
	Stars(): Entity_Group(){
		max_entity = 10;
		Types_of_entity = { "images/stars/star_1.png", "images/stars/star_2.png", "images/stars/star_3.png", "images/stars/star_4.png", "images/stars/star_5.png", 
			"images/stars/star_6.png", "images/stars/star_7.png", "images/stars/star_8.png", "images/stars/star_9.png", "images/stars/star_10.png" };
	}
	~Stars() {};

	friend void check_player_stars(Stars& star, Player& hero, float& time, Sounds& audio);//проверка: игрок подобрал звезду?

	void add(sf::RenderWindow& window) override {//добавление новой звезды
		if (All_entity.size() < max_entity) {
			Temporary_Entity* new_N = new Temporary_Entity(Types_of_entity[random_int(Types_of_entity.size())], sf::Vector2f(random_int(window.getSize().x - 100) + 50, random_int(window.getSize().y - 100) + 50), random_float(0.2f, 0.05f));
			All_entity.push_back(new_N);
		}
	}

	void draw(sf::RenderWindow& window) override{//отрисовываю и сразу ибиваю тех, кто вышел за низ экрана
		int i = 0;
		while (i < All_entity.size()) {//прохожу по всем туманностям
			if (All_entity[i]->get_time_current_life() >= All_entity[i]->get_time_of_life()) {//если время жизни вышло
				All_entity.erase(All_entity.begin() + i);//убиваю
			}
			else {
				window.draw(All_entity[i++]->mob);

			}
		}
	}

	void clear() override {//очищение
		max_entity = 10;
		All_entity.clear();
	}

	int get_q_stars() {//количество существующих звезд в данный момент
		return All_entity.size();
	}
};
