#include "scene.hpp"

Scene::Scene(std::string identifier) : identifier(identifier) { }

Scene::~Scene() { }

void Scene::SetBackground(std::string textureFile, sf::Vector2f windowSize)
{
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(windowSize.x / texture.getSize().x, windowSize.y / texture.getSize().y));
    sprite.setPosition(0, 0);
}

void Scene::addGameObject(GameObject* object) {
    if (std::find(listOfGameObjects.begin(), listOfGameObjects.end(), object) == listOfGameObjects.end())
    {
        this->listOfGameObjects.push_back(object);
    }
}

void Scene::removeGameObject(GameObject* object) {
    for (int i = 0; i < listOfGameObjects.size(); i++)
    {
        if (object == listOfGameObjects[i])
        {
            this->listOfGameObjects.erase(listOfGameObjects.begin() + i);
        }
    }
}

void Scene::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    for(unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
        this->listOfGameObjects[i]->handleEvent(event, window);
    }
}

void Scene::update() { 
    for(unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
        this->listOfGameObjects[i]->update();
    }
}

void Scene::render(sf::RenderWindow& window) { 
    window.draw(this->sprite);
    for(unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
       this->listOfGameObjects[i]->render(window);
    }
}

std::string Scene::getIdentifier() const {
    return this->identifier;
}