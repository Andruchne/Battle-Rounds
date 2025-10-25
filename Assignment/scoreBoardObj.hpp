#pragma once

#include "button.hpp"
#include "box.hpp"
#include "sceneHandler.hpp"
#include "scoreBoard.hpp"
#include "scene.hpp"

class ScoreBoardObj : public GameObject
{
	private:
        Box* scoreBox;
        Button* scoreBackButton;
        Button* eraseScoreButton;

	public:
        ScoreBoardObj(std::string identifier, sf::Font& font, sf::Color& color, sf::Sound& buttonSound, ScoreBoard& scoreboard, SceneHandler& handler, Scene& scene);
		~ScoreBoardObj();

		void update();
};