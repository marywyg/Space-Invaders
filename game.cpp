
#include "game.h"
#include "menu.h"
void game::updateHealthBar() {
    float healthPercent = static_cast<float> (playerOfGame.getHealth())/playerOfGame.getMaxHealth();
    playerOfGame.manager.playerHealthBar.setSize(sf::Vector2f(300.f * healthPercent, playerOfGame.manager.playerHealthBar.getSize().y));
}
void game::playerMoving() {
    while (gameWindow.isOpen()) {
        playerOfGame.moveDown();
        playerOfGame.moveUp();
        playerOfGame.moveLeft();
        playerOfGame.moveRight();
    }
}
bool game::isAnyKeyPressed()
{
    for (int k = -1; k < sf::Keyboard::KeyCount; ++k)
    {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
            return true;
    }
    return false;
}
void game::playerBorders() {
    if (playerOfGame.sprite.getPosition().x < 0)
    {
        playerOfGame.sprite.setPosition(0, playerOfGame.sprite.getPosition().y);
        playerOfGame.velocity = { 0.f, 0.f };
        playerOfGame.acceleration = { 0.f, 0.f };
    }
    else if (playerOfGame.sprite.getPosition().x > backgroundSprite.getGlobalBounds().width - playerOfGame.sprite.getGlobalBounds().width)
    {
        playerOfGame.sprite.setPosition(backgroundSprite.getGlobalBounds().width - playerOfGame.sprite.getGlobalBounds().width, playerOfGame.sprite.getPosition().y);
        playerOfGame.velocity = { 0.f, 0.f };
        playerOfGame.acceleration = { 0.f, 0.f };
    }
    if (playerOfGame.sprite.getPosition().y < 0)
    {
        playerOfGame.sprite.setPosition(playerOfGame.sprite.getPosition().x, 0);
        playerOfGame.velocity = { 0.f, 0.f };
        playerOfGame.acceleration = { 0.f, 0.f };
    }
    else if (playerOfGame.sprite.getPosition().y > backgroundSprite.getGlobalBounds().height - playerOfGame.sprite.getGlobalBounds().height)
    {
        playerOfGame.sprite.setPosition(playerOfGame.sprite.getPosition().x, backgroundSprite.getGlobalBounds().height - playerOfGame.sprite.getGlobalBounds().height);
        playerOfGame.velocity = { 0.f, 0.f };
        playerOfGame.acceleration = { 0.f, 0.f };
    }
    return;
}
void game::hurtingInvaders(sf::Time& time) {
    playerOfGame.fireBullet(time);
    for (auto it = playerOfGame.bullets.begin(); it != playerOfGame.bullets.end();) {
        bool hitInvader = false;
        for (auto& el : level_.invaders) {
            if (it->sprite.getGlobalBounds().intersects(el.sprite.getGlobalBounds()) && !el.isDead) {
                el.health -= 20;
                hitInvader = true;
                it = playerOfGame.bullets.erase(it);
                score += 25;
                break;
            }
        }
        if (!hitInvader) {
            ++it;
        }
    }
}
void game::invadersShooting(sf::Time& time) {
    if (level_.invaders.empty()) {
        return;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> invaderIndex(0, level_.invaders.size() - 1);
    int selectedInvaderIndex = invaderIndex(gen);
    bool hitPlayer = false;
    if (!level_.invaders[selectedInvaderIndex].isDead && level_.invaders[selectedInvaderIndex].shotClock.getElapsedTime() >= level_.invaders[selectedInvaderIndex].shotInterval) {
        level_.invaders[selectedInvaderIndex].shotClock.restart();
        std::uniform_int_distribution<> shootChance(0, 1);
        if (shootChance(gen) == 0) {
            bullet newBullet = level_.invaders[selectedInvaderIndex].entityBullet;
            newBullet.sprite.setPosition(
                level_.invaders[selectedInvaderIndex].sprite.getPosition().x + level_.invaders[selectedInvaderIndex].sprite.getGlobalBounds().width / 2 - newBullet.sprite.getGlobalBounds().width / 2,
                level_.invaders[selectedInvaderIndex].sprite.getPosition().y + level_.invaders[selectedInvaderIndex].sprite.getGlobalBounds().height
            );

            invaderBullets.push_back(newBullet);
        }
    }
    auto visibleBullets = invaderBullets | std::views::filter([](const bullet& b) {
        return b.sprite.getPosition().y <= 512;
        });
    for (auto& b : visibleBullets) {
        b.sprite.move(b.velocity);
        b.bulletAnimation(time.asSeconds());
    }

    for (auto it = invaderBullets.begin(); it != invaderBullets.end();) {
        it->sprite.move(it->velocity);
        it->bulletAnimation(time.asSeconds());

        if (it->sprite.getGlobalBounds().intersects(playerOfGame.sprite.getGlobalBounds())) {
            playerOfGame.health -= 20;
            it = invaderBullets.erase(it);
        }
        else {
            ++it;
        }
    }
    level_.invaders[selectedInvaderIndex].shotInterval = level_.invaders[selectedInvaderIndex].shootingIntervalGenerator(sf::seconds(1), sf::seconds(10));
}
void game::updateInvadersMovement(float deltaTime) {

    bool changeDirection = false;

    for (auto& invader : level_.invaders) {
        if (invader.moveLeft) {
            invader.sprite.move(-invader.velocityX * deltaTime, 0.f);
            if (invader.sprite.getPosition().x < 0) {
                changeDirection = true;
            }
        }
        else {
            invader.sprite.move(invader.velocityX * deltaTime, 0.f);
            if (invader.sprite.getPosition().x + invader.sprite.getGlobalBounds().width > backgroundSprite.getGlobalBounds().width) {
                changeDirection = true;
            }
        }
    }

    if (changeDirection) {
        for (auto& invader : level_.invaders) {
            invader.moveLeft = !invader.moveLeft;

            if (invader.moveLeft) {
                invader.sprite.move(0.1f, invader.sprite.getGlobalBounds().height);
            }
            else if(!invader.isDead){
                invader.sprite.move(0.1f, invader.sprite.getGlobalBounds().height);
            }
            if (invader.sprite.getPosition().y + invader.sprite.getGlobalBounds().height >= backgroundSprite.getGlobalBounds().height) {
                playerWon = false;
                mainMenu.gameOver(*this, playerWon);
            }
        }
    }
}

void game::mainLoop() {
    while (gameWindow.isOpen()) {
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
        }
        sf::Time time = clock.restart();
        invadersShooting(time);
        playerOfGame.moveLeft();
        playerOfGame.moveRight();
        playerOfGame.moveUp();
        playerOfGame.moveDown();
        updateHealthBar();
        playerBorders();
        hurtingInvaders(time);
        updateInvadersMovement(time.asSeconds());
        playerOfGame.sprite.move(playerOfGame.velocity * playerOfGame.speedMultiplier);
        gameWindow.draw(backgroundSprite);

        if (!level_.levelFinished && std::all_of(level_.invaders.begin(), level_.invaders.end(), [](const invader& inv) { return inv.isDead; })) {
            level_.levelFinished = true;
            if (level_.levelNumber == 2 && level_.levelFinished && !playerOfGame.isDead) {
                playerWon = true;
                mainMenu.gameOver(*this, playerWon);
            }
            level_.levelNumber++;
            std::cout << level_.levelNumber << std::endl;
            level_.initLevel();
        }
        for (auto& el : level_.invaders) {
            if (el.health < 1) {
                el.isDead = true;
                playerWon = false;
            }
            else {
                gameWindow.draw(el.sprite);
            }

        }
        auto visibleBullets = invaderBullets | std::views::filter([](const bullet& b) {
            return b.sprite.getPosition().y <= 512;
            });
        for (const auto& bullet : playerOfGame.bullets) {
            gameWindow.draw(bullet.sprite);
            
        }
        for (const auto& bullet : visibleBullets) {
            gameWindow.draw(bullet.sprite);
        }
        if (playerOfGame.health <= 0 && !playerOfGame.isDead) {
            playerOfGame.isDead = true;
            mainMenu.gameOver(*this, playerWon);
        }
        
        gameWindow.draw(playerOfGame.sprite);
        gameWindow.draw(playerOfGame.manager.playerHealthBarBack);
        gameWindow.draw(playerOfGame.manager.playerHealthBar);
        gameWindow.display();
    }

}
void game::startGame() {
    std::cout << "Starting game :)" << std::endl;
    mainMenu.manageMenus(*this);
}