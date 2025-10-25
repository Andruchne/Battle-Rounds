#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "gameObject.hpp"

class Scene {
    private:
        const std::string identifier;
        std::vector<GameObject*> listOfGameObjects;
        sf::Sprite sprite;
        sf::Texture texture;

    public:
        Scene(std::string identifier);
        ~Scene();

    public:
        void SetBackground(std::string textureFile, sf::Vector2f windowSize);
        void addGameObject(GameObject* object);
        void removeGameObject(GameObject* object);
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
        void update();
        void render(sf::RenderWindow& window);

        std::string getIdentifier() const;
};