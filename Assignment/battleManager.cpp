#include "battleManager.hpp"


BattleManager::BattleManager(std::string identifier, Scene* scene, Character* playerCharacter, sf::RenderWindow& window, SceneHandler& handler,
	ScoreBoard& scoreBoard, sf::Music& music, sf::Sound& buttonSound, std::string playerName, sf::Font& font, sf::Color& buttonFontColor) :
	GameObject(identifier), scoreBoard(scoreBoard), music(music), buttonSound(buttonSound)
{
	enemySound.setVolume(15.0f);

	score = 0;
	this->handler = handler;
	this->playerName = playerName;
	this->scoreBoard = scoreBoard;

	healPlayerAmount = -1;
	enemySkipped = false;
	currentStage = 0;
	enemyHealthMultiplier = 1;
	attackIncrease = 0;
	defenseIncrease = 0;
	this->window = &window;
	this->battleScene = scene;
	this->playerCharacter = playerCharacter;
	damageToPlayer = -1;
	damageToEnemy = -1;
	playersTurn = true;
	resigned = false;
	sceneChangeInterval = 2.5f;
	turnInterval = 1.0f;
	buttonsActive = true;
	textAreaVisible = false;

	// Setup enemies...
	
	// Flying eye
	defaultHPEnemies[0] = 5;
	defaultAttackEnemies[0] = 3;
	defaultDefenseEnemies[0] = 2;
	enemies[0] = new Character("Flying Eye", "Sprites/Monsters/FlyingEye/eyeIdle.png", 8, 1, defaultHPEnemies[0], defaultAttackEnemies[0], defaultDefenseEnemies[0], enemySound);
	enemies[0]->AddAnimationSprite(State::Attack, "Sprites/Monsters/FlyingEye/eyeAttack.png", 8, 1, "Sounds/SFX/Enemy/Flying_Eye/eye_attack.wav");
	enemies[0]->AddAnimationSprite(State::Hit, "Sprites/Monsters/FlyingEye/eyeHit.png", 4, 1, "Sounds/SFX/Enemy/Flying_Eye/eye_hit.wav");
	enemies[0]->AddAnimationSprite(State::Death, "Sprites/Monsters/FlyingEye/eyeDeath.png", 4, 1, "Sounds/SFX/Enemy/Flying_Eye/eye_death.wav");

	// Mushroom
	defaultHPEnemies[1] = 6;
	defaultAttackEnemies[1] = 2;
	defaultDefenseEnemies[1] = 2;
	enemies[1] = new Character("Mushroom", "Sprites/Monsters/Mushroom/shroomIdle.png", 4, 1, defaultHPEnemies[1], defaultAttackEnemies[1], defaultDefenseEnemies[1], enemySound);
	enemies[1]->AddAnimationSprite(State::Attack, "Sprites/Monsters/Mushroom/shroomAttack.png", 8, 1, "Sounds/SFX/Enemy/Mushroom/shroom_attack.wav");
	enemies[1]->AddAnimationSprite(State::Hit, "Sprites/Monsters/Mushroom/shroomHit.png", 4, 1, "Sounds/SFX/Enemy/Mushroom/shroom_hit.wav");
	enemies[1]->AddAnimationSprite(State::Death, "Sprites/Monsters/Mushroom/shroomDeath.png", 4, 1, "Sounds/SFX/Enemy/Mushroom/shroom_death.wav");

	// Goblin
	defaultHPEnemies[2] = 8;
	defaultAttackEnemies[2] = 3;
	defaultDefenseEnemies[2] = 2;
	enemies[2] = new Character("Goblin", "Sprites/Monsters/Goblin/goblinIdle.png", 4, 1, defaultHPEnemies[2], defaultAttackEnemies[2], defaultDefenseEnemies[2], enemySound);
	enemies[2]->AddAnimationSprite(State::Attack, "Sprites/Monsters/Goblin/goblinAttack.png", 8, 1, "Sounds/SFX/Enemy/Goblin/goblin_attack.wav");
	enemies[2]->AddAnimationSprite(State::Hit, "Sprites/Monsters/Goblin/goblinHit.png", 4, 1, "Sounds/SFX/Enemy/Goblin/goblin_hit.wav");
	enemies[2]->AddAnimationSprite(State::Death, "Sprites/Monsters/Goblin/goblinDeath.png", 4, 1, "Sounds/SFX/Enemy/Goblin/goblin_death.wav");

	// Skeleton
	defaultHPEnemies[3] = 10;
	defaultAttackEnemies[3] = 5;
	defaultDefenseEnemies[3] = 3;
	enemies[3] = new Character("Skeleton", "Sprites/Monsters/Skeleton/skeletonIdle.png", 4, 1, defaultHPEnemies[3], defaultAttackEnemies[3], defaultDefenseEnemies[3], enemySound);
	enemies[3]->AddAnimationSprite(State::Attack, "Sprites/Monsters/Skeleton/skeletonAttack.png", 8, 1, "Sounds/SFX/Enemy/Skeleton/skeleton_attack.wav");
	enemies[3]->AddAnimationSprite(State::Hit, "Sprites/Monsters/Skeleton/skeletonHit.png", 4, 1, "Sounds/SFX/Enemy/Skeleton/skeleton_hit.wav");
	enemies[3]->AddAnimationSprite(State::Death, "Sprites/Monsters/Skeleton/skeletonDeath.png", 4, 1, "Sounds/SFX/Enemy/Skeleton/skeleton_death.wav");

	for (int i = 0; i < 4; i++)
	{
		enemies[i]->setScale(sf::Vector2f(5.0f, 5.0f));
		enemies[i]->mirrorHorizontal();
		enemies[i]->setPosition(sf::Vector2f(1250.0f, -100.0f));
		enemies[i]->SetFramesPerSecond(8);
	}

	// Health bars...

	playerHealth = new HealthBar("playerHealth", *playerCharacter);
	playerHealth->SetPosition(sf::Vector2f(250.0f, 250.0f));
	playerHealth->SetScale(sf::Vector2f(3.0f, 3.0f));

	enemyHealth = new HealthBar("enemyHealth", *enemies[0]);
	enemyHealth->SetPosition(sf::Vector2f(725.0f, 150.0f));
	enemyHealth->SetScale(sf::Vector2f(3.0f, 3.0f));

	battleScene->addGameObject(playerHealth);
	battleScene->addGameObject(enemyHealth);

	// Buttons for actions...

	attackButton = new Button("attackButton", font, "Attack", sf::Vector2f(200.0f, 100.0f), buttonFontColor, buttonSound);
	attackButton->setPosition(sf::Vector2f(600.0f, 600.0f));
	attackButton->SetButtonAction([this]() {
		this->ActionButton();
	});

	healButton = new Button("healButton", font, "Heal", sf::Vector2f(200.0f, 100.0f), buttonFontColor, buttonSound);
	healButton->setPosition(sf::Vector2f(820.0f, 600.0f));
	healButton->SetButtonAction([this]() {
		this->HealButton();
	});

	resignButton = new Button("resignButton", font, "Yield", sf::Vector2f(200.0f, 100.0f), buttonFontColor, buttonSound);
	resignButton->setPosition(sf::Vector2f(1040.0f, 600.0f));
	resignButton->SetButtonAction([this]() {
		this->ResignButton();
	});

	battleScene->addGameObject(attackButton);
	battleScene->addGameObject(healButton);
	battleScene->addGameObject(resignButton);

	// Hover texts for action display...
	playerText = new HoverText("playerText", font, "", 35, sf::Color::Red, sf::Vector2f(500.0f, 450.0f));
	enemyText = new HoverText("enemyText", font, "", 35, sf::Color::Red, sf::Vector2f(1000.0f, 300.0f));

	battleScene->addGameObject(playerText);
	battleScene->addGameObject(enemyText);

	// Text area for displaying info...
	textArea = new Box("textArea", font, "", sf::Vector2f(600.0f, 200.0f), sf::Color::White);
	textArea->setPosition(sf::Vector2f(10.0f, 10.0f));
	textArea->setCharacterSize(15);

	toggleTextArea = new Button("toggleTextArea", font, "Info", sf::Vector2f(150.0f, 80.0f), buttonFontColor, buttonSound);
	toggleTextArea->setPosition(sf::Vector2f(75.0f, 610.0f));
	toggleTextArea->SetButtonAction([this]() {
		if (!textAreaVisible) {
			this->battleScene->addGameObject(this->textArea);
			textAreaVisible = true;
		}
		else {
			this->battleScene->removeGameObject(this->textArea);
			textAreaVisible = false;
		}
	});

	battleScene->addGameObject(toggleTextArea);

	// Background for upgrade and game over screen...
	backgroundBox = new Box("backgroundBox", font, "", sf::Vector2f(1080, 620), sf::Color::Red);
	backgroundBox->setPosition(sf::Vector2f(100.0f, 50.0f));

	// Components for upgrade screen...
	nextBattleButton = new Button("nextBattleButton", font, "Next", sf::Vector2f(200.0f, 80.0f), buttonFontColor, buttonSound);
	nextBattleButton->setPosition(sf::Vector2f(775.0f, 500.0f));
	nextBattleButton->SetButtonAction([this]() {
		this->NextBattleButton();
		battleScene->addGameObject(toggleTextArea);
		if (textAreaVisible)battleScene->addGameObject(textArea);
	});

	healthStat = new Box("healthInfo", font, "", sf::Vector2f(250.0f, 80.0f), sf::Color::White);
	healthStat->setPosition(sf::Vector2f(750.0f, 180.0f));
	healthStat->setCharacterSize(30);
	healthPlus = new Button("healthPlus", font, "+", sf::Vector2f(70.0f, 70.0f), buttonFontColor, buttonSound);
	healthPlus->setPosition(sf::Vector2f(1020.0f, 184.0f));
	healthPlus->setCharacterSize(30);
	healthPlus->SetButtonAction([scene, this]() {
		scene->removeGameObject(this->healthPlus);
		scene->removeGameObject(this->attackPlus);
		scene->removeGameObject(this->defensePlus);
		scene->addGameObject(this->healthMinus);
		this->playerCharacter->setHP(this->playerCharacter->getHP() + 3);
		this->playerCharacter->setMaxHP(this->playerCharacter->getMaxHP() + 3);
		this->healthStat->SetText("Health: " + std::to_string(this->playerCharacter->getMaxHP()));
		this->healthStat->SetColor(sf::Color::Green);
		scene->addGameObject(this->nextBattleButton);
	});
	healthMinus = new Button("healthMinus", font, "-", sf::Vector2f(70.0f, 70.0f), buttonFontColor, buttonSound);
	healthMinus->setPosition(sf::Vector2f(660.0f, 184.0f));
	healthMinus->setCharacterSize(30);
	healthMinus->SetButtonAction([scene, this]() {
		scene->addGameObject(this->healthPlus);
		scene->addGameObject(this->attackPlus);
		scene->addGameObject(this->defensePlus);
		scene->removeGameObject(this->healthMinus);
		this->playerCharacter->setHP(this->playerCharacter->getHP() - 3);
		this->playerCharacter->setMaxHP(this->playerCharacter->getMaxHP() - 3);
		this->healthStat->SetText("Health: " + std::to_string(this->playerCharacter->getMaxHP()));
		this->healthStat->SetColor(sf::Color::White);
		scene->removeGameObject(this->nextBattleButton);
	});

	attackStat = new Box("attackInfo", font, "", sf::Vector2f(250.0f, 80.0f), sf::Color::White);
	attackStat->setPosition(sf::Vector2f(750.0f, 280.0f));
	attackStat->setCharacterSize(30);
	attackPlus = new Button("attackPlus", font, "+", sf::Vector2f(70.0f, 70.0f), buttonFontColor, buttonSound);
	attackPlus->setPosition(sf::Vector2f(1020.0f, 284.0f));
	attackPlus->setCharacterSize(30);
	attackPlus->SetButtonAction([scene, this]() {
		scene->removeGameObject(this->healthPlus);
		scene->removeGameObject(this->attackPlus);
		scene->removeGameObject(this->defensePlus);
		scene->addGameObject(this->attackMinus);
		this->playerCharacter->setAttack(this->playerCharacter->getAttack() + 1);
		this->attackStat->SetText("Attack: " + std::to_string(this->playerCharacter->getAttack()));
		this->attackStat->SetColor(sf::Color::Green);
		scene->addGameObject(this->nextBattleButton);
	});
	attackMinus = new Button("attackMinus", font, "-", sf::Vector2f(70.0f, 70.0f), buttonFontColor, buttonSound);
	attackMinus->setPosition(sf::Vector2f(660.0f, 284.0f));
	attackMinus->setCharacterSize(30);
	attackMinus->SetButtonAction([scene, this]() {
		scene->addGameObject(this->healthPlus);
		scene->addGameObject(this->attackPlus);
		scene->addGameObject(this->defensePlus);
		scene->removeGameObject(this->attackMinus);
		this->playerCharacter->setAttack(this->playerCharacter->getAttack() - 1);
		this->attackStat->SetText("Attack: " + std::to_string(this->playerCharacter->getAttack()));
		this->attackStat->SetColor(sf::Color::White);
		scene->removeGameObject(this->nextBattleButton);
	});

	defenseStat = new Box("defenseInfo", font, "", sf::Vector2f(250.0f, 80.0f), sf::Color::White);
	defenseStat->setPosition(sf::Vector2f(750.0f, 380.0f));
	defenseStat->setCharacterSize(30);
	defensePlus = new Button("defensePlus", font, "+", sf::Vector2f(70.0f, 70.0f), buttonFontColor, buttonSound);
	defensePlus->setPosition(sf::Vector2f(1020.0f, 384.0f));
	defensePlus->setCharacterSize(30);
	defensePlus->SetButtonAction([scene, this]() {
		scene->removeGameObject(this->healthPlus);
		scene->removeGameObject(this->attackPlus);
		scene->removeGameObject(this->defensePlus);
		scene->addGameObject(this->defenseMinus);
		this->playerCharacter->setDefense(this->playerCharacter->getDefense() + 1);
		this->defenseStat->SetText("Defense: " + std::to_string(this->playerCharacter->getDefense()));
		this->defenseStat->SetColor(sf::Color::Green);
		scene->addGameObject(this->nextBattleButton);
	});
	defenseMinus = new Button("defenseMinus", font, "-", sf::Vector2f(70.0f, 70.0f), buttonFontColor, buttonSound);
	defenseMinus->setPosition(sf::Vector2f(660.0f, 384.0f));
	defenseMinus->setCharacterSize(30);
	defenseMinus->SetButtonAction([scene, this]() {
		scene->addGameObject(this->healthPlus);
		scene->addGameObject(this->attackPlus);
		scene->addGameObject(this->defensePlus);
		scene->removeGameObject(this->defenseMinus);
		this->playerCharacter->setDefense(this->playerCharacter->getDefense() - 1);
		this->defenseStat->SetText("Defense: " + std::to_string(this->playerCharacter->getDefense()));
		this->defenseStat->SetColor(sf::Color::White);
		scene->removeGameObject(this->nextBattleButton);
	});

	// Game Over components...
	scoreBox = new Box("scoreBox", font, "You scored: " + std::to_string(score), sf::Vector2f(800.0f, 100.0f), sf::Color::White);
	scoreBox->setPosition(sf::Vector2f(235.0f, 325.0f));
	scoreBox->setCharacterSize(40);

	exitButton = new Button("exitButton", font, "Main Menu", sf::Vector2f(220.0f, 80.0f), buttonFontColor, buttonSound);
	exitButton->setPosition(sf::Vector2f(1050.0f, 10.0f));
	exitButton->SetButtonAction([&handler, this, scene]() {
		handler.popScene();
		handler.popScene();

		// Save score on file...
		this->scoreBoard.AddScore(this->playerName + ": " + std::to_string(score));
		this->music.openFromFile("Sounds/Music/Main_Menu.mp3");
		this->music.play();

		this->ResetManager();
	});

	battleScene->addGameObject(exitButton);

	SetScenery();
}

