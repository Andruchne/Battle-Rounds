#include "button.hpp"

Button::Button(std::string identifier, sf::Font& font, std::string buttonText, sf::Vector2f size, sf::Color color, sf::Sound& buttonSound) : 
    Box(identifier, font, buttonText, size, color, "Sprites/Components/button.png"), buttonSound(buttonSound)
{
    doOnce = false;
}

Button::~Button() { }

void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f position = sprite.getPosition();

    if(event.type == sf::Event::MouseButtonPressed  && 
        event.mouseButton.button == sf::Mouse::Button::Left) {

        if(mousePosition.x >= position.x && mousePosition.x <= position.x + size.x && 
            mousePosition.y >= position.y && mousePosition.y <= position.y + size.y) {
            this->onClick();
        }
    }

    if (event.type == sf::Event::MouseMoved)
    {
        if (mousePosition.x >= position.x && mousePosition.x <= position.x + size.x &&
            mousePosition.y >= position.y && mousePosition.y <= position.y + size.y) 
        {
            if (!doOnce)
            {
                this->text.setFillColor(sf::Color::White);
                this->onHover();
                soundEffects.loadFromFile("Sounds/SFX/Button/Hover.mp3");
                buttonSound.setBuffer(soundEffects);
                buttonSound.play();
                doOnce = true;
            }
        }
        else if (text.getFillColor() != color) 
        {
            this->text.setFillColor(color);
            if (doOnce) doOnce = false;
        }
    }
}

void Button::update() {
    Box::update();
}

void Button::onClick() {
    if(action != NULL)
    this->action();
}

void Button::onHover() {
    if (hover != NULL)
    this->hover();
}

void Button::SetButtonAction(std::function<void()> action) {
    this->action = action;
}

void Button::SetButtonHover(std::function<void()> hover) {
    this->hover = hover;
}