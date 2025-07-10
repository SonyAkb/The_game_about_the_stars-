#include "sfml_button.hpp"

RectButton::RectButton(const sf::Vector2f size){//конструктор
    this->button.setSize(size);
    this->buttonRect = this->button.getLocalBounds();
}

RectButton::RectButton(const sf::Vector2f size, const sf::Vector2f position){//конструктор
    this->button.setSize(size);
    this->button.setPosition(position);
    this->buttonPos = position;
    this->buttonRect = this->button.getLocalBounds();
}

RectButton::~RectButton(){}//Деструктор

void RectButton::getButtonStatus(sf::RenderWindow& window, sf::Event& event)//статус
{
    this->mousePosWindow = sf::Mouse::getPosition(window);//позиция мыши в окне
    this->mousePosView = window.mapPixelToCoords(this->mousePosWindow);

    this->isHover = false;//курсор наведен?
    this->isPressed = false;//нажато?

    if (isActive){//если кнопка актива
        if (button.getGlobalBounds().contains(this->mousePosView)){//курсор наведен
            this->isHover = true;
        }
        if (button.getGlobalBounds().contains(this->mousePosView)){//после 1 нажатия кнопки
            this->isPressed = true; //состояние меняется на активное - кнопка нажата
        }

        if (isHover){//курсор наведен
            button.setFillColor(defaultPressed);//меняю цвет при наведении
        }
        else button.setFillColor(defaultHovered);//обычный цвет

        if (isPressed){//кнопка нажата
            button.setFillColor(defaultPressed);//возвращаю истинный цвет
        }
    }
    else{//обычный цвет
        button.setFillColor(defaultPressed);
    }
}

void RectButton::draw(sf::RenderWindow& window){ //отображаю кнопку в окне
    window.draw(button);//кнопка
    window.draw(buttonLabel);//надпись
}

void RectButton::setButtonLable(std::wstring label, const sf::Color& color, float charSize){//устанавливаю надпись
    this->buttonLabel.setString(label);//надпись
    this->buttonLabel.setCharacterSize(charSize);//размер символов
    this->buttonLabel.setFillColor(color);//устанавливаю цвет
    this->label = label;//присваиваю надпись

    this->labelRect = this->buttonLabel.getLocalBounds();
    this->buttonLabel.setOrigin(this->labelRect.width / 2.0f, this->labelRect.height / 2.0f);//ставлю координаты

    this->buttonLabel.setPosition(this->buttonPos.x + (this->buttonRect.width / 2.0f),//ставлю координаты
        this->buttonPos.y + (this->buttonRect.height / 4.0f) + 7);
}