BattleManager::~BattleManager() {

	for (int i = 0; i < 4; i++) 
	{
		delete enemies[i];
	}

	delete playerHealth;
	delete enemyHealth;

	delete attackButton;
	delete healButton;
	delete resignButton;

	delete playerText;
	delete enemyText;

	delete backgroundBox;

	delete nextBattleButton;

	delete healthStat;
	delete healthPlus;
	delete healthMinus;

	delete attackStat;
	delete attackPlus;
	delete attackMinus;

	delete defenseStat;
	delete defensePlus;
	delete defenseMinus;

	delete scoreBox;
	delete exitButton;

	delete textArea;
	delete toggleTextArea;
}

void BattleManager::update() {
	UpdateScenery();
	UpdateTurns();
}

void BattleManager::SetScenery(){
	float hp;
	int newHP;

	for (int i = 0; i < 4; i++)
	{
		battleScene->removeGameObject(enemies[i]);
	}
	
	switch (currentStage)
	{
		case 0:
			// Remove/Replace everything...
			enemyHealth->SetCharacter(*enemies[0]);
			battleScene->SetBackground("Backgrounds/forest.png", window->getView().getSize());

			// Scale the enemies hp by the multiply factor...
			hp = defaultHPEnemies[0];
			newHP = static_cast<int>(std::round(hp * enemyHealthMultiplier));
			enemies[0]->setMaxHP(newHP);
			enemies[0]->setHP(newHP);
			enemies[0]->setAttack(enemies[0]->getAttack() + attackIncrease);
			enemies[0]->setDefense(enemies[0]->getDefense() + defenseIncrease);

			battleScene->addGameObject(enemies[0]);
			AddTextInfo(enemies[0]->getIdentifier() + " has appeared!");
			break;

		case 1:
			enemyHealth->SetCharacter(*enemies[1]);
			battleScene->SetBackground("Backgrounds/cave.png", window->getView().getSize());

			hp = defaultHPEnemies[1];
			newHP = static_cast<int>(std::round(hp * enemyHealthMultiplier));
			enemies[1]->setMaxHP(newHP);
			enemies[1]->setHP(newHP);
			enemies[1]->setAttack(enemies[1]->getAttack() + 1);
			enemies[1]->setDefense(enemies[1]->getDefense() + defenseIncrease);

			battleScene->addGameObject(enemies[1]);
			AddTextInfo(enemies[1]->getIdentifier() + " has appeared!");
			break;

		case 2:
			enemyHealth->SetCharacter(*enemies[2]);
			battleScene->SetBackground("Backgrounds/crystal.png", window->getView().getSize());

			hp = defaultHPEnemies[2];
			newHP = static_cast<int>(std::round(hp * enemyHealthMultiplier));
			enemies[2]->setMaxHP(newHP);
			enemies[2]->setHP(newHP);
			enemies[2]->setAttack(enemies[2]->getAttack() + 1);
			enemies[2]->setDefense(enemies[2]->getDefense() + defenseIncrease);

			battleScene->addGameObject(enemies[2]);
			AddTextInfo(enemies[2]->getIdentifier() + " has appeared!");
			break;

		case 3:
			enemyHealth->SetCharacter(*enemies[3]);
			battleScene->SetBackground("Backgrounds/lava.png", window->getView().getSize());

			hp = defaultHPEnemies[3];
			newHP = static_cast<int>(std::round(hp * enemyHealthMultiplier));
			enemies[3]->setMaxHP(newHP);
			enemies[3]->setHP(newHP);
			enemies[3]->setAttack(enemies[3]->getAttack() + 1);
			enemies[3]->setDefense(enemies[3]->getDefense() + defenseIncrease);

			battleScene->addGameObject(enemies[3]);
			AddTextInfo(enemies[3]->getIdentifier() + " has appeared!");
			break;
	}
}

