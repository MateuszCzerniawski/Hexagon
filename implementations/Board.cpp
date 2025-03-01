//
// Created by PC on 15.05.2023.
//

#include "../headers/Board.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

Board::Board() {
    load();
    showCoordinates();
}
Board::~Board(){
    textData.clear();
    data.clear();
}
void Board::load() {
    fstream in = fstream("../assets/board.txt" , ios::in);
    string line;
    int counter=0;
    while(getline(in,line)) {
        this->textData.push_back(line);
        for(char c : line)
            if(c!=' ')this->data.push_back(new Field(counter++,c));
    }
    this->data.at(0 )->setWhoHere('f');
    this->data.at(46)->setWhoHere('f');
    this->data.at(50)->setWhoHere('f');
    this->data.at(10)->setWhoHere('s');
    this->data.at(14)->setWhoHere('s');
    this->data.at(60)->setWhoHere('s');
    in.close();
}
void Board::loadSave(fstream& in){
    string line;
    getline(in,line); //tylko jedna linia
    loadSave(line);
}
void Board::loadSave(string line){
    data.clear();
    for(int i=0;i<line.size();i++)
        data.push_back(new Field(i,line.at(i)));
}
void Board::save(fstream& out){
    for(auto f : data)
        out<<f->getWhoHere();
}
void Board::showCoordinates() {
    int index=0;
    for(string s : this->textData){
        for(char c : s){
            if(c!=' '){
                int tmp=this->data.at(index++)->getCoordinate();
                if(tmp==21 || tmp==34 || tmp==35) c='x';
                if(c!='x') cout<<(tmp<10?" ":"")<<tmp;
                else cout<<"x ";
            } else cout<<c;
        }
        cout<<endl;
    }
}
int Board::count(const char& toCount){
    int result=0;
    for(Field* field : this->data)
        if(field->getWhoHere()==toCount) result++;
    return result;
}
const vector<Board::Field*> &Board::getData() const {
    return data;
}

Board::Field::Field(int coordinate,char whoHere): coordinate(coordinate),whoHere(whoHere){}

//getter setter
int Board::Field::getCoordinate() const {
    return coordinate;
}


char Board::Field::getWhoHere() const {
    return whoHere;
}

void Board::Field::setWhoHere(char whoHere) {
    Field::whoHere = whoHere;
}

