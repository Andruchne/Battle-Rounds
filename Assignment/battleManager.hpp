#pragma once

#include <SFML/Audio.hpp>

#include <fstream>
#include <iostream>

#include "gameObject.hpp"
#include "scene.hpp"
#include "character.hpp"
#include "healthBar.hpp"
#include "spriteInfo.hpp"
#include "button.hpp"
#include "hoverText.hpp"
#include "sceneHandler.hpp"
#include "scoreBoard.hpp"

class BattleManager : public GameObject
{
	private:
		std::string playerName;
		ScoreBoard& scoreBoard;
		sf::Music& music;
		sf::Sound& buttonSound;

		sf::Sound enemySound;
		sf::SoundBuffer soundEffects;

		int score;
		SceneHandler handler;

		bool resigned;
		bool enemyDied;
		bool playerDied;
		bool enemySkipped;
		sf::Clock clock;
		float sceneChangeInterval;
		float turnInterval;

		bool buttonsActive;

		int currentStage;
		sf::RenderWindow* window;

		Character* enemies[4];
		int defaultHPEnemies[4];
		int defaultAttackEnemies[4];
		int defaultDefenseEnemies[4];
		float enemyHealthMultiplier;
		int attackIncrease;
		int defenseIncrease;

		Scene* battleScene;
		Character* playerCharacter;

		HealthBar* playerHealth;
		HealthBar* enemyHealth;

		Button* attackButton;
		Button* healButton;
		Button* resignButton;
		Button* nextBattleButton;

		HoverText* playerText;
		HoverText* enemyText;

		Box* backgroundBox;

		Box* healthStat;
		Button* healthPlus;
		Button* healthMinus;

		Box* attackStat;
		Button* attackPlus;
		Button* attackMinus;

		Box* defenseStat;
		Button* defensePlus;
		Button* defenseMinus;

		Box* scoreBox;
		Button* exitButton;

		std::vector<std::string> textAreaText;
		Box* textArea;
		Button* toggleTextArea;
		bool textAreaVisible;

		bool playersTurn;

		int damageToEnemy;
		int damageToPlayer;
		int healPlayerAmount;

		void SetScenery();
		void ActionButton();
		void HealButton();
		void ResignButton();
		void NextBattleButton();

		void ToggleButtons();
		void UpdateScenery();
		void UpdateTurns();

		void AddTextInfo(std::string info);

	public:
		BattleManager(std::string identifier, Scene* scene, Character* playerCharacter, sf::RenderWindow& window, SceneHandler& handler,
			ScoreBoard& scoreBoard, sf::Music& music, sf::Sound& buttonSound, std::string playerName, sf::Font& font, sf::Color& buttonFontColor);
		~BattleManager();

		void update() override;

		void SetPlayerCharacter(Character& playerCharacter);
		void ResetManager();

		Character& GetCurrentEnemy() const;
};

