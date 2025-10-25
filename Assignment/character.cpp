#include "character.hpp"

Character::Character(std::string name, std::string spriteFile, int columns, int rows, int hp, int attack, int defense, sf::Sound& characterSound) :
    AnimationSprite(name, spriteFile, columns, rows),
    name(name), spriteFile(spriteFile), hp(hp), attack(attack), defense(defense), characterSound(characterSound)
{
    for (int i = 0; i < 4; i++)
    {
        animations[i] = NULL;
    }

    maxHP = hp;
    AddAnimationSprite(State::Idle, spriteFile, columns, rows);
    PlayIdleAnimation();

    defaultHP = hp;
    defaultAttack = attack;
    defaultDefense = defense;
}

Character::~Character() {
    for (int i = 0; i < 4; i++)
    {
        delete animations[i];
    }
}

void Character::update()
{
    // If character still alive -> Revert to idle animation...
    if (finishedAnimation && hp > 0) {
        PlayIdleAnimation();
        finishedAnimation = false;
    }
}

int Character::attackCharacter(const Character& character){
    int attackPower = attack + rand() % 4; 
    int defensePower = character.getDefense() + (-1 + rand() % 3); 

    PlayAttackAnimation();

    return std::max(attackPower - defensePower, 0);
}

bool Character::takeDamage(int damage) {
    hp = std::max(hp - damage, 0);
    if (hp > 0)
        PlayHitAnimation();
    else
        PlayDeathAnimation();

    return hp == 0;
}

int Character::getAttack() const {
    return this->attack;
}

void Character::setAttack(int attack) {
    this->attack = attack;
}

int Character::getDefense() const {
    return this->defense;
}

int Character::getHP() const {
    return this->hp;
}

int Character::getMaxHP() const {
    return this->maxHP;
}

std::string Character::getName() const {
    return this->name;
}

std::string Character::getSpriteFile() const {
    return this->spriteFile;
}

void Character::setDefense(int defense) {
    this->defense = defense;
}

void Character::setHP(int hp) {
    this->hp = hp;
}

void Character::setMaxHP(int hp) {
    this->maxHP = hp;
}

void Character::setName(std::string name) {
    this->name = name;
}

int Character::Heal()
{
    int healAmount = rand() % defense + 1;
    hp += healAmount;
    if (hp > maxHP) hp = maxHP;

    soundEffects.loadFromFile("Sounds/SFX/Action/heal.mp3");
    characterSound.setBuffer(soundEffects);
    characterSound.play();

    return healAmount;
}

void Character::AddAnimationSprite(State state, std::string spriteFile, int columns, int rows, std::string soundFile){
    bool doOnce = true;
    int i = 0;

    while (doOnce)
    {
        if ((animations[i] != NULL && animations[i]->GetState() == state) || animations[i] == NULL)
        {
            delete animations[i];
            animations[i] = new SpriteInfo(state, spriteFile, columns, rows);
            animations[i]->SetSoundFile(soundFile);
            doOnce = false;
        }
        i++;
    }
}

void Character::AddAnimationSprite(State state, std::string spriteFile, int columns, int rows) {
    bool doOnce = true;
    int i = 0;

    while (doOnce)
    {
        if ((animations[i] != NULL && animations[i]->GetState() == state) || animations[i] == NULL)
        {
            delete animations[i];
            animations[i] = new SpriteInfo(state, spriteFile, columns, rows);
            doOnce = false;
        }
        i++;
    }
}

void Character::SetAnimation(State state){
    // Set the current animation...
    for (int i = 0; i < 4; i++)
    {
        if (animations[i] != NULL && animations[i]->GetState() == state)
        {
            SetSprite(animations[i]->GetSpriteFile(), animations[i]->GetColumns(), animations[i]->GetRows());
            if (animations[i]->GetSoundFile() != "")
            {
                //printf("%d", soundEffects.loadFromFile(animations[i]->GetSoundFile()) == 0);
                soundEffects.loadFromFile(animations[i]->GetSoundFile());
                characterSound.setBuffer(soundEffects);
                characterSound.play();
            }
        }
    }
}

void Character::PlayIdleAnimation(){

    currentState = State::Idle;
    SetAnimation(State::Idle);
    AnimateLoop();
}

void Character::PlayAttackAnimation(){
    currentState = State::Attack;
    SetAnimation(State::Attack);
    AnimateOnce();
}

void Character::PlayHitAnimation(){
    currentState = State::Hit;
    SetAnimation(State::Hit);
    AnimateOnce();
}

void Character::PlayDeathAnimation(){
    currentState = State::Death;
    SetAnimation(State::Death);
    AnimateOnce();
}

State Character::GetCurrentState() const{
    return currentState;
}

void Character::ResetCharacter(){
    maxHP = defaultHP;
    hp = defaultHP;
    attack = defaultAttack;
    defense = defaultDefense;
}