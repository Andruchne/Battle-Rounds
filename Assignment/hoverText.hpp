#pragma once

#include "gameObject.hpp"

class HoverText : public GameObject
{
	private:
		bool active;
		sf::Vector2f startPos;

		sf::Clock clock;
		sf::Text text;
		float lastCurveValue;
		float currentAlpha;

		// Time in milliseconds
		float currentTime;
		float totalTime;

		void ResetText();
		void Tween();
		float GetCurveValue(float t);

	public:
		HoverText(std::string identifier, sf::Font& font, std::string text, int size, sf::Color color, sf::Vector2f startPos);
		~HoverText();

		void update() override;
		void render(sf::RenderWindow& window) override;

		void Reactivate();
		void SetText(std::string text);
		void SetColor(sf::Color color);
};

