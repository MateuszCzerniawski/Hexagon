//
// Created by PC on 25.05.2023.
//

#include "../headers/HighScores.h"
#include "../headers/Board.h"
#include "algorithm"
HighScores::HighScores(Board* current,GraphicsParameters* parameters){
    records= vector<Board*>();
    this->current=current;
    this->parameters=parameters;
    fstream in = fstream("../assets/scores.txt",ios::in);
    string line;
    while (getline(in,line)){
        Board* board = new Board();
        board->loadSave(line);
        records.push_back(board);
    }
    auto sortHelp= [this](Board* first, Board* second)->int{
        pair<int , int > firstCounters= getScores(first);
        int firstCount1=firstCounters.first,firstCount2=firstCounters.second;
        pair<int , int > secondCounters= getScores(second);
        int secondCount1=secondCounters.first,secondCount2=secondCounters.second;
        int firstHigher=firstCount1>firstCount2?firstCount1:firstCount2;
        int secondHigher=secondCount1>secondCount2?secondCount1:secondCount2;
        return firstHigher>secondHigher;
    };
    std::ranges::sort(records,sortHelp);
}
HighScores::~HighScores(){
    for(auto i : records) {
        delete i;
    }
    records.clear();
}
sf::Color HighScores::getColor(int which){
    pair<int , int > counters= getScores(which);
    int count1=counters.first,count2=counters.second;
    return count1>count2?parameters->player1:parameters->player2;

}
std::string HighScores::getTexture(int which){
    pair<int , int > counters= getScores(which);
    int count1=counters.first,count2=counters.second;
    return count1>count2?parameters->getFirstPlayerTexture():parameters->getSecondPlayerTexture();
}
std::string HighScores::getText(int which){
    pair<int , int > counters= getScores(which);
    int count1=counters.first,count2=counters.second;
    return count1>count2?to_string(count1):to_string(count2);
}
void HighScores::saveNewScore(){
    fstream out = fstream("../assets/scores.txt",ios::app);
    out<<endl;
    current->save(out);
    out.close();
}
pair<int,int> HighScores::getScores(int which){
    pair<int , int > result;
    Board& board = *records.at(which);
    int count1=0,count2=0;
    for(auto i : board.getData()){
        if(i->getWhoHere()=='f') {
            count1++;
        }
        if(i->getWhoHere()=='s') {
            count2++;
        }
    }
    result.first=count1;
    result.second=count2;
    return result;
}
pair<int,int> HighScores::getScores(Board* board){
    pair<int , int > result;
    int count1=0,count2=0;
    for(auto i : board->getData()){
        if(i->getWhoHere()=='f') {
            count1++;
        }
        if(i->getWhoHere()=='s') {
            count2++;
        }
    }
    result.first=count1;
    result.second=count2;
    return result;
}
