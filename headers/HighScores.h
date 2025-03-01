//
// Created by PC on 25.05.2023.
//

#ifndef PROJECT1ALPHA4_HIGHSCORES_H
#define PROJECT1ALPHA4_HIGHSCORES_H
#include "Board.h"
#include "GraphicsParameters.h"
#include "SFML/Graphics.hpp"
/**
 * Klasa intepretująca recordy w pliku scores.txt jako plansze gry
 * i pozwalaca wyciągnąć najwążniejsze dane do wyrysowania panelu HighScores
 */
class HighScores {
    /**
     * Pola niezbędne do fuknjonowania HighScores
     */
    vector<Board*> records;
    Board* current;
    GraphicsParameters* parameters;

public:
    /**
     * Konstruktor inicjujący obiekt
     */
    HighScores(Board* current,GraphicsParameters* parameters);
    ~HighScores();
    /**
     * Gettery pozwalające określić na podstawie recordów z pliku
     * jak powinny być prezentowane wyniki dla każdego z 5 najlepszych wyników
     */
    sf::Color getColor(int which);
    std::string getText(int which);
    std::string getTexture(int which);
    /**
     * Zapisuje ukończoną grę do pliku
     */
    void saveNewScore();
    /**
     * Gettery zwracające parę liczb (wynik gracza1 , wynik gracza 2)
     * na podstawie numeru z pola records albo odnośnika do konkretnego Board
     */
    pair<int,int> getScores(int which);
    pair<int,int> getScores(Board* board);
};


#endif //PROJECT1ALPHA4_HIGHSCORES_H
