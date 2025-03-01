//
// Created by PC on 22.05.2023.
//

#include "../headers/Robot.h"
#include "../headers/Board.h"
#include <iostream>
#include <map>
#include <set>
#include <ctime>
Robot::Robot(Board* board, Display* display): board(board), display(display) {}
Robot::~Robot() {}
void Robot::makeMove() {
    map< int ,map<int,int>  > options=analize();
    Move best= findBestMove(options);
    if(best.to==-1) {
        return; //potrzebne gdy skończą się opcje
    }
    if(best.benefit==0){
        propagate();
        return;
    }
    auto neighbours = display->findNeighbours(best.from);
    bool closeNeighbour = false;
    for (auto i: neighbours) {
        if (best.from == i.first) {
            closeNeighbour = true;
        }
    }
    const vector<Board::Field *> &data = board->getData();
    data.at(best.to)->setWhoHere('s');
    set<int> toReplace = display->findNearestNeighbours(best.to);
    for (int i: toReplace) {
        if (data.at(i)->getWhoHere() == 'f') {
            data.at(i)->setWhoHere('s');
        }
    }
    if (!closeNeighbour) {
        data.at(best.from)->setWhoHere('O');
    }
}
map< int ,map<int,int>  > Robot::analize(){
    map< int ,map<int,int>  > options; //szczegółowa analiza
    const vector<Board::Field*>& data=board->getData();
    for(Board::Field* field : data)
        if(field->getWhoHere()=='s'){
            int here=field->getCoordinate();
            map<int,int> tmp;
            for(auto i : display->findNeighbours(here)) {
                if (data.at(i.first)->getWhoHere() == 'O') {
                    tmp[i.first] = calculateBenefit(i.first);
                    for (int j: i.second) {
                        if (data.at(j)->getWhoHere() == 'O') {
                            tmp[j] = calculateBenefit(j);
                        }
                    }
                }
            }
            options[here]=tmp;
        }
    return options;
}
int Robot::calculateBenefit(const int& where){
    int benefit=0;
    const vector<Board::Field*>& data=board->getData();
    for(int i : display->findNearestNeighbours(where)) {
        if (data.at(i)->getWhoHere() == 'f') {
            benefit++;
        }
    }
    return benefit;
}
Robot::Move Robot::findBestMove( const map< int ,map<int,int>  >& options){
    vector<Move> candidates;
    for(auto i : options){
        Move candidate=getMaxBenefit(i.first,i.second);
        candidates.push_back(candidate);
    }
    int max=-1;
    Move best=Move();
    for(Move i : candidates)
        if(i.benefit>max){
            max=i.benefit;
            best=i;
        }
    for(Move i : candidates) {
        cout << i.from << " -> " << i.to << " (" << i.benefit << ")\n";
    }
    cout<<"  Best "<<best.from<<" -> "<<best.to<<" ("<<best.benefit<<")\n";
    return best;
}
Robot::Move Robot::getMaxBenefit(int from,map<int,int> options){
    int max=-1;
    Move best=Move();
    best.setFrom(from);
    for(auto i : options)
        if(max<i.second) {
            max = i.second;
            best.setTo(i.first);
            best.setBenefit(max);
        }
    return best;
}
void Robot::propagate(){
    set<int> possiblePropagations;
    for(auto i : board->getData())
        if(i->getWhoHere()=='s'){
            set<int> neighbours=display->findNearestNeighbours(i->getCoordinate());
            for(int j : neighbours) {
                if (board->getData().at(j)->getWhoHere() == 'O') {
                    possiblePropagations.insert(j);
                }
            }
        }
    vector<int> asVector;
    for(int i : possiblePropagations) {
        asVector.push_back(i);
    }
    srand(time(NULL));
    board->getData().at(asVector.at(rand()%asVector.size()))->setWhoHere('s');
}
Robot::Move::Move() : from(-1), to(-1), benefit(-1) {}
Robot::Move::Move(int from, int to, int benefit) : from(from), to(to), benefit(benefit) {}
void Robot::Move::setFrom(int from) {
    Move::from = from;
}
void Robot::Move::setTo(int to) {
    Move::to = to;
}
void Robot::Move::setBenefit(int benefit) {
    Move::benefit = benefit;
}
