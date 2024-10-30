#include "menu.h"
#include "game.h"
#include "Windows.h"
menu::menu(float width, float height) {
    if (!font.loadFromFile("NovaSlim-Regular.ttf")) {
        std::cout << "Cannot load font file :(" << std::endl;
    }
    else {
        std::cout << "Font file loaded :)" << std::endl;
    }
    if (backgroundTexture.loadFromFile("options-background.png") ){
        std::cout << "Cannot load background file :(" << std::endl;
    }
    else {
        std::cout << "Background file loaded :)" << std::endl;
    }
}
void menu::initMenuItems(int width, int height) {
    selectedItemIndex = 0;
    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setFillColor(selectedItemIndex == i ? sf::Color::Magenta : sf::Color::White);
        text.setString(items[i]);
        text.setPosition(sf::Vector2f(width / 2.0f - text.getGlobalBounds().width / 2.0f, height / (items.size() + 1) * (i + 1)));
        text.setCharacterSize(30);
        menuItems.push_back(text);
    }
    
}
void menu::draw(sf::RenderWindow& window) {
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}
void menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Magenta);
        std::cout << "Move up, new index: " << selectedItemIndex << std::endl;
    }
}
void menu::moveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Magenta);
        std::cout << "Move down, new index: " << selectedItemIndex << std::endl;
    }
}
int menu::getSelectedItem() const {
    return selectedItemIndex;
}
void menu::displayHighScores(game& SpaceInvaders) const {
    highScores& mutableHighScoresInMenu = const_cast<highScores&>(highScoresInMenu);
    mutableHighScoresInMenu.loadScores("scores/high_scores.txt");
    sf::Font font;
    if (!font.loadFromFile("NovaSlim-Regular.ttf")) {
        std::cout << "Failed to load font file." << std::endl;
        return;
    }
    std::vector<std::pair<std::string, int>> topScores = mutableHighScoresInMenu.getTopScores(10);

    sf::Text scoresText;
    scoresText.setFont(font);
    scoresText.setCharacterSize(24);
    scoresText.setFillColor(sf::Color::Yellow);
    scoresText.setPosition(100, 100);

    std::string scoresDisplay = "Top 10 High Scores:\n";
    for (size_t i = 0; i < topScores.size(); ++i) {
        scoresDisplay += std::to_string(i + 1) + ". " + topScores[i].first + ": " + std::to_string(topScores[i].second) + "\n";
    }
    scoresText.setString(scoresDisplay);

    bool exitHighScores = false;
    while (SpaceInvaders.gameWindow.isOpen() && !exitHighScores) {
        sf::Event event;
        while (SpaceInvaders.gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                SpaceInvaders.gameWindow.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    SpaceInvaders.currentGameState = gameState::Options;
                    exitHighScores = true;
                }
            }
        }
        SpaceInvaders.gameWindow.clear();
        SpaceInvaders.gameWindow.draw(scoresText);
        SpaceInvaders.gameWindow.display();
    }
    SpaceInvaders.currentGameState = gameState::MainMenu;
}

