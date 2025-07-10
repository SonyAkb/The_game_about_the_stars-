#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.h"
#include "Stars.h"
#include "Enemy.h"
#include "sfml_button.hpp"
#include "Background.h"
#include "Sounds.h"
#include "Nebulas.h"
#include "Background_Music.h"
#include "Tremble_Entity.h"

sf::Color background_color(0, 0, 0);//���
sf::Color text_color(255, 255, 255);//�����

std::vector<std::pair<std::string, float>> Types_of_explosion{ {"music/explosion/blast_1.ogg", 55}, {"music/explosion/blast_2.ogg", 90 }, {"music/explosion/blast_3.ogg", 100 }, {"music/explosion/blast_4.ogg", 60 }, {"music/explosion/blast_5.ogg", 80 } };
std::vector<std::pair<std::string, float>> Types_of_laser{ {"music/laser/sound_laser_1.ogg", 90}, {"music/laser/sound_laser_2.ogg", 100}, {"music/laser/sound_laser_3.ogg", 100}, {"music/laser/sound_laser_4.ogg", 100}, {"music/laser/sound_laser_5.ogg", 100}, {"music/laser/sound_laser_6.ogg", 100} };
std::vector<std::pair<std::string, float>> Types_of_get_star{ {"music/success/get_star_sound_1.ogg", 100}, {"music/success/get_star_sound_2.ogg", 100}, { "music/success/get_star_sound_3.ogg", 100 }, { "music/success/get_star_sound_4.ogg", 100 }, { "music/success/get_star_sound_5.ogg", 80 } };

void start_game(bool Flag_god_mode = false);

void clear_all(Player& hero, Enemy& foe, sf::RenderWindow& window, Nebulas& neb, Stars& star) {//�������� ����
    window.clear(background_color);//������ �����
    hero.clear();
    foe.clear();
    neb.clear();
    star.clear();
}

void current_health(Player& hero, sf::RenderWindow& window, not_a_living_entity& image) {//����� �������� ��������
    int start_x = window.getSize().x - 50;
    for (int i = 0; i < hero.get_health(); i++) {
        image.change_the_position(sf::Vector2f(start_x -= 40, image.get_position_y()));//������ ��������� ���������� ��������� �������
        image.draw(window);
    }
}

void current_laser(Player& hero, sf::RenderWindow& window, not_a_living_entity& image) {//������� ���������� ��������� �������
    int start_x = -50;
    for (int i = 0; i < hero.get_max_shots() - hero.get_shots(); i++) {
        image.change_the_position(sf::Vector2f(start_x += 55, image.get_position_y()));//������ ��������� ���������� ��������� �������
        image.draw(window);
    }
}

void check_mob_hit(Player& hero, Enemy& foe, Sounds& shoot) {//�������� ������������
    int l_count, en_count = 0;
    bool flag_enemy = true;

    while (en_count < foe.All_enemies.size()) {//�������� ���� ������
        l_count = 0;
        flag_enemy = true;//������� ���� ��� ���

        while (l_count < hero.shots_fired.size() && flag_enemy) {//�������� ��� ���������� �������

            if (((hero.shots_fired[l_count]->borders_2.x > foe.All_enemies[en_count]->borders_1.x && hero.shots_fired[l_count]->borders_2.x < foe.All_enemies[en_count]->borders_2.x) ||
                (hero.shots_fired[l_count]->borders_1.x > foe.All_enemies[en_count]->borders_1.x && hero.shots_fired[l_count]->borders_1.x < foe.All_enemies[en_count]->borders_2.x)) &&
                ((hero.shots_fired[l_count]->borders_2.y > foe.All_enemies[en_count]->borders_1.y && hero.shots_fired[l_count]->borders_2.y < foe.All_enemies[en_count]->borders_2.y) ||
                    (hero.shots_fired[l_count]->borders_1.y > foe.All_enemies[en_count]->borders_1.y && hero.shots_fired[l_count]->borders_1.y < foe.All_enemies[en_count]->borders_2.y))) {
                hero.shots_fired.erase(hero.shots_fired.begin() + l_count);//������ ������
                foe.All_enemies.erase(foe.All_enemies.begin() + en_count);//������ �����
                flag_enemy = false;
                shoot.play_random();
                hero.a_new_murder();//�������� ������� �����
            }
            else {
                ++l_count;
            }
        }
        if (flag_enemy) {//���� ���� ��� ���
            if (((hero.borders_2.x > foe.All_enemies[en_count]->borders_1.x && hero.borders_2.x < foe.All_enemies[en_count]->borders_2.x) ||
                (hero.borders_1.x > foe.All_enemies[en_count]->borders_1.x && hero.borders_1.x < foe.All_enemies[en_count]->borders_2.x)) &&
                ((hero.borders_2.y > foe.All_enemies[en_count]->borders_1.y && hero.borders_2.y < foe.All_enemies[en_count]->borders_2.y) ||
                    (hero.borders_1.y > foe.All_enemies[en_count]->borders_1.y && hero.borders_1.y < foe.All_enemies[en_count]->borders_2.y))) {
                foe.All_enemies.erase(foe.All_enemies.begin() + en_count);//������ �����
                shoot.play_random();
                hero.damage();//����� ������ �����
                hero.a_new_murder();//�������� ������� �����
            }
            else {
                ++en_count;
            }
        }
    }
}

