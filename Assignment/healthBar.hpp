#pragma once

#include "spriteObject.hpp"
#include "gameObject.hpp"
#include "character.hpp"

class HealthBar : public GameObject
{
	private:
		SpriteObject* container;
		SpriteObject* healthBar;
		sf::Vector2f healthBarOffset;
		sf::Vector2f currentScale;
		sf::Vector2f currentPos;
		Character* character;

	public:
		HealthBar(std::string identifier, Character& character);
		~HealthBar();

		void update() override;
		void render(sf::RenderWindow& window) override;

		void SetPosition(sf::Vector2f pos);
		void SetScale(sf::Vector2f scale);
		void SetCharacter(Character& character);

		float Lerp(float a, float b, float c);
};

