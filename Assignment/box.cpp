#include "box.hpp"

Box::Box(std::string identifier, sf::Font& font, std::string boardText, sf::Vector2f size, sf::Color color, std::string spriteFile) :
    GameObject(identifier), font(font), boxText(boardText)
{
    this->size = size;
    this->color = color;

    this->texture.loadFromFile(spriteFile);
    this->sprite.setTexture(this->texture);
    sprite.setScale(sf::Vector2f(size.x / texture.getSize().x, size.y / texture.getSize().y));

    this->text.setFont(font);
    this->text.setString(boardText);
    this->text.setCharacterSize(26);
    this->text.setFillColor(color);

    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.25f);

    this->setPosition(sf::Vector2f(0.0f, 0.0f));
}

Box::Box(std::string identifier, sf::Font& font, std::string boardText, sf::Vector2f size, sf::Color color) :
    GameObject(identifier), font(font), boxText(boardText)
{
    this->size = size;
    this->color = color;

    this->texture.loadFromFile("Sprites/Components/sign.png");
    this->sprite.setTexture(this->texture);
    sprite.setScale(sf::Vector2f(size.x / texture.getSize().x, size.y / texture.getSize().y));

    this->text.setFont(font);
    this->text.setString(boardText);
    this->text.setCharacterSize(26);
    this->text.setFillColor(color);

    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.5f);

    this->setPosition(sf::Vector2f(0.0f, 0.0f));
}

Box::~Box() { }

void Box::render(sf::RenderWindow& window) {
    window.draw(this->sprite);
    window.draw(this->text);
}

void Box::update() {
    if (updateText != NULL){
        this->updateText();
    }
}

void Box::setCharacterSize(const int size) {
    this->text.setCharacterSize(size);
    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.5f);
}

void Box::setPosition(const sf::Vector2f position) {
    this->sprite.setPosition(position);
    sf::Vector2f centerButton(position.x + (size.x / 2.0f), position.y + (size.y / 2.0f));
    this->text.setPosition(centerButton);
}

void Box::SetUpdateText(std::function<void()> updateText){
    this->updateText = updateText;
}

void Box::SetText(std::string text){
    this->boxText = text;
    this->text.setString(text);
    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.5f);
}

void Box::SetColor(sf::Color color){
    this->color = color;
    this->text.setFillColor(color);
}