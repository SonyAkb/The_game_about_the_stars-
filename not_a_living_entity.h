#pragma once
#include <SFML/Graphics.hpp>

class not_a_living_entity {
public:
	sf::Image image; //������� ������ Image (�����������)
	sf::Texture texture;//������� ������ Texture (��������)
	sf::Sprite mob;//������ ����

	float speed;//��������

	not_a_living_entity(std::string name_img, sf::Vector2f new_coords, float size_, float fast = 0) {
		speed = fast;

		image.loadFromFile(name_img);//��������� � ���� ����
		texture.loadFromImage(image);//�������� � ���� ������ Image (�����������)

		mob.setTexture(texture);//������� � ���� ������ Texture (��������)
		mob.setPosition(new_coords);//������ ��������� ���������� ��������� �������

		mob.setScale(size_, size_);
	}
	~not_a_living_entity() {};

	void draw(sf::RenderWindow& window) {//���������
		window.draw(mob);
	}

	virtual void change_the_position(sf::Vector2f new_coords) {//����� ����������
		mob.setPosition(new_coords);
	}

	void step() {//���
		mob.setPosition(sf::Vector2f(get_position_x(), get_position_y() + speed));
	}

	float get_position_y() {//������� �� x
		return mob.getPosition().y;
	}
	float get_position_x() {//������� �� y
		return mob.getPosition().x;
	}
	float get_speed() {//�������� ��������
		return speed;
	}
};