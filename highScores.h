#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include <iostream>
#include <list>
#include <unordered_map>
#include <regex>
#include <filesystem>
#include <fstream> 
class highScores {
public:
    std::unordered_multimap<std::string, int> listOfHighScores;
    void loadScores(const std::string& filePath);
    void saveScores(const std::string& filePath) const;
    void addScore(const std::string& playerNickname, int score);
    std::vector<std::pair<std::string, int>> getTopScores(size_t count) const;
};

#endif
