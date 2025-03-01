//
// Created by PC on 18.05.2023.
//
#include "../headers/Display.h"
#include "../headers/GraphicsParameters.h"
Display::Display(Board* board, GraphicsParameters* parameters) {
    this->board=board;
    this->parameters=parameters;
    this->buttons = new vector<sf::CircleShape>();
    this->window= new sf::RenderWindow(sf::VideoMode({width, height}), "Game Hexxagon",
                                          sf::Style::Default,
                                          sf::ContextSettings(0, 0, 8));
    if(this->arial.loadFromFile("../assets/arial.ttf")){
        this->score1 = new Score(this,arial,3,1);
        this->score2 = new Score(this,arial,3,2);
    }
    this->highScores=new HighScores(board,parameters);
}
Display::~Display() {
    delete this->buttons;
    delete this->score1;
    delete this->score2;
    delete this->highScores;
}
void Display::addSingleHexagon(float x,float y){
    int whichOne=buttons->size();
    sf::CircleShape hexagon(radius, 6);
    hexagon.setOutlineColor(sf::Color::Transparent);
    hexagon.setOutlineThickness(radius*0.2f);
    hexagon.setFillColor(parameters->field);
    const char& tmp = board->getData().at(whichOne)->getWhoHere();
    if(tmp=='x')hexagon.setFillColor(sf::Color::Transparent);
    if(tmp=='f')hexagon.setFillColor(parameters->player1);
    if(tmp=='s')hexagon.setFillColor(parameters->player2);
    if(tmp=='n')hexagon.setOutlineColor(parameters->selection1);
    if(tmp=='d')hexagon.setOutlineColor(parameters->selection2);
    hexagon.setPosition({x, y});
    buttons->push_back(hexagon);
    window->draw(hexagon);
    if(tmp=='f')drawSprite(window,parameters->getFirstPlayerTexture(),x,y,1);
    else if(tmp=='s')drawSprite(window,parameters->getSecondPlayerTexture(),x,y,1);
    else if(tmp!='x')drawSprite(window,parameters->getFieldTexture(),x,y,1);
}
void Display::addHexagons(){
    delete buttons;
    buttons=new vector<sf::CircleShape>;
    for(int i=1;i<=5;i++){
        for(int j=i-1;j>=0;j--)//musi być malejący int inaczej hexagony dodają się od prawej do lewej
        {
            float x=(width / 2) - radius*(1.7f*(j-i/2.f))-radius*2,y=1.7f*i*radius;
            if(x>width/2) x+=radius*offset*(i/2.f-j);
            if(x<width/2) x-=radius*offset*(j-i/2.f);
            addSingleHexagon(x-1.7f*radius,y); //przesuwamy o -1.7f*radius aby wyśrodkować ( w tym miejscu wygodnie przesuwa się całą planszę )
        }
    }
    for(int i=6;i<13;i++){
        int m=i%2==0?4:5; //parametr do ustawiania równo
        for(int j=m-1;j>=0;j--)//for(int j=0;j<m;j++)
        {
            float x=(width / 2) - radius*(1.7f*(j-m/2.f))-radius*2,y=1.7f*i*radius;
            if(x>width/2) x+=radius*offset*(m/2.f-j);
            if(x<width/2) x-=radius*offset*(j-m/2.f);
            addSingleHexagon(x-1.7f*radius,y);
        }
    }
    for(int i=13;i<=17;i++){
        int m=(18-i); //parametr odwracający kolejność
        for(int j=m-1;j>=0;j--)//for(int j=0;j<m;j++)
        {
            float x=(width / 2) - radius*(1.7f*(j-m/2.f))-radius*2,y=1.7f*i*radius;
            if(x>width/2) x+=radius*offset*(m/2.f-j);
            if(x<width/2) x-=radius*offset*(j-m/2.f);
            addSingleHexagon(x-1.7f*radius,y);
        }
    }
}
void Display::refresh(int mode) {
    window->clear(parameters->background);
    drawSprite(window,parameters->getBackgroundTexture(),0,0,1);
    switch (mode) {
        case 0:
            drawMenu(HUMAN);
            break;
        case 1:
            drawMenu(ROBOT);
            break;
        case 2:
            drawMenu(SCORES);
            break;
        case 3:
            drawMenu(SAVED);
            break;
        case 4:
            drawGame(1);
            break;
        case 5:
            drawGame(2);
            break;
        case 6:
            drawGame(0);
            break;
        case 7:
            drawResult(score1->value>score2->value?1:2);
            break;
        case 8:
            drawHighScores();
            break;
        default:
            break;
    }
    window->display();
}
bool Display::within(sf::Vector2f& here,sf::Rect<float>& button){
    return abs(here.x-button.left)<=button.width && abs(here.y-button.top)<=button.height;
}
map<int , set<int> > Display::findNeighbours(int which){
    map<int , set<int> > neighbours;
    for(int i : findNearestNeighbours(which))
        neighbours[i]=findDistantNeighbours(i,which);
    return neighbours;
}
set<int> Display::findNearestNeighbours(int which) {
    sf::CircleShape hexagon=buttons->at(which);
    sf::Vector2f where=hexagon.getPosition();
    set<int> closeNeighbours;
    //tworzymy przesunięcia aby zobaczyć sąsiadów
    sf::Vector2f loc1=sf::Vector2f(0.f,-3.f*radius),loc2=sf::Vector2f(-1.3f*radius,-1.3f*radius),
            loc3=sf::Vector2f(1.3f*radius,-1.3f*radius),loc4=sf::Vector2f(-1.3f*radius,1.3f*radius),
            loc5=sf::Vector2f(1.3f*radius,1.3f*radius),loc6=sf::Vector2f(0.f,3.f*radius);
    sf::Vector2f here=where+loc1;
    for(int i=0;i<buttons->size();i++){
        sf::Rect<float> button=buttons->at(i).getGlobalBounds();
        if(i!=which && within(here,button))
            closeNeighbours.insert(i);
    }
    here=where+loc2;
    for(int i=0;i<buttons->size();i++){
        sf::Rect<float> button=buttons->at(i).getGlobalBounds();
        if(i!=which && within(here,button))
            closeNeighbours.insert(i);
    }
    here=where+loc3;
    for(int i=0;i<buttons->size();i++){
        sf::Rect<float> button=buttons->at(i).getGlobalBounds();
        if(i!=which && within(here,button))
            closeNeighbours.insert(i);
    }
    here=where+loc4;
    for(int i=0;i<buttons->size();i++){
        sf::Rect<float> button=buttons->at(i).getGlobalBounds();
        if(i!=which && within(here,button))
            closeNeighbours.insert(i);
    }
    here=where+loc5;
    for(int i=0;i<buttons->size();i++){
        sf::Rect<float> button=buttons->at(i).getGlobalBounds();
        if(i!=which && within(here,button))
            closeNeighbours.insert(i);
    }
    here=where+loc6;
    for(int i=0;i<buttons->size();i++){
        sf::Rect<float> button=buttons->at(i).getGlobalBounds();
        if(i!=which && within(here,button))
            closeNeighbours.insert(i);
    }
    return closeNeighbours;
}
set<int> Display::findDistantNeighbours(int which,int lock){
    set<int> distantNeighbours;
    sf::CircleShape hexagon=buttons->at(which);
    sf::Vector2f where=hexagon.getPosition();
    //tworzymy przesunięcia aby zobaczyć sąsiadów
    sf::Vector2f loc1=sf::Vector2f(0.f,-3.f*radius),loc2=sf::Vector2f(-1.3f*radius,-1.3f*radius),
            loc3=sf::Vector2f(1.3f*radius,-1.3f*radius),loc4=sf::Vector2f(-1.3f*radius,1.3f*radius),
            loc5=sf::Vector2f(1.3f*radius,1.3f*radius),loc6=sf::Vector2f(0.f,3.f*radius);
    sf::Vector2f here=where+loc1;
    for(int i=0;i<buttons->size();i++){
        sf::Rect<float> button=buttons->at(i).getGlobalBounds();
        if(i!=which && i!=lock && within(here,button))
            distantNeighbours.insert(i);
    }
    here=where+loc2;
    for(int i=0;i<buttons->size();i++){
        sf::Rect<float> button=buttons->at(i).getGlobalBounds();
        if(i!=which && i!=lock && within(here,button))
            distantNeighbours.insert(i);
    }
    here=where+loc3;
    for(int i=0;i<buttons->size();i++){
        sf::Rect<float> button=buttons->at(i).getGlobalBounds();
        if(i!=which && i!=lock && within(here,button))
            distantNeighbours.insert(i);
    }
    here=where+loc4;
    for(int i=0;i<buttons->size();i++){
        sf::Rect<float> button=buttons->at(i).getGlobalBounds();
        if(i!=which && i!=lock && within(here,button))
            distantNeighbours.insert(i);
    }
    here=where+loc5;
    for(int i=0;i<buttons->size();i++){
        sf::Rect<float> button=buttons->at(i).getGlobalBounds();
        if(i!=which && i!=lock && within(here,button))
            distantNeighbours.insert(i);
    }
    here=where+loc6;
    for(int i=0;i<buttons->size();i++){
        sf::Rect<float> button=buttons->at(i).getGlobalBounds();
        if(i!=which && i!=lock && within(here,button))
            distantNeighbours.insert(i);
    }
    return distantNeighbours;
}
sf::RenderWindow *Display::getWindow() const {return window;}
vector<sf::CircleShape> *Display::getButtons() const {return buttons;}
Display::Score::Score(Display* display,sf::Font font,float scale,int player){
    this->display=display;
    this->font=font;
    this->player=player;
    this->scale=scale;
    this->displayField=new sf::CircleShape(scale*radius,6);
    this->text = new sf::Text();
    this->text->setFont(this->font);
    this->text->setString(std::to_string(value));
    this->text->setCharacterSize(static_cast<unsigned int>(6 / 7.f * radius * scale));
}
void Display::Score::draw(const float& x, const float& y) {
    this->displayField->setFillColor((player==1)?display->parameters->player1:display->parameters->player2);
    this->displayField->setPosition({x, y});
    this->text->setPosition({x+(this->value<10?(scale*radius)*0.75f:(scale*radius)*0.5f), y+(scale*radius)*0.45f});
    std::string toLoad=(player==1)?display->parameters->getFirstPlayerTexture():display->parameters->getSecondPlayerTexture();
    display->window->draw(*this->displayField);
    drawSprite(display->window,toLoad,x,y,scale);
    display->window->draw(*this->text);
}
void Display::Score::update(const int value) {
    this->value=value;
    this->text = new sf::Text();
    this->text->setFont(this->font);
    this->text->setString(std::to_string(value));
    this->text->setCharacterSize(static_cast<unsigned int>(6 / 7.f * radius * scale));
    this->text->setOutlineThickness(3);
    this->text->setOutlineColor(display->parameters->background);
}
Display::Score::~Score(){
    delete this->text;
    delete this->displayField;
}
void Display::Score::highLight(bool enabled) {
    if(enabled)
        this->displayField->setOutlineThickness(this->scale * radius * 0.1f);
    else
        this->displayField->setOutlineThickness(0);
}
void Display::drawMenu(menuOption option){
    float titleX=width/2.f-9.f*radius, titleY=1.7f*radius;
    sf::CircleShape titlePanel=sf::CircleShape(radius*9.f,6);
    titlePanel.setFillColor(parameters->field);
    titlePanel.setPosition({titleX,titleY});
    titlePanel.setOutlineThickness(0.5f*radius);
    titlePanel.setOutlineColor(parameters->player1);
    sf::Text titleText= sf::Text();
    titleText.setFont(arial);
    titleText.setString("HEXXAGON");
    titleText.setCharacterSize(static_cast<unsigned int>(2.5f*radius));
    titleText.setFillColor(parameters->player2);
    titleText.setPosition({titleX+1.9f*radius,titleY+6.9f*radius});
    titleText.setOutlineColor(parameters->background);
    titleText.setOutlineThickness(3);
    sf::Text graphicOptions =sf::Text();
    graphicOptions.setFont(arial);
    graphicOptions.setString(parameters->getVariant());
    graphicOptions.setCharacterSize(radius*1.5f);
    graphicOptions.setFillColor(parameters->player2);
    graphicOptions.setPosition({titleX+4.3f*radius,titleY+11.f*radius});
    graphicOptions.setOutlineColor(parameters->background);
    graphicOptions.setOutlineThickness(3);
    delete buttons;
    buttons=new vector<sf::CircleShape>;

    float lauchX=width/2+2*radius,lauchY=height-10.4f*radius,modeX=width/2-10*radius,modeY=height-10.4f*radius;
    sf::CircleShape launchButton=sf::CircleShape(radius*4.f,6),
    modeButton=sf::CircleShape(radius*4.f,6);
    launchButton.setFillColor(parameters->player1);
    modeButton.setFillColor(parameters->player2);
    launchButton.setPosition({lauchX,lauchY});
    modeButton.setPosition({modeX,modeY});
    buttons->push_back(launchButton);
    buttons->push_back(modeButton);

    buttons->push_back(titlePanel);

    sf::Text launchText=sf::Text(),
    humanOpponentText=sf::Text(),
    robotOpponentText=sf::Text(),
    scoresText=sf::Text(),
    saveText=sf::Text();
    launchText.setFont(arial);
    humanOpponentText.setFont(arial);
    robotOpponentText.setFont(arial);
    scoresText.setFont(arial);
    saveText.setFont(arial);
    launchText.setString("LAUNCH");
    humanOpponentText.setString("HUMAN");
    robotOpponentText.setString("ROBOT");
    scoresText.setString("SCORES");
    saveText.setString("SAVED");
    launchText.setCharacterSize(radius*1.5f);
    humanOpponentText.setCharacterSize(radius*1.5f);
    robotOpponentText.setCharacterSize(radius*1.5f);
    scoresText.setCharacterSize(radius*1.5f);
    saveText.setCharacterSize(radius*1.5f);
    launchText= adjustText(launchText,lauchX+radius,lauchY+3.f*radius);
    humanOpponentText= adjustText(humanOpponentText,modeX+radius,modeY+3.f*radius);
    robotOpponentText= adjustText(robotOpponentText,modeX+radius,modeY+3.f*radius);
    scoresText= adjustText(scoresText,modeX+radius,modeY+3.f*radius);
    saveText= adjustText(saveText,modeX+radius,modeY+3.f*radius);
    window->draw(titlePanel);
    window->draw(launchButton);
    window->draw(modeButton);
    drawSprite(window, parameters->getTitleTexture(), titleX, titleY, 1);
    drawSprite(window,parameters->getFirstPlayerTexture(),lauchX,lauchY,4);
    drawSprite(window,parameters->getSecondPlayerTexture(),modeX,modeY,4);
    window->draw(titleText);
    window->draw(graphicOptions);
    window->draw(launchText);
    if(option==HUMAN) window->draw(humanOpponentText);
    if(option==ROBOT) window->draw(robotOpponentText);
    if(option==SCORES) window->draw(scoresText);
    if(option==SAVED) window->draw(saveText);
};
void Display::drawGame(int turn){
    addHexagons();
    score1->update(board->count('f'));
    score2->update(board->count('s'));
    score1->highLight(turn==1);
    score2->highLight(turn==2);
    float scoreHight=height/2-score1->scale*radius*2.5f,buttonsHight=height/2+score1->scale*radius*0.5f,
    firstX=radius*2,secondX=width-(score2->scale+1)*radius*2;
    score1->draw(firstX,scoreHight);
    score2->draw(secondX,scoreHight);
    sf::CircleShape menuButton=sf::CircleShape(score1->scale*radius,6),
            saveButton=sf::CircleShape(score1->scale*radius,6);
    menuButton.setFillColor(parameters->player1);
    saveButton.setFillColor(parameters->player2);
    menuButton.setPosition({firstX,buttonsHight});
    saveButton.setPosition({secondX,buttonsHight});
    buttons->push_back(menuButton);
    buttons->push_back(saveButton);
    window->draw(menuButton);
    window->draw(saveButton);
    drawSprite(window,parameters->getFirstPlayerTexture(),firstX,buttonsHight,score1->scale);
    drawSprite(window,parameters->getSecondPlayerTexture(),secondX,buttonsHight,score1->scale);
    sf::Text menuText=sf::Text(),saveText=sf::Text();
    menuText.setFont(arial);
    saveText.setFont(arial);
    menuText.setString("MENU");
    saveText.setString("SAVE");
    menuText.setCharacterSize(3/7.f*radius*score1->scale);
    saveText.setCharacterSize(3/7.f*radius*score1->scale);
    menuText= adjustText(menuText,firstX+1.2f*radius,buttonsHight+2*radius);
    saveText= adjustText(saveText,secondX+1.2f*radius,buttonsHight+2*radius);
    window->draw(menuText);
    window->draw(saveText);
}
void Display::drawResult(int winner){
    sf::CircleShape winnerPanel=sf::CircleShape(radius*8,6),oponentPanel=sf::CircleShape(radius*3.f,6);
    winnerPanel.setFillColor(winner==1?parameters->player1:parameters->player2);
    oponentPanel.setFillColor(winner==1?parameters->player2:parameters->player1);
    float winnerX=width/2.f-8.f*radius,winnerY=radius*2,oponentX=width/2.f-3.f*radius,oponentY=height-7.5f*radius;
    winnerPanel.setPosition({winnerX,winnerY});
    oponentPanel.setPosition({oponentX,oponentY});
    sf::Text winnerText=sf::Text(),menuText=sf::Text();
    winnerText.setFont(arial);
    menuText.setFont(arial);
    winnerText.setString("WINNER");
    menuText.setString("MENU");
    winnerText.setCharacterSize(1.7f*radius);
    menuText.setCharacterSize(1.2f*radius);
    winnerText= adjustText(winnerText,winnerX+4.75f*radius,winnerY+radius*6.f);
    menuText= adjustText(menuText,oponentX+1.3f*radius,oponentY+2.f*radius);

    delete buttons;
    buttons=new vector<sf::CircleShape>;
    buttons->push_back(oponentPanel);

    window->draw(winnerPanel);
    window->draw(oponentPanel);
    drawSprite(window,(winner==1)?parameters->getFirstPlayerTexture():parameters->getSecondPlayerTexture(),winnerX,winnerY,8);
    drawSprite(window,(winner==1)?parameters->getSecondPlayerTexture():parameters->getFirstPlayerTexture(),oponentX,oponentY,3);
    window->draw(winnerText);
    window->draw(menuText);
}
void Display::drawHighScores(){
    sf::CircleShape high1=sf::CircleShape(radius*4,6),high2=high1,
    high3=high1,high4=high1,high5=high1,toMenu=high1;
    float centerX= width/2-4*radius,centerY=height/2-4*radius,left=centerX-7.3f*radius,right=centerX+7.3f*radius,
    high=centerY-4.2f*radius,low=centerY+4.2f*radius,verticalOffset=8.2f*radius;
    high1.setFillColor(parameters->field);
    high2.setFillColor(parameters->field);
    high3.setFillColor(parameters->field);
    high4.setFillColor(parameters->field);
    toMenu.setFillColor(parameters->field);
    high1.setPosition({left,low});
    high2.setPosition({left,high});
    high3.setPosition({centerX,centerY-verticalOffset});
    high4.setPosition({right,high});
    high5.setPosition({right,low});
    toMenu.setPosition({centerX,centerY+verticalOffset});
    high1.setFillColor(highScores->getColor(0));
    high2.setFillColor(highScores->getColor(1));
    high3.setFillColor(highScores->getColor(2));
    high4.setFillColor(highScores->getColor(3));
    high5.setFillColor(highScores->getColor(4));
    buttons->clear();
    buttons->push_back(high1);
    buttons->push_back(high2);
    buttons->push_back(high3);
    buttons->push_back(high4);
    buttons->push_back(high5);
    buttons->push_back(toMenu);
    sf::Text toMenuText=sf::Text();
    toMenuText.setFont(arial);
    toMenuText.setString("MENU");
    toMenuText.setCharacterSize(12/7.f*radius);
    toMenuText.setFillColor(parameters->background);
    toMenuText.setPosition({centerX+1.5f*radius, centerY+verticalOffset + 3.f * radius});

    sf::Text high1Text=sf::Text(),high2Text=sf::Text(),high3Text=sf::Text(),high4Text=sf::Text(),high5Text=sf::Text();
    high1Text.setFont(arial);
    high2Text.setFont(arial);
    high3Text.setFont(arial);
    high4Text.setFont(arial);
    high5Text.setFont(arial);
    high1Text.setString(highScores->getText(0));
    high2Text.setString(highScores->getText(1));
    high3Text.setString(highScores->getText(2));
    high4Text.setString(highScores->getText(3));
    high5Text.setString(highScores->getText(4));
    high1Text.setCharacterSize(12/7.f*radius);
    high2Text.setCharacterSize(12/7.f*radius);
    high3Text.setCharacterSize(12/7.f*radius);
    high4Text.setCharacterSize(12/7.f*radius);
    high5Text.setCharacterSize(12/7.f*radius);
    high1Text= adjustText(high1Text,left+3.0f*radius, low + 3.f * radius);
    high2Text= adjustText(high2Text,left+3.0f*radius, high + 3.f * radius);
    high3Text= adjustText(high3Text,centerX+3.0f*radius, centerY-verticalOffset + 3.f * radius);
    high4Text= adjustText(high4Text,right+3.0f*radius, high + 3.f * radius);
    high5Text= adjustText(high5Text,right+3.0f*radius, low + 3.f * radius);

    window->draw(high1);
    window->draw(high2);
    window->draw(high3);
    window->draw(high4);
    window->draw(high5);
    window->draw(toMenu);
    drawSprite(window,highScores->getTexture(0),left,low,4);
    drawSprite(window,highScores->getTexture(1),left,high,4);
    drawSprite(window,highScores->getTexture(2),centerX,centerY-verticalOffset,4);
    drawSprite(window,highScores->getTexture(3),right,high,4);
    drawSprite(window,highScores->getTexture(4),right,low,4);
    drawSprite(window,parameters->getFieldTexture(),centerX,centerY+verticalOffset,4);
    window->draw(toMenuText);
    window->draw(high1Text);
    window->draw(high2Text);
    window->draw(high3Text);
    window->draw(high4Text);
    window->draw(high5Text);
}
void Display::setBoard(Board *board) {
    this->board = board;
}
void Display::drawSprite(sf::RenderWindow* window,string path, float x, float y, float scale){
    sf::Texture test;
    test.loadFromFile(path);
    sf::Sprite sprite = sf::Sprite(test);
    sprite.setPosition({x, y});
    sprite.setScale({scale,scale});
    window->draw(sprite);
}
HighScores *Display::getHighScores() const {
    return highScores;
}
sf::Text Display::adjustText(sf::Text& text, float x, float y){
    text.setFillColor(parameters->field);
    text.setOutlineColor(parameters->background);
    text.setOutlineThickness(3);
    text.setPosition({x,y});
    return text;
}
