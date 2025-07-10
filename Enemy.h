#pragma once
#include "Entity_Group.h"
#include <vector>

class Player;
class Sound;

class Enemy: public Entity_Group{
private:
	std::vector<Entity*> All_enemies;
public:
	friend void check_mob_hit(Player& hero, Enemy& foe, Sounds& shoot);//������ ��������� ������/������/��������

	Enemy() {//�����������
		Types_of_entity = { "images/enemy/meteorite_1.png", "images/enemy/meteorite_2.png", "images/enemy/meteorite_3.png",  "images/enemy/meteorite_4.png", 
			"images/enemy/meteorite_5.png", "images/enemy/meteorite_6.png",  "images/enemy/meteorite_7.png", "images/enemy/meteorite_8.png", 
			"images/enemy/meteorite_9.png", "images/enemy/meteorite_10.png", "images/enemy/meteorite_11.png", "images/enemy/meteorite_12.png", 
			"images/enemy/meteorite_13.png", "images/enemy/meteorite_14.png" };
		max_entity = 13;
	}
	~Enemy() {};//����������

	void add(sf::RenderWindow& window) override {
		int type = rand() % Types_of_entity.size();//��� �����
		float size = (rand() % 1600 + 200) * 0.0001;//������
		float side;//������� ��������
		if (rand() % 4 == 0) {
			side = 0;//���� ���� �� ������
		}
		else {
			side = random_float(0.08f, -0.08f);//���� ���� ������ ��������
		}	
		float fast = (rand() % 10 + 2) * 0.01;//������������ ��������
		float x = ((rand() % (window.getSize().x - 100)) + 50);//�, ��� �������� ����
		
		Entity* new_mob = new Entity(Types_of_entity[type], sf::Vector2f(x, -100), size, fast, side);//����� ����
		All_enemies.push_back(new_mob);//�������� ����� � ������ ������
	}

	void add_all_possible_enemies(sf::RenderWindow& window) {//�������� ����� ��������� ������ �� ������������� ����������
		while (All_enemies.size() < max_entity) {
			add(window);
		}
	}

	void draw(sf::RenderWindow& window) override {//������ �������� �� ������� ������ ������ � ����������� �����
		int count = 0;
		int shift_side;
		int shift_length;
		while (count < All_enemies.size()) {
			if (All_enemies[count]->borders_1.x < 0 || All_enemies[count]->borders_2.x > window.getSize().x) {
				All_enemies[count]->set_speed_side_change();
			}
			All_enemies[count]->change_the_position(sf::Vector2f(All_enemies[count]->get_position_x() + All_enemies[count]->get_speed_side(), All_enemies[count]->get_position_y() + All_enemies[count]->get_speed()));//������� ������

			if (All_enemies[count]->get_position_y() > window.getSize().y) {
				All_enemies.erase(All_enemies.begin() + count);
			}
			else {
				window.draw(All_enemies[count++]->mob);
			}
		}
	}
	
	int get_current_quantity() {//���������� ������
		return All_enemies.size();
	}
	
	void clear() override{//������ ������ ������
		max_entity = 10;
		All_enemies.clear();
	}
};

