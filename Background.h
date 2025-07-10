#pragma once
#include "Entity.h"
#include <iostream>
class Background : Entity {
public:
	Background(std::string name_img, sf::Vector2f new_coords, float size_, float fast = 0) : 
		Entity(name_img, new_coords, size_, fast) {
	}
	~Background() {};

	void cyclic_image(sf::RenderWindow& window, float distance = -2460) {//циклический сдвиг изображения для зацикливания
		if (borders_1.y > window.getSize().y) {
			change_the_position(sf::Vector2f(get_position_x(), distance));
		}
		change_the_position(sf::Vector2f(get_position_x(), get_position_y() + speed));//сдвигаю
	}

	void Do_I_need_to_draw(sf::RenderWindow& window) {//надо ли отрисовывать сейчас? т.е. видит ли игрок?
		if (!(borders_1.y > window.getSize().y || borders_2.y < 0)) {
			draw(window);
		}
	}
};