void check_player_stars(Stars& star, Player& hero, float& time, Sounds& audio) {//����� ������ ������?
    int i = 0;
    while (i < star.get_q_stars()) {
        if (((hero.borders_2.x > star.All_entity[i]->borders_1.x && hero.borders_2.x < star.All_entity[i]->borders_2.x) ||
            (hero.borders_1.x > star.All_entity[i]->borders_1.x && hero.borders_1.x < star.All_entity[i]->borders_2.x)) &&
            ((hero.borders_2.y > star.All_entity[i]->borders_1.y && hero.borders_2.y < star.All_entity[i]->borders_2.y) ||
                (hero.borders_1.y > star.All_entity[i]->borders_1.y && hero.borders_1.y < star.All_entity[i]->borders_2.y))) {
            hero.add_one_star();
            star.All_entity.erase(star.All_entity.begin() + i);//������ ������
            audio.play_random();
        }
        else {
            star.All_entity[i]->set_time_now(time);
            ++i;
        }
    }
}

void menu() {//������� ����
    sf::Font jackInput;
    int tmp_size_y = 450;

    sf::RenderWindow window(sf::VideoMode(770, 800), L"Menu");//������� ����
    jackInput.loadFromFile("ofont.ru_Nikoleta.ttf");

    sf::Image icon;
    icon.loadFromFile("images/enemy/meteorite_14.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    RectButton button_1(sf::Vector2f(360, 40), sf::Vector2f(window.getSize().x / 2 - 170, tmp_size_y += 50));
    button_1.setButtonFont(jackInput);
    button_1.setButtonLable(L"������ ����", text_color, 30);

    RectButton button_3(sf::Vector2f(360, 40), sf::Vector2f(window.getSize().x / 2 - 170, tmp_size_y += 50));
    button_3.setButtonFont(jackInput);
    button_3.setButtonLable(L"����������� ����", text_color, 30);

    RectButton button_2(sf::Vector2f(360, 40), sf::Vector2f(window.getSize().x / 2 - 170, tmp_size_y += 50));
    button_2.setButtonFont(jackInput);
    button_2.setButtonLable(L"�����", text_color, 30);

    Tremble_Entity end_logo("images/main_menu/logo_3.png", sf::Vector2f(200, 70),
        sf::Vector2f(window.getSize().x / 2 - 250, 60),
        sf::Vector2f(window.getSize().x / 2 + 250, 430), 0.4f, 0.005f, 0.005f);
    Tremble_Entity end_nebula_2("images/main_menu/nebula_1.png", sf::Vector2f(random_float(window.getSize().x / 3), random_float(window.getSize().y / 3)),
        sf::Vector2f(-250,-250),
        sf::Vector2f(window.getSize().x + 250, window.getSize().y + 250), 0.9f, 0.0055f, 0.0035f);
    
    Tremble_Entity end_nebula_4("images/nebulas/nebula_9.png", sf::Vector2f(-20, 10),
        sf::Vector2f(-300, 0),
        sf::Vector2f(1100, window.getSize().y / 2 + 150), 1.f, 0.004f, 0.005f);

    Background fon_1("images/main_menu/start_fon.png", sf::Vector2f(0, -390), 0.9f, 0.007f);
    Background fon_2("images/main_menu/start_fon.png", sf::Vector2f(-3, -1580), 0.9f, 0.007f);

    Background_Music general_music("music/background/fon_start.ogg");//������� ������
    general_music.play();

    while (window.isOpen()) {
        sf::Vector2i mousePoz = sf::Mouse::getPosition(window);//������� ���� � ����
        sf::Event event;

        button_1.getButtonStatus(window, event);
        button_2.getButtonStatus(window, event);
        button_3.getButtonStatus(window, event);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {

                if (event.key.code == sf::Mouse::Left) {
                    if (button_1.isPressed) {//������ ����
                        general_music.stop();
                        window.close();//�������� ��������� ����
                        start_game();//������� ����
                    }
                    if (button_2.isPressed) {//�����
                        general_music.stop();
                        window.close();//�������� ��������� ����
                    }
                    if (button_3.isPressed) {//������ ����������� ����
                        general_music.stop();
                        window.close();//�������� ��������� ����
                        start_game(true);//������� ����������� ����
                    }
                }
            }

        }
        window.clear(background_color);
        fon_1.cyclic_image(window, -1580);//���������� ���
        fon_2.cyclic_image(window, -1580);//���������� ���

        fon_1.Do_I_need_to_draw(window);//��� �����?
        fon_2.Do_I_need_to_draw(window);//��� �����?

        end_nebula_2.draw(window);
        end_nebula_4.draw(window);
        end_logo.draw(window);

        button_1.draw(window);
        button_2.draw(window);
        button_3.draw(window);

        window.display();
    }
}

