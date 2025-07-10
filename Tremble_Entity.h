#pragma once
#include "Entity.h"

class Tremble_Entity : public Entity {
	sf::Vector2f cage_1;
	sf::Vector2f cage_2;
public:
	Tremble_Entity(std::string name_img, sf::Vector2f new_coords, sf::Vector2f first_cage, sf::Vector2f last_cage, float size_, float fast = 0, float side_fast = 0) :
		Entity(name_img, new_coords, size_, fast, side_fast) {
		cage_1 = first_cage;
		cage_2 = last_cage;
	}
	~Tremble_Entity() {};

	void draw(sf::RenderWindow& window) {
		if (speed_side && (borders_1.x < cage_1.x || borders_2.x > cage_2.x)) {
			speed_side = speed_side * (-1);
		}
		if (speed && (borders_1.y < cage_1.y || borders_2.y > cage_2.y)) {
			speed = speed * (-1);
		}
		change_the_position(sf::Vector2f(get_position_x() + speed_side, get_position_y() + speed));
		window.draw(mob);
	}
};