//
// Created by PC on 18.05.2023.
//

#ifndef PROJECT1ALPHA2_GAME_H
#define PROJECT1ALPHA2_GAME_H
#include "Display.h"
#include "Board.h"
#include "Robot.h"
#include <set>
/**
 * enum z możliwymi trybami gry
 */
enum Turn{MENU,PLAYER1,PLAYER2,RESULTS,HIGHSCORES};
/**
 * Klasa stanowiąca kontroller wyświetlania, edycji modelu danych
 * i ( w razie potrzeby) aktywująca AI z trybu gry z komputerem
 */
class Game {
    /**
     * odnośniki do modelu danych, grafiki i sztucznej inteligencji
     */
    Board* board;
    GraphicsParameters* parameters;
    Display* display;
    Robot* robot;
    /**
     * określa w jakim trybie znajduje się gra
     */
    Turn turn;
    /**
     * Przechowuje koordynat ostatniego wybranego pola.
     * Służy wyłącznie do implementacji przeskoku o 2 pola
     */
    int recentSelected;
    /**
     * bool-e parametryzujące jaką opcję wybrać z menu
     */
    bool enableRobot, triggerHighscore,loadFromSave;
public:
    /**
     * Tworzy grę oraz wszystkie niezbędne do jej funkcjonowania obiekty
     */
    Game();
    ~Game();
    /**
     * Funkcja odpowiadajaca za życie gry
     */
    void run();
private:
    /**
     * Czyści z modelu danych zaznaczenie pola
     */
    void clearSelection();
    /**
     * Określa, jak gra ma się zachować przy kliknięciu gracza na przycisk
     */
    void reactToClick(int which);
    /**
     * Funkcja kończąca rozgrywkę i przełączająca grę w tryb wyświetlania podsumowania
     */
    void close();
    /**
     * Zwraca zbiór koordynatów pól, na które w danej turze gracz może przesunąć pionek
     */
    set<int> posMoves();
    /**
     * Określa czy gracz w danej turze ma możliwy jakiś ruch
     * Stanowi podstawę do zakończenia rozgrywki
     */
    bool havePosMove();
    /**
     * Funkcja realizująca funkcjonalność przejmowania pionkó przeciwnika
     */
    void dominate(set<int> neighbours);
    /**
     * Funkja określająca jaki tryb wyświetlania dla Display ma zostać zastosowany
     */
    int deduceMode();
    /**
     * Zapisuje grę do pliku save.txt
     */
    void save();
    /**
     * Realizuje przejście z powrotem do menu
     */
    void backToMenu();
};


#endif //PROJECT1ALPHA2_GAME_H
