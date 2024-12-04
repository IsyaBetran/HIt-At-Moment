#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <string>
#include <vector>

class HighScoreManager {
private:
    std::string filePath;
    std::vector<int> highScores;

    void loadHighScores();
    void saveHighScores();

public:
    HighScoreManager(const std::string& file);
    const std::vector<int>& getHighScores() const;
    bool updateHighScores(int newScore);
    void LoadAgain();
};

#endif
