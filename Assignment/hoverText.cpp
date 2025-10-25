#include "HoverText.hpp"
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

HoverText::HoverText(std::string identifier, sf::Font& font, std::string textString, int size, sf::Color color, sf::Vector2f startPos) : 
    GameObject(identifier){
    
    active = true;
    currentTime = 0;
    currentAlpha = 255.0f;

    totalTime = 1800.0f;
    lastCurveValue = 0.0f;

    this->text.setFont(font);
    this->text.setString(textString);
    this->text.setCharacterSize(size);
    this->text.setFillColor(color);
    this->text.setPosition(startPos);
    this->startPos = startPos;
}

HoverText::~HoverText() { }

void HoverText::update() {
    if (active) {
        currentTime = clock.getElapsedTime().asMilliseconds();

        currentAlpha = 255.0f * (1 - currentTime / totalTime);
        text.setFillColor(sf::Color(text.getFillColor().r, text.getFillColor().g, text.getFillColor().b, currentAlpha));
        Tween();

        if (currentTime >= totalTime) {
            active = false;
            ResetText();
        }
    }
}

void HoverText::render(sf::RenderWindow& window) {
    if (active) {
        window.draw(this->text);
    }
}

void HoverText::Tween(){
    float newCurveValue = GetCurveValue(3.0f * currentTime / (totalTime + 1000)) * 25.0f;
    float output = newCurveValue - lastCurveValue;

    text.setPosition(sf::Vector2f(text.getPosition().x + output, text.getPosition().y  -1.0f));
    lastCurveValue = newCurveValue;
}

float HoverText::GetCurveValue(float t){
    // Clamp the value t between 0 and 1...
    if (t < 0) t = 0;
    else if (t > 1) t = 1;

    // Shake...
    return std::sinf(glm::pi<float>() * 5.0f * t) * (1.0f - t);
}

void HoverText::Reactivate(){
    active = true;
    clock.restart();
    text.setPosition(startPos);
}

void HoverText::ResetText() {
    lastCurveValue = 0;
    currentAlpha = 255;
}

void HoverText::SetText(std::string textString) {
    this->text.setString(textString);
}

void HoverText::SetColor(sf::Color color) {
    this->text.setFillColor(sf::Color(color.r, color.g, color.b, currentAlpha));
}