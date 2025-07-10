#pragma once

#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

const sf::Color defaultHovered = sf::Color(83, 130, 221);//цвет кнопки
const sf::Color defaultPressed = sf::Color(51, 49, 173);//цвет кнопки если она нажата

class Button{
public:
    virtual void getButtonStatus(sf::RenderWindow&, sf::Event&) = 0;//статус кнопки
    virtual void draw(sf::RenderWindow&) = 0;//отображение кнопки
    virtual void setButtonFont(sf::Font&);//шрифт текста на кнопке
    virtual void setButtonLable(std::wstring, const sf::Color&, float) = 0;//установка надписи на кнопке

    bool isHover = false;//курсор наведен?
    bool isPressed = false;//нажата или нет
    bool isActive = true;//состояние кнопки

protected:
    sf::Text buttonLabel;//буквы на кнопке
    sf::Vector2i mousePosWindow;//позиция мыши
    sf::Vector2f mousePosView;
    sf::Vector2f buttonPos;//позиция кнопки
    sf::FloatRect labelRect;
    std::wstring label;//надпись
};

class RectButton : public Button{//подкласс прямоугольных кнопок
public:
    RectButton(const sf::Vector2f = sf::Vector2f(0, 0));//конструкторы
    RectButton(const sf::Vector2f = sf::Vector2f(0, 0), const sf::Vector2f = sf::Vector2f(0, 0));
    ~RectButton();//деструктор

    void getButtonStatus(sf::RenderWindow&, sf::Event&);//статус кнопки (нажата/не нажата)
    void draw(sf::RenderWindow&);//отображение кнопки
    void setButtonLable(std::wstring, const sf::Color&, float);//отображение надписи
    sf::RectangleShape button;

private:
    sf::FloatRect buttonRect;
};
#endif