void BattleManager::UpdateScenery()
{
	if (enemyDied && clock.getElapsedTime().asSeconds() > sceneChangeInterval) {
		// Upgrade screen...

		battleScene->removeGameObject(toggleTextArea);
		if(textAreaVisible) battleScene->removeGameObject(textArea);

		battleScene->addGameObject(backgroundBox);

		battleScene->addGameObject(healthStat);
		battleScene->addGameObject(healthPlus);

		battleScene->addGameObject(attackStat);
		battleScene->addGameObject(attackPlus);

		battleScene->addGameObject(defenseStat);
		battleScene->addGameObject(defensePlus);

		// Set text of current stats...
		healthStat->SetText("Health: " + std::to_string(playerCharacter->getMaxHP()));
		attackStat->SetText("Attack: " + std::to_string(playerCharacter->getAttack()));
		defenseStat->SetText("Defense: " + std::to_string(playerCharacter->getDefense()));

		// Remove and add player to put it to the front...
		battleScene->removeGameObject(playerCharacter);
		battleScene->addGameObject(playerCharacter);

		battleScene->removeGameObject(exitButton);
		battleScene->addGameObject(exitButton);

		// Scale and position the player accordingly...
		if (playerCharacter->getIdentifier() != "Mage")
		{
			playerCharacter->setScale(sf::Vector2f(8.0f, 8.0f));
			if (playerCharacter->getIdentifier() == "Ranger") playerCharacter->setPosition(sf::Vector2f(-25.0f, 0.0f));
			else playerCharacter->setPosition(sf::Vector2f(-250.0f, -220.0f));
		}
		else 
		{
			playerCharacter->setScale(sf::Vector2f(4.0f, 4.0f));
			playerCharacter->setPosition(sf::Vector2f(-50.0f, 0.0f));
		}

		enemyDied = false;
	}
	else if (playerDied && clock.getElapsedTime().asSeconds() > sceneChangeInterval) {
		// Game Over screen...
		battleScene->removeGameObject(attackButton);
		battleScene->removeGameObject(healButton);
		battleScene->removeGameObject(resignButton);
		buttonsActive = false;
		battleScene->removeGameObject(toggleTextArea);

		battleScene->removeGameObject(textArea);
		textAreaVisible = false;
		battleScene->addGameObject(backgroundBox);
		backgroundBox->SetText("Game Over\n\n");
		backgroundBox->setCharacterSize(65);
		battleScene->addGameObject(scoreBox);
		scoreBox->SetText("You scored: " + std::to_string(score));

		exitButton->setPosition(sf::Vector2f(535.0f, 450.0f));
		battleScene->removeGameObject(exitButton);
		battleScene->addGameObject(exitButton);
	}
}

