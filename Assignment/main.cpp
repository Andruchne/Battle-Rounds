#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <fstream>
#include <iostream>

#include "scene.hpp"
#include "textObject.hpp"
#include "spriteObject.hpp"
#include "character.hpp"
#include "button.hpp"
#include "sceneHandler.hpp"
#include "animationSprite.hpp"
#include "healthBar.hpp"
#include "battleManager.hpp"
#include "hoverText.hpp"
#include "mainMenu.hpp"
#include "scoreBoardObj.hpp"
#include "charSelect.hpp"

int main(int argc, char *argv[]) {
    // Name of player
    std::string playerName;
    if (argc > 1) {
        playerName += argv[1];
    }
    else playerName = "Player";

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Assignment", sf::Style::Close);
    window.setFramerateLimit(60);

    // Setup all scenes
    Scene mainMenuScene("mainMenu");
    mainMenuScene.SetBackground("Backgrounds/menu.png", window.getView().getSize());

    Scene scoreScene("scoreBoard");
    scoreScene.SetBackground("Backgrounds/menu.png", window.getView().getSize());

    Scene charSelectScene("charSelect");
    charSelectScene.SetBackground("Backgrounds/menu.png", window.getView().getSize());

    Scene battle("battle");

    SceneHandler handler;
    handler.addScene(mainMenuScene);
    handler.addScene(scoreScene);
    handler.addScene(charSelectScene);
    handler.addScene(battle);

    // Setup sounds
    sf::Music music;
    music.openFromFile("Sounds/Music/Main_Menu.mp3");
    music.setLoop(true);
    music.setVolume(5.0f);
    music.play();

    sf::Sound buttonSound;
    buttonSound.setVolume(10.0f);
    sf::Sound playerSound;
    playerSound.setVolume(10.0f);

    sf::Font font;
    font.loadFromFile("FiveFontsatFreddy's-Regular.ttf");
    sf::Color darkColor = sf::Color(50, 50, 50, 255);

    // Setup Scoreboard
    ScoreBoard scoreboard;

    // Setup all characters

    Character mage("Mage", "Sprites/Mage/mageIdle.png", 6, 1, 12, 6, 3, playerSound);
    mage.AddAnimationSprite(State::Attack, "Sprites/Mage/mageAttack.png", 8, 1, "Sounds/SFX/Player/Mage/mage_attack.wav");
    mage.AddAnimationSprite(State::Hit, "Sprites/Mage/mageHit.png", 4, 1, "Sounds/SFX/Player/Mage/mage_hit.wav");
    mage.AddAnimationSprite(State::Death, "Sprites/Mage/mageDeath.png", 7, 1, "Sounds/SFX/Player/Mage/mage_death.wav");
    mage.SetFramesPerSecond(8);
    mage.setScale(sf::Vector2f(3, 3));

    Character ranger("Ranger", "Sprites/Ranger/rangerIdle.png", 10, 1, 15, 5, 3, playerSound);
    ranger.AddAnimationSprite(State::Attack, "Sprites/Ranger/rangerAttack.png", 6, 1, "Sounds/SFX/Player/Ranger/ranger_attack.wav");
    ranger.AddAnimationSprite(State::Hit, "Sprites/Ranger/rangerHit.png", 3, 1, "Sounds/SFX/Player/Ranger/ranger_hit.wav");
    ranger.AddAnimationSprite(State::Death, "Sprites/Ranger/rangerDeath.png", 10, 1, "Sounds/SFX/Player/Ranger/ranger_death.wav");
    ranger.SetFramesPerSecond(8);
    ranger.setScale(sf::Vector2f(6, 6));

    Character warrior("Warrior", "Sprites/Warrior/warriorIdle.png", 8, 1, 20, 4, 5, playerSound);
    warrior.AddAnimationSprite(State::Attack, "Sprites/Warrior/warriorAttack.png", 5, 1, "Sounds/SFX/Player/Warrior/warrior_attack.wav");
    warrior.AddAnimationSprite(State::Hit, "Sprites/Warrior/warriorHit.png", 3, 1, "Sounds/SFX/Player/Warrior/warrior_hit.wav");
    warrior.AddAnimationSprite(State::Death, "Sprites/Warrior/warriorDeath.png", 8, 1, "Sounds/SFX/Player/Warrior/warrior_death.wav");
    warrior.SetFramesPerSecond(8);
    warrior.setScale(sf::Vector2f(6, 6));

    // Main Menu
    MainMenu mainMenu("mainMenu", font, darkColor, buttonSound, handler, mage, warrior, ranger, window, mainMenuScene);

    // Scoreboard...
    ScoreBoardObj scoreBoardObj("scoreBoardObj", font, darkColor, buttonSound, scoreboard, handler, scoreScene);

    // Preparation for battle scene...
    BattleManager battleManager("battleManager", &battle, &mage, window, handler, scoreboard, music, buttonSound, playerName, font, darkColor);

    // Character Selection
    CharSelect charSelect("charSelectObj", font, buttonSound, music, battleManager, mage, ranger, warrior, handler, charSelectScene, battle);

    // Battle Scene
    battle.addGameObject(&battleManager);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else handler.handleEvent(event, window);

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::A) {
                }
            }
        }
        window.clear();
        handler.update();
        handler.render(window);
        window.display();
    }
    return 0;
}





