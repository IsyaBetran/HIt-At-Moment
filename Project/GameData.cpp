#include "GameData.h"

GameData::GameData() : score(0), combo(0), isCombo(false) { }

GameData& GameData::getInstance() {
    static GameData instance;
    return instance;
}

int GameData::getScore() const {
    return score;
}

void GameData::setScore(int addScore) {
    score += addScore;
    if (combo > 1) {
        score += 10;
    }
    std::cout << score << std::endl;
}

bool GameData::getCombo() const {
    return isCombo;
}

int GameData::getComboPoint() const {
    return combo;
}

void GameData::setCombo() {
    combo++;
    isCombo = true;
}

void GameData::doneCombo() {
    isCombo = false;
    combo = 0;
}

void GameData::reset() {
    std::cout << score << std::endl;
    score = 0;
    combo = 0;
}
