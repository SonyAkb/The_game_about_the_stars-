#pragma once
#include "Entity.h"
#include <vector>
#include "Sounds.h"

class Enemy;
class Stars;

class Player: public Entity {
private:
	std::vector<std::string> name_of_laser{ "images/shots/laser_1.png", "images/shots/laser_2.png", "images/shots/laser_3.png", "images/shots/laser_4.png",
	 "images/shots/laser_5.png", "images/shots/laser_6.png", "images/shots/laser_7.png" };//типы врагов
	int killed_enemies;//убитые враги
	int health;//здорорвье
	int number_of_lives;//максимальное количество жизней за раз
	std::vector<Entity*> shots_fired;//выпущенные снар€ды
	int max_shots;//максимальное количество зао€дов
	int current_shots;//доступные зар€ды
	int all_stars;//всего собрано звезд
public:
	friend void check_mob_hit(Player& hero, Enemy& foe, Sounds& shoot);//свер€ю попадание рокеты/врагов/снар€дов	
	friend void check_player_stars(Stars& star, Player& hero, float& time, Sounds& audio);//провер€ю собрала ли рокета звезду

	Player(sf::Vector2f new_coords): Entity("images/player.png", new_coords, 0.08f, 0.08f) {
		health = number_of_lives = 3;
		killed_enemies = current_shots = all_stars = 0;
		max_shots = 5;
	}

	~Player() {};

	void change_the_position(sf::Vector2f new_coords) override {//мен€ю координаты
		sf::Vector2f super_new_coords = sf::Vector2f(new_coords.x - (hitbox.x / 2), new_coords.y - (hitbox.y / 2));

		mob.setPosition(super_new_coords);
		borders_1 = sf::Vector2f(super_new_coords);//границы хитбокса
		borders_2 = sf::Vector2f(super_new_coords.x + hitbox.x, super_new_coords.y + hitbox.y);
	}

	bool add_shot(sf::Vector2f coords, Sounds& audio) {//добавл€ю выстрел
		if (current_shots < max_shots) {//если есть доступные выстрелы
			int random_laser = rand() % name_of_laser.size();//вид лазера
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

			audio.play_random();//звук выстрела лазера
			Entity* laser_2 = new Entity(name_of_laser[random_laser], sf::Vector2f(coords.x - shift, coords.y - 5), 0.08f, 0.1f, 0);//создаю новый снар€д
			shots_fired.push_back(laser_2);//добавл€ю снар€д к уже выпущенным и живым снар€дам
			current_shots++;//уменьшаю количество доступных зао€дов

			return true;//операци€ успешно выполнена
		}
		return false;//что то пошло не так
	}

	void tracking_mobs_lives(sf::RenderWindow& window) {//лазер вышел за границу
		int count = 0;
		while (count < shots_fired.size()) {//пока не пройду все лазеры
			shots_fired[count]->change_the_position(sf::Vector2f(shots_fired[count]->get_position_x(), shots_fired[count]->get_position_y() - shots_fired[count]->get_speed()));//сдвигаю снар€д
			if (shots_fired[count]->get_position_y() + 50 < 0) {
				shots_fired.erase(shots_fired.begin() + count);
			}
			else {
				window.draw(shots_fired[count]->mob);
				++count;
			}
		}
	}

	void damage() {//урон игроку
		--health;
	}
	int get_health() {//текущее здоровье
		return health;
	}
	int get_killed_enemies() {//убитые враги
		return killed_enemies;
	}
	void a_new_murder() {//добавл€ю еще одного поверженного врага
		++killed_enemies;
	}

	bool is_died() {//жизни закончились?
		return health <= 0;
	}

	void draw_all_shots(sf::RenderWindow& window) {//отрисовка всех живых снар€дов
		for (int i = 0; i < shots_fired.size(); i++) {//снар€ды ракеты - отрисовка
			window.draw(shots_fired[i]->mob);
		}
	}

	void clear() {
		health = number_of_lives = 3;
		killed_enemies = current_shots = all_stars = 0;
		max_shots = 5;
		shots_fired.clear();//выпущенных снар€дов нет
	}

	int get_shots() {//количество ƒќ—“”ѕЌџ’ зар€дов
		return current_shots;
	}
	int get_max_shots() {//ћј —»ћјЋ№Ќќ≈ количество выстрелов
		return max_shots;
	}

	void add_one_shots() {//увеличиваю количество доступных зар€дов
		if (current_shots > 0) {
			--current_shots;
		}
	}

	int get_stars() {//сколько было собрано звезд
		return all_stars;
	}

	void add_one_star() {//добавл€ю одну собранную звезду
		++all_stars;
	}
};



