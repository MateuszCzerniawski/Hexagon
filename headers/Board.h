//
// Created by PC on 15.05.2023.
//

#ifndef PROJECT1ALPHA1_BOARD_H
#define PROJECT1ALPHA1_BOARD_H
#include <vector>
#include <string>
#include <fstream>
using namespace std;

/**
 * Klasa służy do zapisania planszy jako model danych.
 * Wszystkie istotne informacje znajdują się w polu data.
 */
class Board {
    /**
     * zapisuje wygląd planszy w formie linii tekstu
     */
    vector<string> textData;
public:
    /**
     * Struktura odpowiada za reprezentację pola na planszy.
     * Opisuje zarówno miejsce (koordynat) jak i co się na nim znajduje.
     */
    struct Field{
    private:
        int coordinate;
        char whoHere;
    public:
        Field(int coordinate,char whoHere);
        /**
         * gettery i settery dla pól
         */
        int getCoordinate() const;
        char getWhoHere() const;
        void setWhoHere(char whoHere);
    };
    /**
     * Konstruktor tworzy obiekt i wywołuje funkcje potrebne do załadowania pól
     */
    Board();
    ~Board();
    /**
     * wczytuje z pliku board.txt dane do pól i wstawia pionki graczy w pozycji startowej
     */
    void load();
    /**
     * loadSave pobiera  strumień (fstream& in), odczytuje dane
     * a następnie na ich podstawie (string line) uzupełnia dane w data
     * UWAGA: loadSave służy do nadpisywania Board a nie do tworzenia nowego
     */
    void loadSave(fstream& in);
    void loadSave(string line);
    /**
     * Pobiera strumień do którego przekazywane będą dane,
     * następnie zapisuje pole data w formie tekstowej
     *
     */
    void save(fstream& out);
    /**
     * Wypisuje na konsonlę współrzędne wszystkich pól planszy
     */
    void showCoordinates();
    /**
     * Zlicza zadany znak w data,
     * służy głównie do określania ilości pionków graczy
     */
    int count( const char& toCount);
    /**
     * getter pola data
     */
    const vector<Field *> &getData() const;

private:
    /**
     * Najważniejsze pole tej klasy,
     * przchowuje dokładne dane o planszy
     */
    vector<Field*> data; //koniecznie ze wskaźnikiem, inaczej nie wykorzystamy new
};


#endif //PROJECT1ALPHA1_BOARD_H
