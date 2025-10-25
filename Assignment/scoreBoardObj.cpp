#include "scoreBoardObj.hpp"

ScoreBoardObj::ScoreBoardObj(std::string identifier, sf::Font& font, sf::Color& color, sf::Sound& buttonSound, ScoreBoard& scoreboard, SceneHandler& handler, Scene& scene) :
    GameObject(identifier)
{
    scoreBox = new Box("backgroundBox", font, "", sf::Vector2f(540, 620), sf::Color::White);
    scoreBox->setPosition(sf::Vector2f(380.0f, 50.0f));
    scoreBox->setCharacterSize(40);
    scoreBox->SetUpdateText([&scoreboard, this]() {
        this->scoreBox->SetText(scoreboard.GetScores() + "\n");
    });

    scoreBackButton = new Button("scoreBackbutton", font, "Back", sf::Vector2f(200.0f, 80.0f), color, buttonSound);
    scoreBackButton->setPosition(sf::Vector2f(550.0f, 575.0f));
    scoreBackButton->SetButtonAction([&handler]() {
        handler.popScene();
    });

    eraseScoreButton = new Button("eraseButton", font, "Erase", sf::Vector2f(200.0f, 80.0f), color, buttonSound);
    eraseScoreButton->setPosition(sf::Vector2f(50.0f, 600.0f));
    eraseScoreButton->SetButtonAction([&scoreboard]() {
        scoreboard.CreateEmptyScores();
    });

    scene.addGameObject(scoreBox);
    scene.addGameObject(scoreBackButton);
    scene.addGameObject(eraseScoreButton);
}

ScoreBoardObj::~ScoreBoardObj()
{
    delete scoreBox;
    delete scoreBackButton;
    delete eraseScoreButton;
}

void ScoreBoardObj::update() {}