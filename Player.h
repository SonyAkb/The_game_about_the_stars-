#pragma once
#include "Entity.h"
#include <vector>
#include "Sounds.h"

class Enemy;
class Stars;

class Player: public Entity {
private:
	std::vector<std::string> name_of_laser{ "images/shots/laser_1.png", "images/shots/laser_2.png", "images/shots/laser_3.png", "images/shots/laser_4.png",
	 "images/shots/laser_5.png", "images/shots/laser_6.png", "images/shots/laser_7.png" };//���� ������
	int killed_enemies;//������ �����
	int health;//���������
	int number_of_lives;//������������ ���������� ������ �� ���
	std::vector<Entity*> shots_fired;//���������� �������
	int max_shots;//������������ ���������� �������
	int current_shots;//��������� ������
	int all_stars;//����� ������� �����
public:
	friend void check_mob_hit(Player& hero, Enemy& foe, Sounds& shoot);//������ ��������� ������/������/��������	
	friend void check_player_stars(Stars& star, Player& hero, float& time, Sounds& audio);//�������� ������� �� ������ ������

	Player(sf::Vector2f new_coords): Entity("images/player.png", new_coords, 0.08f, 0.08f) {
		health = number_of_lives = 3;
		killed_enemies = current_shots = all_stars = 0;
		max_shots = 5;
	}

	~Player() {};

	void change_the_position(sf::Vector2f new_coords) override {//����� ����������
		sf::Vector2f super_new_coords = sf::Vector2f(new_coords.x - (hitbox.x / 2), new_coords.y - (hitbox.y / 2));

		mob.setPosition(super_new_coords);
		borders_1 = sf::Vector2f(super_new_coords);//������� ��������
		borders_2 = sf::Vector2f(super_new_coords.x + hitbox.x, super_new_coords.y + hitbox.y);
	}

	bool add_shot(sf::Vector2f coords, Sounds& audio) {//�������� �������
		if (current_shots < max_shots) {//���� ���� ��������� ��������
			int random_laser = rand() % name_of_laser.size();//��� ������
			float shift = 0;
			switch (random_laser ){
			case 2:	
			case 6:
				shift = 14;
				break;
			case 5:
				shift = 11;
				break;
			
			default:
				shift = 7;
				break;
			}

			audio.play_random();//���� �������� ������
			Entity* laser_2 = new Entity(name_of_laser[random_laser], sf::Vector2f(coords.x - shift, coords.y - 5), 0.08f, 0.1f, 0);//������ ����� ������
			shots_fired.push_back(laser_2);//�������� ������ � ��� ���������� � ����� ��������
			current_shots++;//�������� ���������� ��������� �������

			return true;//�������� ������� ���������
		}
		return false;//��� �� ����� �� ���
	}

	void tracking_mobs_lives(sf::RenderWindow& window) {//����� ����� �� �������
		int count = 0;
		while (count < shots_fired.size()) {//���� �� ������ ��� ������
			shots_fired[count]->change_the_position(sf::Vector2f(shots_fired[count]->get_position_x(), shots_fired[count]->get_position_y() - shots_fired[count]->get_speed()));//������� ������
			if (shots_fired[count]->get_position_y() + 50 < 0) {
				shots_fired.erase(shots_fired.begin() + count);
			}
			else {
				window.draw(shots_fired[count]->mob);
				++count;
			}
		}
	}

	void damage() {//���� ������
		--health;
	}
	int get_health() {//������� ��������
		return health;
	}
	int get_killed_enemies() {//������ �����
		return killed_enemies;
	}
	void a_new_murder() {//�������� ��� ������ ������������ �����
		++killed_enemies;
	}

	bool is_died() {//����� �����������?
		return health <= 0;
	}

	void draw_all_shots(sf::RenderWindow& window) {//��������� ���� ����� ��������
		for (int i = 0; i < shots_fired.size(); i++) {//������� ������ - ���������
			window.draw(shots_fired[i]->mob);
		}
	}

	void clear() {
		health = number_of_lives = 3;
		killed_enemies = current_shots = all_stars = 0;
		max_shots = 5;
		shots_fired.clear();//���������� �������� ���
	}

	int get_shots() {//���������� ��������� �������
		return current_shots;
	}
	int get_max_shots() {//������������ ���������� ���������
		return max_shots;
	}

	void add_one_shots() {//���������� ���������� ��������� �������
		if (current_shots > 0) {
			--current_shots;
		}
	}

	int get_stars() {//������� ���� ������� �����
		return all_stars;
	}

	void add_one_star() {//�������� ���� ��������� ������
		++all_stars;
	}
};



