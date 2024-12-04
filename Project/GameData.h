#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <iostream>

class GameData {
private:
    GameData();

    GameData(GameData const&) = delete;
    void operator=(GameData const&) = delete;

    int score;
    int combo;
    bool isCombo;
public:
    static GameData& getInstance();
   
    int getScore() const;
    void setScore(int newScore);
    bool getCombo() const;
    int getComboPoint() const;
    void setCombo();
    void doneCombo();
    void reset();
};

#endif 
