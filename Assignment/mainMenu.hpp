#pragma once

#include "button.hpp"
#include "box.hpp"
#include "sceneHandler.hpp"
#include "character.hpp"
#include "scene.hpp"

class MainMenu : public GameObject
{
    private:
        Button* startButton;
        Button* scoreboardButton;
        Button* exitButton;

	public:
		MainMenu(std::string identifier, sf::Font& font, sf::Color& color, sf::Sound& buttonSound, 
            SceneHandler& handler, Character& mage, Character& warrior, Character& ranger, sf::RenderWindow& window, Scene& scene);
		~MainMenu();

        void update() override;
};