void BattleManager::UpdateTurns()
{
	// Player attacks Enemy / heals...
	if ((damageToEnemy >= 0 && playerCharacter->FinishedAnimating()) || healPlayerAmount >= 0)
	{
		if (healPlayerAmount < 0 && !resigned) {
			enemies[currentStage]->takeDamage(damageToEnemy);
			enemyText->SetText(std::to_string(damageToEnemy));
			if (currentStage != 2) enemyText->SetColor(sf::Color::Red);
			else enemyText->SetColor(sf::Color::White);
			enemyText->Reactivate();
			AddTextInfo(playerCharacter->getIdentifier() + " attacked " + enemies[currentStage]->getIdentifier() + " and dealt " + std::to_string(damageToEnemy) + " damage");
			damageToEnemy = -1;
		}
		else if (healPlayerAmount > 0)
		{
			playerText->SetText(std::to_string(healPlayerAmount));
			playerText->SetColor(sf::Color::Green);
			playerText->Reactivate();
			AddTextInfo(playerCharacter->getIdentifier() + " healed by " + std::to_string(healPlayerAmount) + " health");
			healPlayerAmount = -1;
		}

		playersTurn = false;
		clock.restart();

		// Enemy died...
		if (enemies[currentStage]->getHP() <= 0) {
			score += 100;
			enemyDied = true;
			AddTextInfo(playerCharacter->getIdentifier() + " defeated " + enemies[currentStage]->getIdentifier() + "!");
			AddTextInfo("Current score: " + std::to_string(score));
		}
	}
	// Player takes damage...
	else if ((damageToPlayer >= 0) && enemies[currentStage]->GetCurrentState() == State::Idle)
	{
		playerCharacter->takeDamage(damageToPlayer);
		playerText->SetText(std::to_string(damageToPlayer));
		if (currentStage != 2) playerText->SetColor(sf::Color::Red);
		else playerText->SetColor(sf::Color::White);
		playerText->Reactivate();
		AddTextInfo(enemies[currentStage]->getIdentifier() + " attacked " + playerCharacter->getIdentifier() + " and dealt " + std::to_string(damageToPlayer) + " damage");
		damageToPlayer = -1;
		clock.restart();

		// Player died...
		if(playerCharacter->getHP() <= 0) {
			AddTextInfo(playerCharacter->getIdentifier() + " was defeated!");
			playerDied = true;
		}
	}
	// Enemy attacks Player...
	else if (!playersTurn && enemies[currentStage]->GetCurrentState() == State::Idle && clock.getElapsedTime().asSeconds() > turnInterval)
	{
		// The "Do-Nothing" mechanic...
		int randomValue = std::rand() % 10;
		if (randomValue == 0 && !resigned)
		{
			AddTextInfo(enemies[currentStage]->getIdentifier() + " skipped his turn!");
			enemyText->SetText("Skip");
			enemyText->SetColor(sf::Color::Yellow);
			enemyText->Reactivate();
			enemySkipped = true;

			soundEffects.loadFromFile("Sounds/SFX/Action/skip.mp3");
			enemySound.setBuffer(soundEffects);
			enemySound.play();
		}
		else
		{
			damageToPlayer = enemies[currentStage]->attackCharacter(*playerCharacter);
			if (resigned) damageToPlayer = 99999;
		}

		playersTurn = true;
	}
	
	if (playersTurn && (playerCharacter->FinishedAnimating() || enemySkipped) && playerCharacter->getHP() > 0)
	{
		if (enemySkipped) enemySkipped = false;
		ToggleButtons();
	}
}

