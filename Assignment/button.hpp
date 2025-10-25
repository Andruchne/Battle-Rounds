#pragma once

#include "box.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <functional>

// typedef std::function<void()> buttonAction;

class Button : public Box {

    private:
        // buttonAction action;
        std::function<void()> action;
        std::function<void()> hover;
        sf::Sound& buttonSound;
        sf::SoundBuffer soundEffects;
        bool doOnce;

    public:
        Button(std::string identifier, sf::Font& font, std::string buttonText, sf::Vector2f size, sf::Color color, sf::Sound& buttonSound);
        ~Button();

        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
        void onClick();
        void onHover();
        void update() override;

        // void setButtonAction(buttonAction action);
        void SetButtonAction(std::function<void()> action);
        void SetButtonHover(std::function<void()> hover);
};

