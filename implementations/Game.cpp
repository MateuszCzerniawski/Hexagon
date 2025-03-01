//
// Created by PC on 18.05.2023.
//

#include "../headers/Game.h"
#include <set>
#include <thread>
#include <chrono>
#include <fstream>
Game::Game() {
    this->board=new Board();
    this->parameters=new GraphicsParameters();
    this->display=new Display(board,parameters);
    this->turn=MENU;
    this->recentSelected=-1;
    this->enableRobot= false;
    this->triggerHighscore= false;
    this->loadFromSave= false;
}
Game::~Game() {
    delete this->display;
    delete this->parameters;
    delete this->board;
    delete this->robot;
}
void Game::run() {
    sf::RenderWindow* window=display->getWindow();
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type==sf::Event::MouseButtonPressed){
                sf::Vector2i clickedPosition=sf::Mouse::getPosition(*window);
                for(int i=0; i < display->getButtons()->size(); i++) {
                    if (display->getButtons()->at(i).getGlobalBounds().contains(
                            {static_cast<float>(clickedPosition.x), static_cast<float>(clickedPosition.y)})) {
                        reactToClick(i);
                    }
                }
            }
        }
        display->refresh(deduceMode());
    }
}
void Game::clearSelection() {
    for(Board::Field* field : board->getData()) {
        if (field->getWhoHere() == 'n' || field->getWhoHere() == 'd') {
            field->setWhoHere('O');
        }
    }
}
void Game::dominate(set<int> neighbours) {
    if(this->turn==PLAYER1) {
        for (int i: neighbours) {
            if (board->getData().at(i)->getWhoHere() == 's') {
                board->getData().at(i)->setWhoHere('f');
            }
        }
    } else{
        for (int i: neighbours) {
            if (board->getData().at(i)->getWhoHere() == 'f') {
                board->getData().at(i)->setWhoHere('s');
            }
        }
    }
}
void Game::reactToClick(int which){
    cout<<"Clicked "<<which<<endl;
    switch (this->turn) {
        case MENU:
            switch (which) {
                case 0:
                    if(!triggerHighscore){
                        this->robot = enableRobot ? (new Robot(this->board, this->display)) : nullptr;
                        this->turn = PLAYER1;
                        if(loadFromSave){
                            fstream in = fstream ("../assets/save.txt",ios::in);
                            string toLoad;
                            getline(in,toLoad);
                            this->turn=stoi(toLoad)==1?PLAYER1:PLAYER2;
                            board->loadSave(in);
                            in.close();
                        }
                    } else {
                        this->turn = HIGHSCORES;
                    }
                    break;
                case 1:
                    //te if-y realizują cykl napisów ->HUMAN->ROBOT->SCORES->SAVED->
                    if(!enableRobot){
                        if(triggerHighscore){
                            this->enableRobot = false;
                            this->triggerHighscore= false;
                            this->loadFromSave= true;
                        } else {
                            if(!loadFromSave){
                                this->enableRobot = true;
                                this->triggerHighscore = false;
                                this->loadFromSave = false;
                            } else{
                                this->enableRobot = false;
                                this->triggerHighscore= false;
                                this->loadFromSave= false;
                            }
                        }
                    }else{
                        this->enableRobot = false;
                        this->triggerHighscore= true;
                        this->loadFromSave= false;
                    }
                    break;
                case 2:
                    parameters->cicleVariants();
                    parameters->changeColors();
                    break;
            }
            break;
        case PLAYER1:
            if(which<=60){
                switch (board->getData().at(which)->getWhoHere()) {
                    case 'f': {
                        clearSelection();
                        recentSelected = which;
                        vector<int> possibilities;
                        map<int, set<int> > neighbours = display->findNeighbours(which);
                        for (auto entry: neighbours) {
                            if (board->getData().at(entry.first)->getWhoHere() == 'O' ||
                                board->getData().at(entry.first)->getWhoHere() == 'd') {
                                board->getData().at(entry.first)->setWhoHere('n');
                            }
                            cout << entry.first << " -> ";
                            for (int i: entry.second) {
                                if (board->getData().at(i)->getWhoHere() == 'O') {
                                    board->getData().at(i)->setWhoHere('d');
                                }
                                cout << i << " ";
                            }
                            cout << endl;
                        }
                    }
                        break;
                    case 'n': {
                        board->getData().at(which)->setWhoHere('f');
                        clearSelection();
                        recentSelected = -1;
                        dominate(display->findNearestNeighbours(which));
                        this->turn = PLAYER2;
                    }
                        break;
                    case 'd': {
                        board->getData().at(which)->setWhoHere('f');
                        board->getData().at(recentSelected)->setWhoHere('O');
                        clearSelection();
                        recentSelected = -1;
                        dominate(display->findNearestNeighbours(which));
                        this->turn = PLAYER2;
                    }
                        break;
                }
                if (!havePosMove()) {
                    close();
                }
                if (enableRobot) {
                    display->refresh(deduceMode());
                    std::this_thread::sleep_for(std::chrono::milliseconds(350)); //sleep dla estetyki
                    if (turn == PLAYER2) {
                        robot->makeMove();
                    }
                    if (!havePosMove()) {
                        close();
                    }
                    if (turn == PLAYER2) {
                        this->turn = PLAYER1;
                    }
                }
        }else{
                if(which==62) {
                    save();
                }
                backToMenu();
            }
            break;
        case PLAYER2:
            if(which<=60){
            if (!enableRobot) {
                switch (board->getData().at(which)->getWhoHere()) {
                    case 's': {
                        clearSelection();
                        recentSelected = which;
                        map<int, set<int> > neighbours = display->findNeighbours(which);
                        for (auto entry: neighbours) {
                            if (board->getData().at(entry.first)->getWhoHere() == 'O' ||
                                board->getData().at(entry.first)->getWhoHere() == 'd')
                                board->getData().at(entry.first)->setWhoHere('n');
                            cout << entry.first << " -> ";
                            for (int i: entry.second) {
                                if (board->getData().at(i)->getWhoHere() == 'O')
                                    board->getData().at(i)->setWhoHere('d');
                                cout << i << " ";
                            }
                            cout << endl;
                        }
                    }
                        break;
                    case 'n': {
                        board->getData().at(which)->setWhoHere('s');
                        clearSelection();
                        recentSelected = -1;
                        dominate(display->findNearestNeighbours(which));
                        this->turn = PLAYER1;
                    }
                        break;
                    case 'd': {
                        board->getData().at(which)->setWhoHere('s');
                        board->getData().at(recentSelected)->setWhoHere('O');
                        clearSelection();
                        recentSelected = -1;
                        dominate(display->findNearestNeighbours(which));
                        this->turn = PLAYER1;
                    }
                        break;
                }
            }
            if (!havePosMove()) {
                close();
            }
        }else{
                if(which==62) {
                    save();
                }
                backToMenu();
            }
            break;
        case RESULTS:
            display->getHighScores()->saveNewScore();
            backToMenu();
            break;
        case HIGHSCORES:
            if(which==5) {
                backToMenu();
            }
    }
}
set<int> Game::posMoves(){
    char searched=turn==PLAYER1?'f':'s';
    set<int> possibilities;
    for(Board::Field* field : board->getData())
        if(field->getWhoHere()==searched){
            set<int> tmp;
            for(auto entry : display->findNeighbours(field->getCoordinate())){
                for(int i : entry.second) {
                    tmp.insert(i);
                }
            }
            for(int i : tmp) {
                possibilities.insert(i);
            }
        }
    set<int> tmp;
    for(int i : possibilities) {
        char c=board->getData().at(i)->getWhoHere();
        if ( c != 'f' && c!='s' && c!='x') {
            tmp.insert(i);
        }
    }
    possibilities=tmp;
    return possibilities;
}
bool Game::havePosMove(){
    //sprawdzamy czy są jeszcze wolne pola
    bool check= false;
    for(Board::Field* field : board->getData()) {
        char tmp=field->getWhoHere();
        if ( tmp== 'O' || tmp=='n' || tmp=='d' ) {
            check = true;
        }
    }
    if(!check) {
        return false;
    }
    return posMoves().size()>0;
}
void Game::close() {
    cout<<(turn==PLAYER1?"PLAYER1":"PLAYER2")<<" has no move\n";
    this->turn=RESULTS;
}
int Game::deduceMode(){
    switch (turn) {
        case MENU:
            if (enableRobot) { return 1; }
            if (triggerHighscore) { return 2; }
            if (loadFromSave) { return 3; }
            return 0;
        case PLAYER1: return enableRobot?6:4;
        case PLAYER2: return enableRobot?6:5;
        case RESULTS: return 7;
        case HIGHSCORES: return 8;
    }
}
void Game::save(){
    fstream out = fstream("../assets/save.txt" , ios::out);
    out<<turn<<endl;
    board->save(out);
    out.close();
}
void Game::backToMenu(){
    if(enableRobot) { delete this->robot; }
    Board* tmp=new Board();
    delete this->board;
    display->setBoard(tmp);
    this->board=tmp;
    this->turn=MENU;
}