#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "gameObject.hpp"
#include <functional>

class TextObject : public GameObject {
    private:
        sf::Font& font;
        sf::Text text;
        std::string textStr;
        sf::Vector2f position;
        std::function<void()> updateText;
        
    public:
        TextObject(std::string identifier, sf::Font& font, std::string textStr);
        ~TextObject();
    
        void update() override;
        void render(sf::RenderWindow& window) override;

        std::string getTextStr() const;
        void setText(const std::string textStr);
        void setCharacterSize(const int size);
        void setFillColor(const sf::Color color);
        void setPosition(const sf::Vector2f position);
        void setUpdateText(std::function<void()> action);
};