void BattleManager::ResetManager()
{
	// Clear text area...
	textArea->SetText("");
	textAreaText.clear();

	// Activate all buttons...
	battleScene->addGameObject(attackButton);
	battleScene->addGameObject(healButton);
	battleScene->addGameObject(resignButton);
	buttonsActive = true;
	battleScene->addGameObject(toggleTextArea);

	// Reset all values for new battle...
	playersTurn = true;
	enemySkipped = false;
	resigned = false;
	enemyDied = false;

	score = 0;
	healPlayerAmount = -1;
	currentStage = 0;
	enemyHealthMultiplier = 1;
	attackIncrease = 0;
	defenseIncrease = 0;
	damageToPlayer = -1;
	damageToEnemy = -1;
	playerDied = false;

	// Remove upgrade screen...
	battleScene->removeGameObject(backgroundBox);
	battleScene->removeGameObject(healthStat);
	battleScene->removeGameObject(attackStat);
	battleScene->removeGameObject(defenseStat);
	battleScene->removeGameObject(healthMinus);
	battleScene->removeGameObject(attackMinus);
	battleScene->removeGameObject(defenseMinus);
	battleScene->removeGameObject(healthPlus);
	battleScene->removeGameObject(attackPlus);
	battleScene->removeGameObject(defensePlus);
	battleScene->removeGameObject(nextBattleButton);
	healthStat->SetColor(sf::Color::White);
	attackStat->SetColor(sf::Color::White);
	defenseStat->SetColor(sf::Color::White);

	if (playerCharacter->getIdentifier() != "Mage")
	{
		playerCharacter->setScale(sf::Vector2f(6.0f, 6.0f));
		if (playerCharacter->getIdentifier() == "Ranger") playerCharacter->setPosition(sf::Vector2f(80.0f, 175.0f));
		else playerCharacter->setPosition(sf::Vector2f(-70.0f, 5.0f));
	}
	else
	{
		playerCharacter->setScale(sf::Vector2f(3.0f, 3.0f));
		playerCharacter->setPosition(sf::Vector2f(50.0f, 160.0f));
	}

	for (int i = 0; i < 4; i++)
	{
		enemies[i]->setHP(defaultHPEnemies[i]);
		enemies[i]->setMaxHP(defaultHPEnemies[i]);
		enemies[i]->setAttack(defaultAttackEnemies[i]);
		enemies[i]->setDefense(defaultDefenseEnemies[i]);
	}

	// Remove gane over...
	battleScene->removeGameObject(backgroundBox);
	exitButton->setPosition(sf::Vector2f(1050.0f, 10.0f));
	battleScene->removeGameObject(scoreBox);
	battleScene->removeGameObject(playerCharacter);
	backgroundBox->SetText("");

	playerCharacter->ResetCharacter();
	SetScenery();
}

