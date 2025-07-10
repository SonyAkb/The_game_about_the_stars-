#pragma once

class Entity_Group {
public:
	int max_entity;//������������ ���������� �������� � ���� ������
	std::vector<std::string> Types_of_entity;//���� ���������

	Entity_Group() {
		max_entity = 5;
	}
	~Entity_Group() {};

	virtual void add(sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void clear() = 0;
};