bool you_died_menu() {//����� ����
    sf::Font jackInput;
    int end_size_y = 560;
    std::vector<Background> nebuls;

    sf::RenderWindow window(sf::VideoMode(800, 800), L"The end of the game");//������� ����
    jackInput.loadFromFile("ofont.ru_Nikoleta.ttf");

    sf::Image icon;
    icon.loadFromFile("images/enemy/meteorite_2.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    RectButton button_4(sf::Vector2f(360, 40), sf::Vector2f(window.getSize().x / 2 - 180, end_size_y += 60));//����� ���� - ������ ����� ����
    button_4.setButtonFont(jackInput);
    button_4.setButtonLable(L"����� ����", text_color, 30);

    RectButton button_5(sf::Vector2f(360, 40), sf::Vector2f(window.getSize().x / 2 - 180, end_size_y += 60));//����� ���� - ��������� � ����
    button_5.setButtonFont(jackInput);
    button_5.setButtonLable(L"��������� � ����", text_color, 30);

    not_a_living_entity you_died_logo("images/end_game/you_died.png", sf::Vector2f(window.getSize().x / 2 - 288, window.getSize().y / 2 + 40), 0.45f);//���� ������
    
    not_a_living_entity end_logo_background_1("images/end_game/fon_2.png", sf::Vector2f(0, -100), 0.75f);//��� ������
    not_a_living_entity end_logo_background_2("images/end_game/fon_3.png", sf::Vector2f(0, 250), 1.f);//��� ������
    Tremble_Entity end_logo("images/end_game/logo_1.png", sf::Vector2f(window.getSize().x / 2 - 257, 0),
        sf::Vector2f(window.getSize().x / 2 - 300, 0),
        sf::Vector2f(window.getSize().x / 2 + 300, 460), 0.6f, 0.001f, 0.002f);
    One_sound you_died_1("music/end_game/dark_souls_you_died.ogg");//���� ������
    you_died_1.play();

    while (window.isOpen()) {
        sf::Vector2i mousePoz = sf::Mouse::getPosition(window);//������� ���� � ����
        sf::Event event;

        button_4.getButtonStatus(window, event);//����� ����
        button_5.getButtonStatus(window, event);//����� � ����
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                you_died_1.stop();
                window.close();
                return false;
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {//���� ������� ����
                if (event.key.code == sf::Mouse::Left) {//���� ������ ����� ������
                    if (button_4.isPressed) {//����� ����
                        you_died_1.stop();
                        window.close();//�������� ����
                        return true;
                    }
                    if (button_5.isPressed) {//� ����
                        you_died_1.stop();
                        window.close();//�������� ����
                        return false;
                    }
                }
            }              
        }
        window.clear(background_color);//������ �����

        end_logo_background_1.draw(window);
        end_logo_background_2.draw(window);
        end_logo.draw(window);
        you_died_logo.draw(window);

        button_4.draw(window);
        button_5.draw(window);
        
        window.display();
    }
    return false;
}

