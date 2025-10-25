#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <algorithm>
#include <random>

#include "animationSprite.hpp"
#include "spriteInfo.hpp"


class Character : public AnimationSprite {
private:
    sf::Sound& characterSound;

    State currentState;
    std::string name;
    std::string spriteFile;

    int defaultHP;
    int defaultAttack;
    int defaultDefense;

    int maxHP;
    int hp;
    int attack;
    int defense;
    SpriteInfo* animations[4];
    sf::SoundBuffer soundEffects;

    void SetAnimation(State state);

    public:
        Character(std::string name, std::string spriteFile, int columns, int rows, int hp, int attack, int defense, sf::Sound& characterSound);
        ~Character();

        void update() override;

        int attackCharacter(const Character& character);
        bool takeDamage(int damage);
        int Heal();

        int getAttack() const;
        void setAttack(int attack);

        int getDefense() const;
        void setDefense(int defense);

        int getHP() const;
        int getMaxHP() const;
        void setHP(int hp);
        void setMaxHP(int hp);

        std::string getName() const;
        void setName(std::string name);

        std::string getSpriteFile() const;

        void AddAnimationSprite(State state, std::string spriteFile, int columns, int rows, std::string soundFile);
        void AddAnimationSprite(State state, std::string spriteFile, int columns, int rows);

        void PlayAttackAnimation();
        void PlayHitAnimation();
        void PlayDeathAnimation();
        void PlayIdleAnimation();

        State GetCurrentState() const;
        void ResetCharacter();
};


