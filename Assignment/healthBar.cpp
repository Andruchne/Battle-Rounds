#include "healthBar.hpp"

HealthBar::HealthBar(std::string identifier, Character& character) : GameObject(identifier){
	this->character = &character;
	healthBarOffset = sf::Vector2f(8, 2);

	container = new SpriteObject("containerHP", "Sprites/Components/healthContainer.png");
	healthBar = new SpriteObject("barHP", "Sprites/Components/healthBar.png");
	// Correct healthBar placement...
	healthBar->setPosition(sf::Vector2f(healthBar->getPosition() + healthBarOffset));
	currentPos = container->getPosition();
	SetScale(sf::Vector2f(1.0f, 1.0f));
}

HealthBar::~HealthBar() { 
	delete container;
	delete healthBar;
}

void HealthBar::update() {
	float currentHP = character->getHP();
	float maxHP = character->getMaxHP();
	float newScale = Lerp(0, 1, currentHP / maxHP);
	healthBar->setScale(sf::Vector2f(currentScale.x * newScale, currentScale.y));
}

void HealthBar::render(sf::RenderWindow& window) {
	this->healthBar->render(window);
	this->container->render(window);
}

void HealthBar::SetPosition(sf::Vector2f pos){
	this->healthBar->setPosition(pos);
	sf::Vector2f newOffset(healthBarOffset.x * currentScale.x, healthBarOffset.y * currentScale.y);
	healthBar->setPosition(sf::Vector2f(healthBar->getPosition() + newOffset));
	this->container->setPosition(pos);
	currentPos = pos;
}

void HealthBar::SetScale(sf::Vector2f scale){
	this->healthBar->setScale(scale);
	this->container->setScale(scale);
	currentScale = scale;
	SetPosition(currentPos);
}

void HealthBar::SetCharacter(Character& character){
	this->character = &character;
}

float HealthBar::Lerp(float a, float b, float t) {
	return a + t * (b - a);
}