void start_game(bool Flag_god_mode) {//������ ����
    sf::Font jackInput;
    int tmp_size_y = 20, pause_size_y = 430, end_size_y = 530;
    std::vector<Background> nebuls;

    sf::RenderWindow window(sf::VideoMode(800, 800), L"Asteroid game");//������� ����
    jackInput.loadFromFile("ofont.ru_Nikoleta.ttf");

    sf::Image icon;
    icon.loadFromFile("images/enemy/meteorite_3.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    RectButton button_1(sf::Vector2f(360, 40), sf::Vector2f(window.getSize().x / 2 - 180, pause_size_y += 60));
    button_1.setButtonFont(jackInput);
    button_1.setButtonLable(L"����������", text_color, 30);

    RectButton button_2(sf::Vector2f(360, 40), sf::Vector2f(window.getSize().x / 2 - 180, pause_size_y += 60));
    button_2.setButtonFont(jackInput);
    button_2.setButtonLable(L"������ � ������", text_color, 30);

    RectButton button_3(sf::Vector2f(360, 40), sf::Vector2f(window.getSize().x / 2 - 180, pause_size_y += 60));
    button_3.setButtonFont(jackInput);
    button_3.setButtonLable(L"��������� � ����", text_color, 30);

    Tremble_Entity pause_enemy_logo("images/logo/pause_enemy.png", sf::Vector2f((window.getSize().x / 2) - 320, -20),
        sf::Vector2f((window.getSize().x / 2) - 360, -30),
        sf::Vector2f((window.getSize().x / 2) + 360, window.getSize().y / 2 + 80), 0.8f, 0.002f, 0.004f);

    not_a_living_entity pause_background("images/logo/pause_fon.png", sf::Vector2f(0, 0), 0.8f);//��� �����
   
    Nebulas pause_additional_fon;//���������� �� �����
    pause_additional_fon.add_several(window, 2);
    Background_Music pause_general_music("music/background/fon_pause.ogg");//������� ������ ��� ����� 

    not_a_living_entity meteorite_kill("images/logo/logo_enemy.png", sf::Vector2f(window.getSize().x - 170, tmp_size_y), 0.07f);//���� ������
    sf::Text the_number_of_dead;
    the_number_of_dead.setFont(jackInput);
    the_number_of_dead.setString(L"0");
    the_number_of_dead.setFillColor(text_color);
    the_number_of_dead.setCharacterSize(40);
    the_number_of_dead.setPosition(window.getSize().x - 100, tmp_size_y);

    not_a_living_entity star_logo("images/logo/logo_star.png", sf::Vector2f(window.getSize().x - 170, tmp_size_y += 70), 0.09f);//���� �����
    sf::Text the_number_of_stars;
    the_number_of_stars.setFont(jackInput);
    the_number_of_stars.setString(L"0");
    the_number_of_stars.setFillColor(text_color);
    the_number_of_stars.setCharacterSize(40);
    the_number_of_stars.setPosition(window.getSize().x - 100, tmp_size_y);

    not_a_living_entity health_now("images/logo/logo_health.png", sf::Vector2f(50, tmp_size_y += 70), 0.08f);//������� ��������
    not_a_living_entity laser_logo("images/logo/logo_laser.png", sf::Vector2f(0, window.getSize().y - 70), 0.08f);//���� �������
    
    Background fon_1("images/fon_1.png", sf::Vector2f(-10, -800), 1.f, 0.02f);
    Background fon_2("images/fon_1.png", sf::Vector2f(-10, -2480), 1.f, 0.02f);

    Background_Music general_music("music/background/fon_1.ogg");//������� ������
    general_music.play();

    Nebulas additional_fon;//���������� � ����
    additional_fon.add_several(window, 3);

    Stars progress_star;

    Sounds sound_of_blast(Types_of_explosion);//���� ������ �����
    Sounds sound_of_laser(Types_of_laser);//����� ������
    Sounds sound_of_get_sound(Types_of_get_star);//����� ������� ������

    Player hero_1(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));//�����
    Enemy foes;//������ ������

    float COUNTER_1 = 0, COUNTER_2 = 800, COUNTER_3 = 0; //������� ��� ������� ������������ ����� ����� 3 �������
    sf::Clock clock;

    bool Flag_pause = false, Flag_end_game = false;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
        clock.restart(); //������������� �����
        time = time / 800; //�������� ����
        COUNTER_1 += time;//���������� � ����� ���������� time

        sf::Vector2i mousePoz = sf::Mouse::getPosition(window);//������� ���� � ����
        sf::Event event;

        if (Flag_pause) {
            button_1.getButtonStatus(window, event);
            button_2.getButtonStatus(window, event);
            button_3.getButtonStatus(window, event);
        }
        else {
            COUNTER_2 += time;//���������� � ����� ���������� time
            COUNTER_3 += random_float(0.7, 0.1);
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (Flag_pause) {//���� �� �����
                if (event.type == sf::Event::KeyReleased) {//�������� ���� �� ������ ������� 
                    if (event.key.code == sf::Keyboard::Space) {// ��������, ���� �� �������� ������� �������

                        Flag_pause = false;
                        pause_general_music.stop();//������������ ������� ������
                        general_music.play();//���������� ������
                        pause_additional_fon.clear();
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {//���� ������� ����
                    if (event.key.code == sf::Mouse::Left) {//���� ������ ����� ������
                        if (button_1.isPressed) {//���������� ����
                            Flag_pause = false;
                            pause_additional_fon.clear();
                            general_music.play();
                            pause_general_music.stop();//������������ ������� ������
                        }
                        if (button_2.isPressed) {//������ � ������
                            clear_all(hero_1, foes, window, additional_fon, progress_star);
                            pause_additional_fon.clear();
                            pause_general_music.stop();//������������ ������� ������
                            general_music.stop();
                            general_music.play();
                            Flag_pause = false;
                        }
                        if (button_3.isPressed) {//����� � ������� ����
                            clear_all(hero_1, foes, window, additional_fon, progress_star);//������ ��� ������
                            pause_general_music.stop();//������������ ������� ������
                            pause_additional_fon.clear();
                            window.close();
                            menu();//������� ����
                        }
                    }
                }
                if (COUNTER_1 > 2000) {
                    COUNTER_1 = 0;
                    pause_additional_fon.add(window);//�������� ����������
                }
            }
            else {//������� ����
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.key.code == sf::Mouse::Left) {
                        hero_1.add_shot(sf::Vector2f(mousePoz.x, mousePoz.y), sound_of_laser);
                    }
                }
                if (event.type == sf::Event::KeyReleased) {//�������� ���� �� ������ �������
                    if (event.key.code == sf::Keyboard::Space) {// ��������, ���� �� �������� ������� �������
                        Flag_pause = true;
                        general_music.pause();
                        pause_general_music.play();
                    }
                }

                if (COUNTER_1 > 3000) {
                    COUNTER_1 = 0;
                    additional_fon.add(window);//�������� ����������
                }
                if (COUNTER_2 > 4000) {
                    COUNTER_2 = 0;
                    hero_1.add_one_shots();//�������� ��������� ����� ������
                }
                if (COUNTER_3 > 4500) {
                    COUNTER_3 = 0;

                    progress_star.add(window);
                }
            }
        }
        window.clear(background_color);//������ �����

        if (!Flag_god_mode) {//���� ������������ ���������� ������
            if (hero_1.is_died()) {
                general_music.pause();
                if (you_died_menu()) {
                    clear_all(hero_1, foes, window, additional_fon, progress_star);//������ ��� ��������
                    Flag_end_game = false;//���� �������    
                    general_music.stop();//���������� ������
                    general_music.play();//�������� ������� ������
                }
                else {
                    clear_all(hero_1, foes, window, additional_fon, progress_star);//������ ��� ��������
                    window.close();//�������� ����
                    menu();//����� � ����
                }
            }
        }

        if (Flag_pause) {//���� ������ �����?
            pause_background.draw(window);//��� �����
            pause_enemy_logo.draw(window);//������� �����

            pause_additional_fon.draw(window);//����������

            button_1.draw(window);
            button_2.draw(window);
            button_3.draw(window);
        }
        else {
            hero_1.change_the_position(sf::Vector2f(mousePoz.x, mousePoz.y));
            the_number_of_dead.setString(std::to_wstring(hero_1.get_killed_enemies()));//����� ���������� ������ ������
            the_number_of_stars.setString(std::to_wstring(hero_1.get_stars()));//����� ���������� ��������� �����
            check_mob_hit(hero_1, foes, sound_of_blast);//�������� ������������
            hero_1.tracking_mobs_lives(window);//������ �������� �� ������� ������ ������
            foes.add_all_possible_enemies(window);//�������������� ���������� ������ �� ������������� ����������
            check_player_stars(progress_star, hero_1, time, sound_of_get_sound);//�������� - ������� ������?

            fon_1.cyclic_image(window, -2460);//���������� ���
            fon_2.cyclic_image(window, -2460);//���������� ���

            fon_1.Do_I_need_to_draw(window);//��� �����?
            fon_2.Do_I_need_to_draw(window);//��� �����?

            additional_fon.draw(window);//���������� - ���������

            foes.draw(window);//������ �������� �� ������� ������ ������ - ���������
            hero_1.draw_all_shots(window);//��� ������� - ���������
            hero_1.draw(window);//������� ������ �� ����� �����
            
            progress_star.draw(window);//��������� �����
            
            current_health(hero_1, window, health_now);//������� �������� - ���������
            current_laser(hero_1, window, laser_logo);//������� ���������� �������� �������
            meteorite_kill.draw(window);//������ ����� - ������ - ���������
            star_logo.draw(window);//��������� ������ - ���� - ���������

            window.draw(the_number_of_dead);//������ ����� - �� ���������� - ���������
            window.draw(the_number_of_stars);//������ ������ - �� ���������� - ���������
        }
        window.display();
    }
}