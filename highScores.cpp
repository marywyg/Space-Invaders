#include "highScores.h"

void highScores::loadScores(const std::string& filePath) {
    listOfHighScores.clear(); 
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Failed to open high scores file: " << filePath << std::endl;
        return;
    }

    std::string playerName;
    int score;
    while (file >> playerName >> score) {
        listOfHighScores.emplace(playerName, score);
    }

    file.close();
    std::cout << "Loaded high scores from file: " << filePath << std::endl;
}

void highScores::saveScores(const std::string& filePath) const {
    std::filesystem::path savePath = std::filesystem::path(filePath).parent_path();
    if (!std::filesystem::exists(savePath)) {
        std::filesystem::create_directory(savePath);
    }

    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Failed to open high scores file for saving: " << filePath << std::endl;
        return;
    }

    for (const auto& entry : listOfHighScores) {
        file << entry.first << " " << entry.second << std::endl;
    }

    file.close();
    std::cout << "Saved high scores to file: " << filePath << std::endl;
}

void highScores::addScore(const std::string& playerNickname, int score) {
    listOfHighScores.emplace(playerNickname, score);
}

std::vector<std::pair<std::string, int>> highScores::getTopScores(size_t count) const {
    std::vector<std::pair<std::string, int>> scores(listOfHighScores.begin(), listOfHighScores.end());

    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
        });

    if (scores.size() > count) {
        scores.resize(count);
    }

    return scores;
}