#include "gameObject.hpp"
#include "scene.hpp"

GameObject::GameObject(std::string identifier) : identifier(identifier) { }
 
GameObject::GameObject(const GameObject& other) : identifier(other.getIdentifier()) { }

GameObject::~GameObject() { }

std::string GameObject::getIdentifier() const {
    return this->identifier;
}

void GameObject::AddChild(GameObject* pGameObject)
{
    // If the gameObject isn't already in the list...
    if (std::find(listOfGameObjects.begin(), listOfGameObjects.end(), pGameObject) == listOfGameObjects.end())
    {
        listOfGameObjects.push_back(pGameObject);
        pGameObject->SetParent(this);
    }
    else printf("Object %s is already a child of object %s", pGameObject->identifier.c_str(), this->identifier.c_str());
}

void GameObject::RemoveChild(GameObject* pGameObject)
{
    for (int i = 0; i < listOfGameObjects.size(); i++)
    {
        if (pGameObject == listOfGameObjects[i])
        {
            listOfGameObjects.erase(listOfGameObjects.begin() + i);
        }
    }
}

void GameObject::SetParent(GameObject* pGameObject)
{
    parent = pGameObject;
    parentOffset = localPosition - parent->localPosition;
}

void GameObject::SeperateFromParent() // This is public...
{
    parent->RemoveChild(this);
    parent = NULL;
}

void GameObject::SetOffset()
{
    if (parent != NULL)
    {
        parentOffset = localPosition - parent->localPosition;
    }
}

void GameObject::render(sf::RenderWindow& window) {
    for (int i = 0; i < listOfGameObjects.size(); i++)
    {
        listOfGameObjects[i]->render(window, localPosition);
    }
}

void GameObject::render(sf::RenderWindow& window, sf::Vector2f pLocalPosition) {
    for (int i = 0; i < listOfGameObjects.size(); i++)
    {
        listOfGameObjects[i]->render(window, pLocalPosition);
    }
}