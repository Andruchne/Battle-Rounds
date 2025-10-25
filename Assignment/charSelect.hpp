#pragma once

#include "box.hpp"
#include "button.hpp"
#include "scene.hpp"
#include "character.hpp"
#include "sceneHandler.hpp"
#include "battleManager.hpp"

class CharSelect : GameObject
{
    private:
        Box* signHP;
        Box* signAttack;
        Box* signDefense;

        Button* mageButton;
        Button* rangerButton;
        Button* warriorButton;

    public:
        CharSelect(std::string identifier, sf::Font& font, sf::Sound& buttonSound, sf::Music& music, BattleManager& battleManager,
            Character& mage, Character& ranger, Character& warrior, SceneHandler& handler, Scene& scene, Scene& battle);
        ~CharSelect();

        void update() override;
};