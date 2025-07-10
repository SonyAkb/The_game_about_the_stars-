#pragma once
#include "Entity_Group.h"

class Nebulas: public Entity_Group {
private:
	std::vector<not_a_living_entity*> All_entity;//все возможные сущности
public:
	Nebulas() {
		max_entity = 10;
		Types_of_entity = { "images/nebulas/nebula_1.png", "images/nebulas/nebula_2.png", "images/nebulas/nebula_3.png", "images/nebulas/nebula_4.png", 
			"images/nebulas/nebula_5.png", "images/nebulas/nebula_6.png", "images/nebulas/nebula_7.png", "images/nebulas/nebula_8.png", 
			"images/nebulas/nebula_9.png", "images/nebulas/nebula_10.png", "images/nebulas/nebula_11.png", "images/nebulas/nebula_12.png", 
			"images/nebulas/nebula_13.png" };
	}

	~Nebulas() {};

	void add(sf::RenderWindow& window) override {	
		if (All_entity.size() < max_entity) {
			not_a_living_entity* new_N = new not_a_living_entity(Types_of_entity[random_int(Types_of_entity.size())], sf::Vector2f(random_int(window.getSize().x),  -500), random_float(0.8f, 0.02f), random_float(0.08f, 0.01f));
			All_entity.push_back(new_N);
		}
	}

	void add_several(sf::RenderWindow& window, const int& num) {//добавить сразу несколько туманностей
		for (int i = 0; i < num; i++) {
			add(window);
		}
	}

	void draw(sf::RenderWindow& window){//отрисовываю и сразу ибиваю тех, кто вышел за низ экрана
		int i = 0;
		while (i < All_entity.size()) {//прохожу по всем туманностям
			if (All_entity[i]->get_position_y() > window.getSize().y + 10) {//если вышел за низ экрана
				All_entity.erase(All_entity.begin() + i);//убиваю
			}
			else {
				All_entity[i]->step();//передвигаю
				window.draw(All_entity[i++]->mob);
			}
		}
	}

	void clear() override {//очищение
		max_entity = 10;
		All_entity.clear();
	}
};
