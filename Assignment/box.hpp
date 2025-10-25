#pragma once

#include "gameObject.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <functional>

class Box : public GameObject
{
    protected:
        sf::Text text;
        sf::Font& font;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f size;
        sf::Color color;

        std::string boxText;
        std::function<void()> updateText;

    public:
        Box(std::string identifier, sf::Font& font, std::string boardText,
            sf::Vector2f size, sf::Color color, std::string spriteFile);
        Box(std::string identifier, sf::Font& font, std::string boardText,
            sf::Vector2f size, sf::Color color);
        ~Box();
        virtual void render(sf::RenderWindow& window) override;
        virtual void update() override;

        void setCharacterSize(const int size);
        void setPosition(const sf::Vector2f position);

        void SetUpdateText(std::function<void()> updateText);
        void SetText(std::string text);
        void SetColor(sf::Color color);
};
