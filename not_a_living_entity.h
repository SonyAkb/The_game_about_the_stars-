#pragma once
#include <SFML/Graphics.hpp>

class not_a_living_entity {
public:
	sf::Image image; //создаем объект Image (изображение)
	sf::Texture texture;//создаем объект Texture (текстура)
	sf::Sprite mob;//спрайт моба

	float speed;//скорость

	not_a_living_entity(std::string name_img, sf::Vector2f new_coords, float size_, float fast = 0) {
		speed = fast;

		image.loadFromFile(name_img);//загружаем в него файл
		texture.loadFromImage(image);//передаем в него объект Image (изображени€)

		mob.setTexture(texture);//передаЄм в него объект Texture (текстуры)
		mob.setPosition(new_coords);//задаем начальные координаты по€влени€ спрайта

		mob.setScale(size_, size_);
	}
	~not_a_living_entity() {};

	void draw(sf::RenderWindow& window) {//отрисовка
		window.draw(mob);
	}

	virtual void change_the_position(sf::Vector2f new_coords) {//мен€ю координаты
		mob.setPosition(new_coords);
	}

	void step() {//шаг
		mob.setPosition(sf::Vector2f(get_position_x(), get_position_y() + speed));
	}

	float get_position_y() {//позици€ по x
		return mob.getPosition().y;
	}
	float get_position_x() {//позици€ по y
		return mob.getPosition().x;
	}
	float get_speed() {//скорость сущности
		return speed;
	}
};