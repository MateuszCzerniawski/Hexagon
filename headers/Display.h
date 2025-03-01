//
// Created by PC on 18.05.2023.
//

#ifndef PROJECT1ALPHA2_DISPLAY_H
#define PROJECT1ALPHA2_DISPLAY_H
#include <iostream>
#include "Board.h"
#include "SFML/Graphics.hpp"
#include <map>
#include <set>
#include "GraphicsParameters.h"
#include "HighScores.h"
/**
 * enum określający wybraną opcję w menu
 */
enum menuOption{HUMAN,ROBOT,SCORES,SAVED};
/**
 * Klasa odpowiadająca w pełni za wyświatlaną grafikę, czyli:
 * okno, plansza, wyniki, przyciski, napisy
 */
class Display {
    /**
     * Obiekty niezbędne do życia gry
     */
    Board* board;
    HighScores* highScores;
    sf::RenderWindow* window;
    vector<sf::CircleShape>* buttons;
    /**
     * Struktura odpowiadająca za wyświetlanie wyników w czasie gry
     */
    struct Score{
        sf::CircleShape* displayField;
        sf::Font font;
        sf::Text* text;
        int value,player;
        float scale;
        Display* display;
    public:
        /**
         * Kostruktor inicjujący strukturę Score
         * UWAGA: Użycie samego konstruktora nie da w pełni funkcjonalnego wyświetlacza,
         * należy korzystać z funkcji update, draw czy highlight
         */
        Score(Display* display,sf::Font font,float scale,int player);
        /**
         * Wyrysowuje wyswietlacz w miejscu określonym przez argumenty x i y
         */
        void draw(const float& x, const float& y);
        /**
         * Podmienia obecny tekst na tekstowy odpowiednik argumentu value
         */
        void update(const int value);
        /**
         * Na podstawie argumentu enabled, określa czy należy dodatkowo wyrysowywać obramowanie
         */
        void highLight(bool enabled);
        ~Score();
    };
    /**
     * Wyniki i komunikaty podczas gry
     */
    sf::Font arial;
public:
    /**
     * Parametry graficzne oraz wyświetlacze wyników
     */
    GraphicsParameters* parameters;
    Score* score1;
    Score* score2;
public:
    /**
     * Konstruktor tworzący okno i łączący wyświetlaną grę z modelem danych Board
     */
    Display(Board* board,GraphicsParameters* parameters);
    ~Display();
    /**
     * Funkja wyświetlająca pole na planszy i tworząca przycisk
     * Ponadto wyrysowuje odpowiednie assety
     */
    void addSingleHexagon(float x,float y);
    /**
     * Za pomocą parametrów graficznych i funkji addSingleHexagon,
     * wyrysowuje wszystkie pola planszy
     */
    void addHexagons();
    /**
     * Na podstawie argumentu mode, wyświetla stosowne części interfejsu graficznego
     * Służy do reagowania na zmiany zarządzone przez grę
     */
    void refresh(int mode);
    /**
     * Wyszukuje wszystkich sąsiadów pola planszy o koordynacie which,
     * zwracając dane w formie mapy (pole odległe o 1 -> zbiór pól odległych o 2)
     */
    map<int , set<int> > findNeighbours(int which); //z jakiegoś powodu nie działa funkcja contains i trzeba było pisać własną
    /**
     * Wyszukuje i zwraca zbiór wszystkich najbliższych sąsiadów pola planszy o koordynacie which
     */
    set<int> findNearestNeighbours(int which);
    /**
     * gettery i settery
     */
    sf::RenderWindow *getWindow() const;
    vector<sf::CircleShape> *getButtons() const;
    void setBoard(Board *board);
    HighScores *getHighScores() const;

private:
    /**
     * Alternatywa dla sfml-owej funkji contains
     */
    bool within(sf::Vector2f& here,sf::Rect<float>& button);
    /**
     * Wyszukuje i zwraca zbiór pól planszy odległych od which o 1 (bliskich sąsiadów)
     * argument lock służy do wyeliminowania konkretnego pola (zastowanie przy znajdowaniu sąsiadów odległych o 2 pola)
     */
    set<int> findDistantNeighbours(int which,int lock);
    /**
     * Funkcja wyświetlająca menu, czyli wszystkie jego przciski, grafiki i napisy
     */
    void drawMenu(menuOption option);
    /**
     * Funkcja rysująca obecny stan gry
     */
    void drawGame(int turn);
    /**
     * Funkcja wyświetlająca ekran z podsumowaniem rozgrywki
     */
    void drawResult(int winner);
    /**
     * Służy do wyświetlania panelu najlepszych 5 wyników
     */
    void drawHighScores();
    /**
     * Wyrysowuje sprite na podstawie pliku o ścieżce path, w miejscu określonym przez x i y, w skali scale
     * ponieważ jest to metoda statyczna, konieczne jest podanie odnośnika do okna w którym będzie wyrysowywany
     * sprite
     */
    static void drawSprite( sf::RenderWindow* window, string path, float x, float y, float scale);
    /**
     * Ustawia tekst w zadanym miejscu (argumenty x i y) i dorysowuje mu obramowanie
     */
    sf::Text adjustText(sf::Text& text, float x, float y);
};


#endif //PROJECT1ALPHA2_DISPLAY_H