void BattleManager::SetPlayerCharacter(Character& playerCharacter)
{
	this->playerCharacter = &playerCharacter;
	playerHealth->SetCharacter(playerCharacter);
}

Character& BattleManager::GetCurrentEnemy() const 
{
	return *enemies[currentStage];
}

void BattleManager::ActionButton()
{
	damageToEnemy = playerCharacter->attackCharacter(GetCurrentEnemy());
	ToggleButtons();
}

void BattleManager::HealButton()
{
	healPlayerAmount = playerCharacter->Heal();
	ToggleButtons();
}

void BattleManager::ResignButton()
{
	// Game Over screen...
	resigned = true;
	playersTurn = false;
	ToggleButtons();
}

void BattleManager::NextBattleButton()
{
	// Remove the upgrade screen...
	battleScene->removeGameObject(backgroundBox);
	battleScene->removeGameObject(healthStat);
	battleScene->removeGameObject(attackStat);
	battleScene->removeGameObject(defenseStat);
	battleScene->removeGameObject(healthMinus);
	battleScene->removeGameObject(attackMinus);
	battleScene->removeGameObject(defenseMinus);
	battleScene->removeGameObject(nextBattleButton);
	healthStat->SetColor(sf::Color::White);
	attackStat->SetColor(sf::Color::White);
	defenseStat->SetColor(sf::Color::White);

	if (playerCharacter->getIdentifier() != "Mage")
	{
		playerCharacter->setScale(sf::Vector2f(6.0f, 6.0f));
		if (playerCharacter->getIdentifier() == "Ranger") playerCharacter->setPosition(sf::Vector2f(80.0f, 175.0f));
		else playerCharacter->setPosition(sf::Vector2f(-70.0f, 5.0f));
	}
	else
	{
		playerCharacter->setScale(sf::Vector2f(3.0f, 3.0f));
		playerCharacter->setPosition(sf::Vector2f(50.0f, 160.0f));
	}

	// Go to next stage...
	currentStage++;
	playersTurn = true;
	ToggleButtons();
	if (currentStage > 3)
	{
		currentStage = 0;
		enemyHealthMultiplier += 0.5f;
		attackIncrease += 1;
		defenseIncrease += 1;
	}
	SetScenery();
}

void BattleManager::ToggleButtons()
{
	if (buttonsActive)
	{
		battleScene->removeGameObject(attackButton);
		battleScene->removeGameObject(healButton);
		battleScene->removeGameObject(resignButton);
		buttonsActive = false;
	}
	else
	{
		battleScene->addGameObject(attackButton);
		battleScene->addGameObject(healButton);
		battleScene->addGameObject(resignButton);
		buttonsActive = true;
	}
}

void BattleManager::AddTextInfo(std::string info)
{
	// Remove the oldest info if at max...
	if (textAreaText.size() >= 3) {
		textAreaText.erase(textAreaText.begin());
	}

	info += "\n";
	textAreaText.push_back(info);

	std::string infoText = "";
	for (std::vector<std::string>::iterator it = textAreaText.begin(); it != textAreaText.end(); ++it) 
	{
		infoText += *it;
	}

	textArea->SetText(infoText);
}