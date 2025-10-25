#include "animationSprite.hpp"

AnimationSprite::AnimationSprite(std::string identifier, std::string spriteFile, int columns, int rows) :
    SpriteObject(identifier, spriteFile), columns(columns), rows(rows)
{
    this->texture.loadFromFile(spriteFile);
    this->spriteWidth = texture.getSize().x / columns;
    this->spriteHeight = texture.getSize().y / rows;
    this->currentSpritePos.width = spriteWidth;
    this->currentSpritePos.height = spriteHeight;

    // Loop animation on default...
    this->AnimateLoop();
}

AnimationSprite::AnimationSprite(const AnimationSprite& other) :
    SpriteObject(other.getIdentifier(), other.getSpriteFile()), rows(other.rows), columns(other.columns)
{
    this->texture.loadFromFile(spriteFile);
    this->spriteWidth = texture.getSize().x / columns;
    this->spriteHeight = texture.getSize().y / rows;
    this->currentSpritePos.width = spriteWidth;
    this->currentSpritePos.height = spriteHeight;

    // Loop animation on default...
    this->AnimateLoop();
}

AnimationSprite::~AnimationSprite() { }

void AnimationSprite::update(){ }

void AnimationSprite::render(sf::RenderWindow& window)
{
    this->animate();
    window.draw(sprite);
}

void AnimationSprite::SetFramesPerSecond(float fps)
{
    animationInterval = 1.0f / fps;
}

void AnimationSprite::SetSprite(std::string spriteFile, int columns, int rows)
{
    currentSpritePos.top = 0;
    currentSpritePos.left = 0;
    resetAnim = true;
    this->texture.loadFromFile(spriteFile);
    this->spriteWidth = texture.getSize().x / columns;
    this->spriteHeight = texture.getSize().y / rows;
    this->currentSpritePos.width = spriteWidth;
    this->currentSpritePos.height = spriteHeight;
    this->columns = columns;
    this->rows = rows;
}

void AnimationSprite::SetAnimate(std::function<void()> animate)
{
    this->animate = animate;
}

void AnimationSprite::AnimateLoop()
{
    int& rows = this->rows;
    int& columns = this->columns;
    int& spriteWidth = this->spriteWidth;
    int& spriteHeight = this->spriteHeight;
    float& animationInterval = this->animationInterval;
    sf::IntRect& currentSpritePos = this->currentSpritePos;
    sf::Clock& clock = this->clock;
    sf::Sprite& sprite = this->sprite;
    bool& resetAnim = this->resetAnim;

    SetAnimate([&rows, &columns, &spriteWidth, &spriteHeight, &animationInterval, 
        &currentSpritePos, &clock, &sprite, &resetAnim](){
        if (clock.getElapsedTime().asSeconds() > animationInterval || resetAnim) {
            if (resetAnim) resetAnim = false;

            if (currentSpritePos.left == spriteWidth * (columns - 1))
            {
                currentSpritePos.left = 0;
                if (currentSpritePos.top == spriteHeight * (rows - 1))
                {
                    currentSpritePos.top = 0;
                }
                else currentSpritePos.top += spriteHeight;
            }
            else currentSpritePos.left += spriteWidth;

            sprite.setTextureRect(currentSpritePos);
            clock.restart();
        }
    });
}

void AnimationSprite::AnimateOnce()
{
    int& rows = this->rows;
    int& columns = this->columns;
    int& spriteWidth = this->spriteWidth;
    int& spriteHeight = this->spriteHeight;
    float& animationInterval = this->animationInterval;
    sf::IntRect& currentSpritePos = this->currentSpritePos;
    sf::Clock& clock = this->clock;
    sf::Sprite& sprite = this->sprite;
    bool& finishedAnimation = this->finishedAnimation;
    bool& resetAnim = this->resetAnim;
    
    SetAnimate([&rows, &columns, &spriteWidth, &spriteHeight, &animationInterval, 
        &currentSpritePos, &clock, &sprite, &finishedAnimation, &resetAnim]() {
        if ((clock.getElapsedTime().asSeconds() > animationInterval || resetAnim) && !finishedAnimation) {
            if (resetAnim) resetAnim = false;

            if (currentSpritePos.left == spriteWidth * (columns - 1) && currentSpritePos.top == spriteHeight * (rows - 1))
            {
                finishedAnimation = true;
            }
            
            if (currentSpritePos.left != spriteWidth * (columns - 1))
            {
                currentSpritePos.left += spriteWidth;
                if (currentSpritePos.top != spriteHeight * (rows - 1))
                {
                    currentSpritePos.top += spriteHeight;
                }
            }
            sprite.setTextureRect(currentSpritePos);
            clock.restart();
        }
    });
}

bool AnimationSprite::FinishedAnimating() const
{
    return finishedAnimation;
}