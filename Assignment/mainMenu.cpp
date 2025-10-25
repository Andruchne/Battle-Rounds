#include "mainMenu.hpp"

MainMenu::MainMenu(std::string identifier, sf::Font& font, sf::Color& color, sf::Sound& buttonSound,
    SceneHandler& handler, Character& mage, Character& warrior, Character& ranger, sf::RenderWindow& window, Scene& scene) : GameObject(identifier)
{
    startButton = new Button("startButton", font, "Start", sf::Vector2f(300.0f, 100.0f), color, buttonSound);
    startButton->setPosition(sf::Vector2f(500.0f, 200.0f));
    startButton->SetButtonAction([&handler, &mage, &warrior, &ranger]() {
        handler.stackScene("charSelect");
        // Set position for characterSelection...
        mage.setPosition(sf::Vector2f(320.0f, 140.0f));
        ranger.setPosition(sf::Vector2f(350.0f, 155.0f));
        warrior.setPosition(sf::Vector2f(200.0f, -15.0f));
    });

    scoreboardButton = new Button("scoreboardButton", font, "Scoreboard", sf::Vector2f(300.0f, 100.0f), color, buttonSound);
    scoreboardButton->setPosition(sf::Vector2f(500.0f, 330.0f));
    scoreboardButton->SetButtonAction([&handler]() {
        handler.stackScene("scoreBoard");
    });


    exitButton = new Button("exitButton", font, "Exit", sf::Vector2f(300.0f, 100.0f), color, buttonSound);
    exitButton->setPosition(sf::Vector2f(500.0f, 460.0f));
    exitButton->SetButtonAction([&window]() { window.close(); });

    scene.addGameObject(startButton);
    scene.addGameObject(scoreboardButton);
    scene.addGameObject(exitButton);
}

MainMenu::~MainMenu()
{
    delete startButton;
    delete scoreboardButton;
    delete exitButton;
}

void MainMenu::update() { }