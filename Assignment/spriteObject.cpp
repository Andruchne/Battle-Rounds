#include "spriteObject.hpp"

SpriteObject::SpriteObject(std::string identifier, std::string spriteFile) :
    GameObject(identifier), spriteFile(spriteFile)
{
    this->texture.loadFromFile(this->spriteFile);
    this->sprite.setTexture(this->texture);
}

SpriteObject::SpriteObject(const SpriteObject& other) :
    GameObject(other.getIdentifier()), spriteFile(other.getSpriteFile())
{
    this->texture.loadFromFile(this->spriteFile);
    this->sprite.setTexture(this->texture);
}

SpriteObject::~SpriteObject() { }

void SpriteObject::update() {
    UpdateLocalPosition();
}

void SpriteObject::render(sf::RenderWindow& window) {
    //printf("Rendering sprite\n");
    window.draw(this->sprite);
    GameObject::render(window, localPosition); // this calls the base class method for this particular object
}

void SpriteObject::render(sf::RenderWindow& window, sf::Vector2f pLocalPosition) {
    //printf("X: %f Y: %f\n", offset.x, offset.y);
    sf::Vector2f newPosition = pLocalPosition + parentOffset;
    setPosition(newPosition);

    window.draw(this->sprite);
    GameObject::render(window, newPosition); // this calls the base class method for this particular object
}

void SpriteObject::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);

    // My addition
    localPosition = position;
    if (parent != NULL) SetOffset();
}

void SpriteObject::setScale(sf::Vector2f scale) {
    sprite.setScale(scale);
}

void SpriteObject::mirrorHorizontal()
{
    sprite.setScale(sf::Vector2f(sprite.getScale().x * -1, sprite.getScale().y));
}

std::string SpriteObject::getSpriteFile() const {
    return this->spriteFile;
}

void SpriteObject::UpdateLocalPosition()
{
    if (localPosition != sprite.getPosition())
    {
        localPosition = sprite.getPosition();
    }
}

sf::Vector2f SpriteObject::getPosition() const{
    return this->sprite.getPosition();
}