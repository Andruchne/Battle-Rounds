#include "charSelect.hpp"

CharSelect::CharSelect(std::string identifier, sf::Font& font, sf::Sound& buttonSound, sf::Music& music, BattleManager& battleManager,
    Character& mage, Character& ranger, Character& warrior, SceneHandler& handler, Scene& scene, Scene& battle) : GameObject(identifier)
{
    signHP = new Box("HPSign", font, "", sf::Vector2f(300.0f, 75.0f), sf::Color::White);
    signHP->setPosition(sf::Vector2f(100.0f, 75.0f));

    signAttack = new Box("AttackSign", font, "", sf::Vector2f(300.0f, 75.0f), sf::Color::White);
    signAttack->setPosition(sf::Vector2f(500.0f, 75.0f));

    signDefense = new Box("DefenseSign", font, "", sf::Vector2f(300.0f, 75.0f), sf::Color::White);
    signDefense->setPosition(sf::Vector2f(900.0f, 75.0f));

    mageButton = new Button("mageButton", font, "Mage", sf::Vector2f(300.0f, 100.0f), sf::Color::Magenta, buttonSound);
    mageButton->setPosition(sf::Vector2f(110.0f, 600.0f));
    // Hover...
    mageButton->SetButtonHover([&scene, &mage, &ranger, &warrior, this]() {
        // Update visuals...
        scene.removeGameObject(&ranger);
        scene.removeGameObject(&warrior);
        scene.addGameObject(&mage);

        scene.addGameObject(this->signHP);
        scene.addGameObject(this->signAttack);
        scene.addGameObject(this->signDefense);

        this->signHP->SetUpdateText([this, &mage]() {
            this->signHP->SetText("HP: " + std::to_string(mage.getHP()));
        });
        this->signAttack->SetUpdateText([this, &mage]() {
            this->signAttack->SetText("Attack: " + std::to_string(mage.getAttack()));
        });
        this->signDefense->SetUpdateText([this, &mage]() {
            this->signDefense->SetText("Defense: " + std::to_string(mage.getDefense()));
        });
    });

    mageButton->SetButtonAction([&battleManager, &mage, &handler, &battle, &music]() {
        battleManager.SetPlayerCharacter(mage);
        handler.stackScene("battle");
        battle.addGameObject(&mage);
        // Set position for fight...
        mage.setPosition(sf::Vector2f(50.0f, 160.0f));
        music.openFromFile("Sounds/Music/Battle_Music.mp3");
        music.play();
    });

    rangerButton = new Button("rangerButton", font, "Ranger", sf::Vector2f(300.0f, 100.0f), sf::Color(0, 153, 51, 255), buttonSound);
    rangerButton->setPosition(sf::Vector2f(490.0f, 600.0f));
    // Hover...
    rangerButton->SetButtonHover([&scene, &mage, &ranger, &warrior, this]() {
        // Update visuals...
        scene.removeGameObject(&warrior);
        scene.removeGameObject(&mage);
        scene.addGameObject(&ranger);

        scene.addGameObject(this->signHP);
        scene.addGameObject(this->signAttack);
        scene.addGameObject(this->signDefense);

        this->signHP->SetUpdateText([this, &ranger]() {
            signHP->SetText("HP: " + std::to_string(ranger.getHP()));
        });
        this->signAttack->SetUpdateText([this, &ranger]() {
            this->signAttack->SetText("Attack: " + std::to_string(ranger.getAttack()));
        });
        this->signDefense->SetUpdateText([this, &ranger]() {
            this->signDefense->SetText("Defense: " + std::to_string(ranger.getDefense()));
        });
    });

    rangerButton->SetButtonAction([&battleManager, &ranger, &handler, &battle, &music]() {
        battleManager.SetPlayerCharacter(ranger);
        handler.stackScene("battle");
        battle.addGameObject(&ranger);
        // Set position for fight...
        ranger.setPosition(sf::Vector2f(80.0f, 175.0f));
        music.openFromFile("Sounds/Music/Battle_Music.mp3");
        music.play();
    });

    warriorButton = new Button("warriorButton", font, "Warrior", sf::Vector2f(300.0f, 100.0f), sf::Color::Red, buttonSound);
    warriorButton->setPosition(sf::Vector2f(870.0f, 600.0f));
    // Hover...
    warriorButton->SetButtonHover([&scene, &mage, &ranger, &warrior, this]() {
        // Update visuals...
        scene.removeGameObject(&ranger);
        scene.removeGameObject(&mage);
        scene.addGameObject(&warrior);

        scene.addGameObject(this->signHP);
        scene.addGameObject(this->signAttack);
        scene.addGameObject(this->signDefense);

        this->signHP->SetUpdateText([this, &warrior]() {
            this->signHP->SetText("HP: " + std::to_string(warrior.getHP()));
        });
        this->signAttack->SetUpdateText([this, &warrior]() {
            this->signAttack->SetText("Attack: " + std::to_string(warrior.getAttack()));
        });
        this->signDefense->SetUpdateText([this, &warrior]() {
            this->signDefense->SetText("Defense: " + std::to_string(warrior.getDefense()));
        });
    });

    warriorButton->SetButtonAction([&battleManager, &warrior, &handler, &battle, &music]() {
        battleManager.SetPlayerCharacter(warrior);
        handler.stackScene("battle");
        battle.addGameObject(&warrior);
        // Set position for fight...
        warrior.setPosition(sf::Vector2f(-70.0f, 5.0f));
        music.openFromFile("Sounds/Music/Battle_Music.mp3");
        music.play();
        });

    scene.addGameObject(mageButton);
    scene.addGameObject(rangerButton);
    scene.addGameObject(warriorButton);
}

CharSelect::~CharSelect()
{
    delete signHP;
    delete signAttack;
    delete signDefense;

    delete mageButton;
    delete rangerButton;
    delete warriorButton;
}

void CharSelect::update() { }