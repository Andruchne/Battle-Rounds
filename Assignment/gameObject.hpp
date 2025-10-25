#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

class GameObject {
    private: 
        const std::string identifier;

    protected:
        void SetOffset();
        std::vector<GameObject*> listOfGameObjects;
        sf::Vector2f parentOffset;

    public:
        GameObject(std::string identifier);
        GameObject(const GameObject& other);

        virtual ~GameObject();

        virtual void update() = 0;
        virtual void render(sf::RenderWindow& window);
        virtual void render(sf::RenderWindow& window, sf::Vector2f pLocalPosition);
        virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) { };
        std::string getIdentifier() const;

        sf::Vector2f localPosition;
        GameObject* parent;
        void AddChild(GameObject* pGameObject);
        void RemoveChild(GameObject* pGameObject);
        void SeperateFromParent(); // SeperateFromParent public?
        void SetParent(GameObject* pGameObject);
};