void menu::changeDifficulty(game& SpaceInvaders) {
    std::vector<std::string> difficulties = { "Easy", "Medium", "Hard" };
    while (SpaceInvaders.gameWindow.isOpen()) {
        sf::Event event;
        while (SpaceInvaders.gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                SpaceInvaders.gameWindow.close();
            }
            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) {
                    selectedItemIndex = (selectedItemIndex - 1 + difficulties.size()) % difficulties.size();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    selectedItemIndex = (selectedItemIndex + 1) % difficulties.size();
                }
                else if (event.key.code == sf::Keyboard::Return) {
                    switch (selectedItemIndex) {
                    case 0:
                        for (auto el : SpaceInvaders.level_.invaders) {
                            el.entityBullet.velocity = sf::Vector2f(0.f, 0.025f);
                        }
                        break;
                    case 1:
                        for (auto el : SpaceInvaders.level_.invaders) {
                            el.entityBullet.velocity = sf::Vector2f(0.f, 0.125f);
                        }
                        break;
                    case 2:
                        for (auto el : SpaceInvaders.level_.invaders) {
                            el.entityBullet.velocity = sf::Vector2f(0.f, 0.325f);
                        }
                        break;
                    }
                    return;
                }
            }
        }
        SpaceInvaders.gameWindow.clear();
        sf::Font font;
        if (!font.loadFromFile("NovaSlim-Regular.ttf")) {
        }
        sf::Text title("Choose Difficulty", font, 30);
        title.setPosition(100, 50);
        SpaceInvaders.gameWindow.draw(title);
        for (size_t i = 0; i < difficulties.size(); ++i) {
            sf::Text text(difficulties[i], font, 24);
            text.setPosition(100, 150 + i * 50);
            if (i == selectedItemIndex) {
                text.setFillColor(sf::Color::Magenta);
            }
            SpaceInvaders.gameWindow.draw(text);
        }

        SpaceInvaders.gameWindow.display();
    }
    selectedItemIndex = 0;
}
void menu::mainMenu(game& SpaceInvaders) {
    SpaceInvaders.gameWindow.clear();
    items.clear();
    menuItems.clear();
    items = { "Start Game", "High Scores", "Options", "Exit" };
    sf::Text gameTitle("Space Invaders", font, 50); 
    gameTitle.setPosition(sf::Vector2f(512 / 2.0f - gameTitle.getGlobalBounds().width / 2.0f, 512 / (items.size() + 1) - 90));
    
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    initMenuItems(512, 512);

    while (SpaceInvaders.gameWindow.isOpen() && SpaceInvaders.currentGameState == gameState::MainMenu) {
        sf::Event event;
        while (SpaceInvaders.gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                SpaceInvaders.currentGameState = gameState::Exit;
            }
            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) {
                    moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    moveDown();
                }
                else if (event.key.code == sf::Keyboard::Return) {
                    int selectedItem = getSelectedItem();
                    switch (selectedItem) {
                    case 0:
                        SpaceInvaders.currentGameState = gameState::Playing;
                        break;
                    case 1:
                        SpaceInvaders.currentGameState = gameState::HighScores;
                        break;
                    case 2:
                        SpaceInvaders.currentGameState = gameState::Options;
                        break;
                    case 3:
                        SpaceInvaders.currentGameState = gameState::Exit;
                        break;
                    }
                }
            }
        }

        SpaceInvaders.gameWindow.draw(backgroundSprite);
        SpaceInvaders.gameWindow.draw(gameTitle);
        draw(SpaceInvaders.gameWindow);
        SpaceInvaders.gameWindow.display();
    }
}
void menu::changeNickname(game& SpaceInvaders) {
    std::string newNickname;
    bool enteringNickname = true;
    sf::Text nicknameText;
    sf::Font font;
    
    if (!font.loadFromFile("NovaSlim-Regular.ttf")) {
        std::cout << ":(" << std::endl;
    }
    nicknameText.setFont(font);
    nicknameText.setCharacterSize(24);
    nicknameText.setFillColor(sf::Color::White);
    nicknameText.setPosition(100, 100);
    std::regex nicknameRegex("^[a-zA-Z0-9]+$");
    bool exitChangeNickname = false;
    std::string displayedText = "Enter new nickname: ";
    while (SpaceInvaders.gameWindow.isOpen() && enteringNickname) {
        
        sf::Event event;
        while (SpaceInvaders.gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                SpaceInvaders.gameWindow.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b') {
                        if (!newNickname.empty()) {
                            newNickname.pop_back();
                        }
                    }
                    else if (event.text.unicode == '\r') {
                        if (std::regex_match(newNickname, nicknameRegex)) {
                            SpaceInvaders.playerNickname = newNickname;
                            std::cout << SpaceInvaders.playerNickname << std::endl;
                            enteringNickname = false;
                            while (event.type != sf::Event::KeyReleased || event.key.code != sf::Keyboard::Return) {
                                SpaceInvaders.gameWindow.pollEvent(event);
                            }
                            SpaceInvaders.currentGameState = gameState::Options;
                            return;
                        }
                        else {
                            newNickname.clear();
                            displayedText = "Invalid nickname! \nEnter new nickname: ";

                        }
                        
                    }
                    else {
                        newNickname += static_cast<char>(event.text.unicode);
                    }

                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    enteringNickname = false;
                    SpaceInvaders.currentGameState = gameState::Options;
                    exitChangeNickname = true;
                }
            }
        }

       nicknameText.setString(displayedText+newNickname);
        SpaceInvaders.gameWindow.clear();
        SpaceInvaders.gameWindow.draw(nicknameText);
        SpaceInvaders.gameWindow.display();
    }
    return;
}
void menu::optionsMenu(game& SpaceInvaders) {
    items = { "Game difficulty", "Change nickname", "Back to main menu" };
    initMenuItems(512, 512);
    while (SpaceInvaders.gameWindow.isOpen() && SpaceInvaders.currentGameState == gameState::Options) {
        sf::Event event;
        while (SpaceInvaders.gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                SpaceInvaders.gameWindow.close();
            }
            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) {
                    moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    moveDown();
                }
                else if (event.key.code == sf::Keyboard::Return) {
                    int selectedItem = getSelectedItem();
                    if (selectedItem == 0) {

                        changeDifficulty(SpaceInvaders);
                    }
                    else if (selectedItem == 1) {
                        SpaceInvaders.currentGameState = gameState::ChangeNickname;
                        changeNickname(SpaceInvaders);
                    }
                    else if (selectedItem == 2) {
                        SpaceInvaders.currentGameState = gameState::MainMenu;
                        items.clear();
                        menuItems.clear();
                        return;
                    }
                }
            }
        }
        SpaceInvaders.gameWindow.clear();
        draw(SpaceInvaders.gameWindow);
        SpaceInvaders.gameWindow.display();
    }
}
void menu::gameOver(game& SpaceInvaders, bool playerWon) {
    sf::Font font;
    if (!font.loadFromFile("NovaSlim-Regular.ttf")) {
        std::cout << "Failed to load font file." << std::endl;
        return;
    }

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(36);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(100, 100);

    sf::Color backgroundColor;
    std::string gameOverMessage;

    if (playerWon) {
        backgroundColor = sf::Color::Green;
        gameOverMessage = "Congratulations! You Won!\nPress ESC to exit\nto main menu.";
    }
    else {
        backgroundColor = sf::Color::Red;
        gameOverMessage = "Game Over! You Lost.\nPress ESC to exit\nto main menu.";
    }

    sf::RectangleShape backgroundRect(sf::Vector2f(512, 512));
    backgroundRect.setFillColor(backgroundColor);

    gameOverText.setString(gameOverMessage);
    gameOverText.setPosition(512 / 2.0f - gameOverText.getGlobalBounds().width / 2.0f, 256);

    while (SpaceInvaders.gameWindow.isOpen()) {
        sf::Event event;
        while (SpaceInvaders.gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                SpaceInvaders.gameWindow.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    SpaceInvaders.mainMenu.highScoresInMenu.addScore(SpaceInvaders.playerNickname, SpaceInvaders.score);
                    SpaceInvaders.mainMenu.highScoresInMenu.saveScores(".\\scores\\high_scores.txt");
                    SpaceInvaders.currentGameState = gameState::MainMenu;
                    SpaceInvaders.playerOfGame.isDead = false;
                    SpaceInvaders.playerOfGame.health = SpaceInvaders.playerOfGame.getMaxHealth();
                    SpaceInvaders.playerOfGame.sprite.setPosition(256 - SpaceInvaders.playerOfGame.sprite.getGlobalBounds().width, 512);
                    SpaceInvaders.playerOfGame.bullets.clear();
                    SpaceInvaders.level_.invaders.clear();
                    SpaceInvaders.level_.levelNumber = 1;
                    SpaceInvaders.level_.initLevel();
                    SpaceInvaders.score = 0;
                    SpaceInvaders.startGame();
                    return;
                }
            }
        }

        SpaceInvaders.gameWindow.clear();
        SpaceInvaders.gameWindow.draw(backgroundRect);
        SpaceInvaders.gameWindow.draw(gameOverText);
        SpaceInvaders.gameWindow.display();
    }
}
void menu::manageMenus(game& SpaceInvaders) {
    while (SpaceInvaders.gameWindow.isOpen()) {
        SpaceInvaders.gameWindow.clear();
        switch (SpaceInvaders.currentGameState) {
        case gameState::MainMenu: {
            mainMenu(SpaceInvaders);
            break;
        }
        case gameState::Options: {
            items.clear();
            menuItems.clear();
            optionsMenu(SpaceInvaders);
            break;
        }
        case gameState::HighScores:
            displayHighScores(SpaceInvaders);
            break;
        case gameState::Playing:
            SpaceInvaders.mainLoop();
            break;
        case gameState::Exit:
            SpaceInvaders.gameWindow.close();
            break;
        default:
            break;
        }
        SpaceInvaders.gameWindow.display();
    }
}