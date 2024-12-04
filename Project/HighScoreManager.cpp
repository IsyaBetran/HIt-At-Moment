#include "HighScoreManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>

HighScoreManager::HighScoreManager(const std::string& file) : filePath(file) {
    loadHighScores();
}

void HighScoreManager::loadHighScores() {
    highScores.clear();
    std::ifstream inFile(filePath);

    if (inFile.is_open()) {
        int score;
        while (inFile >> score) {
            highScores.push_back(score);
        }
        inFile.close();
    }

 
    while (highScores.size() < 5) {
        highScores.push_back(0);
    }

    std::sort(highScores.rbegin(), highScores.rend());
}

void HighScoreManager::saveHighScores() {
    std::ofstream outFile(filePath);

    if (outFile.is_open()) {
        for (int score : highScores) {
            outFile << score << std::endl;
        }
        outFile.close();
    }
    else {
        std::cerr << "Error: Unable to write to file." << std::endl;
    }
}

const std::vector<int>& HighScoreManager::getHighScores() const {
    return highScores;
}

bool HighScoreManager::updateHighScores(int newScore) {
    highScores.push_back(newScore);
    std::sort(highScores.rbegin(), highScores.rend());
    if (highScores.size() > 5) {
        highScores.pop_back();
    }

    saveHighScores();
    return (std::find(highScores.begin(), highScores.end(), newScore) != highScores.end());
}

void HighScoreManager::LoadAgain() {
    loadHighScores();
}