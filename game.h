
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "player.h"
#include "level.h"
#include <map>
#include <vector>
#include <future>
#include <mutex>
#include "menu.h"
#include <ranges>
import gameState;
class game {
    invader invaderInGame;
    std::map<int, level> mapOfLevels;
    sf::Texture background;
    sf::Sprite backgroundSprite;
    std::vector<bullet> invaderBullets;
    sf::Clock clock;
    bool invaderShooting;
    sf::VideoMode desktop;
    sf::Vector2u windowSize;
    sf::Vector2u textureSize;
    std::future<void> invaderMovementFuture;
    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarBackground;
    bool playerWon;
public:
    player playerOfGame;
    menu mainMenu;
    menu pauseMenu;
    level level_;
    int score;
    sf::RenderWindow gameWindow;
    sf::Event event;
    std::string playerNickname;
    bool isAnyKeyPressed();
    void playerBorders();
    void mainLoop();
    void startGame();
    void hurtingInvaders(sf::Time&);
    void invadersShooting(sf::Time&);
    void playerMoving();
    void updateInvadersMovement(float);
    gameState currentGameState;
    void updateHealthBar();
    game()
        :gameWindow(sf::VideoMode(512, 512), "Space Invaders"), mainMenu(512, 512) {
        desktop = sf::VideoMode::getDesktopMode();
        background.loadFromFile("background2.png");
        sf::Vector2u windowSize = gameWindow.getSize();
        sf::Vector2u textureSize = background.getSize();
        backgroundSprite.setTexture(background);
        backgroundSprite.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));
        currentGameState = gameState::MainMenu;
        healthBarBackground.setSize(sf::Vector2f(200.0f, 20.0f));
        healthBarBackground.setFillColor(sf::Color::Magenta);
        healthBarBackground.setPosition(10.0f, 10.0f);
        healthBar.setSize(sf::Vector2f(200.0f, 20.0f));
        healthBar.setFillColor(sf::Color::Blue);
        healthBar.setPosition(10.0f, 10.0f);
        playerNickname = "Mery";
        score = 0;
        mainMenu.highScoresInMenu.loadScores(".\\scores\\high_scores.txt");
    }
};

#endif

