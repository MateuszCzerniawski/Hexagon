//
// Created by PC on 22.05.2023.
//

#ifndef PROJECT1ALPHA2_ROBOT_H
#define PROJECT1ALPHA2_ROBOT_H
#include "Board.h"
#include "Display.h"
#include <map>
/**
 * Klasa definiująca AI do gry przeciwko komputerowi
 */
class Robot {
    /**
     * Struktura definiująca możliwe do wykonania ruchy.
     * Określa z jakiego pola jest wykonywane, gdzie i jaki jest z takiego ruchu zysk
     */
    struct Move{
        int from;
        int to;
        int benefit;
        Move();
        Move(int from, int to, int benefit);
        void setFrom(int from);
        void setTo(int to);
        void setBenefit(int benefit);
    };
    /**
     * Dane rozgrywki dla AI (board) i interpretacja graficzna (display) do znajdowania sąsiednich pól
     */
    Board* board;
    Display* display;
    /**
     * Funkcja zwracająca ile pionków zyska AI gdy wykona ruch w dane miejsce
     */
    int calculateBenefit(const int& where);
    /**
     * Funkcja analizująca wszystkie możliwe di wykonania ruchy
     * Przedstawia je w formie skąd -> (dokąd, jaki z tego zysk)
     */
    map< int ,map<int,int>  > analize();
    /**
     * Na podstawie wyniku funkcji analize(), określa najlepsze posunięcie w danej turze
     */
    Move findBestMove( const map< int ,map<int,int>  >& options);
    /**
     * Określa jaki jest najwieszy możliwy zysk dla wykonania ruchu z pola o koordynacie from
     */
    Move getMaxBenefit(int from,map<int,int> options);
    /**
     * Umożliwia AI propagowanie swoich pionków, gdy nie można uzyskać pionków kosztem przeciwnika
     */
    void propagate();
public:
    /**
     * Konstruktor aktywujący AI i informujący je argumentami o rozgrywce
     */
    Robot(Board* board, Display* display);
    ~Robot();
    /**
     * Funckja wykonująca ruch AI w jej turze
     */
    void makeMove();
};


#endif //PROJECT1ALPHA2_ROBOT_H
