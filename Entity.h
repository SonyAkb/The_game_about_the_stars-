#pragma once
#include "not_a_living_entity.h"

class Entity: public  not_a_living_entity {
public:
	float speed_side; //������� ��������
	sf::Vector2f hitbox;
	sf::Vector2f borders_1;
	sf::Vector2f borders_2;
	
	Entity(std::string name_img, sf::Vector2f new_coords, float size_, float fast = 0, float sp_sd = 0): not_a_living_entity(name_img, new_coords, size_, fast){
		speed_side = sp_sd; //������� ��������
		hitbox = sf::Vector2f(mob.getTextureRect().width * size_, mob.getTextureRect().height * size_);

		borders_1 = sf::Vector2f(new_coords);//������� ��������
		borders_2 = sf::Vector2f(new_coords.x + hitbox.x, new_coords.y + hitbox.y);
	}

	~Entity() {};

	void change_the_position(sf::Vector2f new_coords) override{//����� ����������
		mob.setPosition(new_coords);
		borders_1 = sf::Vector2f(new_coords);//������� ��������
		borders_2 = sf::Vector2f(new_coords.x + hitbox.x, new_coords.y + hitbox.y);
	}
	
	void change_hitbox(sf::Vector2f new_hit) {//������� ������� ��������
		hitbox = new_hit;
		borders_2 = sf::Vector2f(borders_1.x + hitbox.x, borders_2.y + hitbox.y);
	}

	float get_speed_side() {//������� ��������
		return speed_side;
	}
	void set_speed_side_change() {//��������� ������� �������� �� ���������������
		speed_side *= (-1);
	}
};