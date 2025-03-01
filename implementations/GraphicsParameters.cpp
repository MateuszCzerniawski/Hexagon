//
// Created by PC on 24.05.2023.
//

#include "../headers/GraphicsParameters.h"
#include <iostream>
GraphicsParameters::GraphicsParameters(): variant(CRYSTALS){changeColors();}
void GraphicsParameters::changeColors(){
    switch (variant) {
        case CRYSTALS:
            background=sf::Color::Black;
            field=sf::Color::White;
            player1=sf::Color(86, 93, 117,255);
            player2=sf::Color(209, 50, 55,255);
            selection1=sf::Color::Yellow;
            selection2=sf::Color::Green;
            break;
        case MINIMALISM:
            background=sf::Color::Black;
            field=sf::Color::White;
            player1=sf::Color(50, 66, 209,255);
            player2=sf::Color(209, 50, 55,255);
            selection1=sf::Color::Yellow;
            selection2=sf::Color::Green;
            break;
        case TEMPEST:
            background=sf::Color::Black;
            field=sf::Color::White;
            player1=sf::Color(128,70,148,225);
            player2=field;
            selection1=sf::Color::Yellow;
            selection2=sf::Color::Green;
            break;
    }
    std::cout<<"Colors changed\n";
}
void GraphicsParameters::cicleVariants(){
    switch (variant) {
        case CRYSTALS:
            this->variant=TEMPEST;
            break;
        case TEMPEST:
            this->variant=MINIMALISM;
            break;
        case MINIMALISM:
            this->variant=CRYSTALS;
    }
}
std::string GraphicsParameters::getVariant() const {
    switch (variant) {
        case MINIMALISM:return "MINIMALISM";
        case CRYSTALS:return "CRYSTALS";
        case TEMPEST:return "TEMPEST";
    }
}
std::string  GraphicsParameters::getFieldTexture() const{
    switch (variant) {
        case CRYSTALS: return empty;
        case MINIMALISM: return blank;
        case TEMPEST: return emptyTempest;
    }
}
std::string  GraphicsParameters::getFirstPlayerTexture() const{
    switch (variant) {
        case CRYSTALS: return blueCrystal;
        case MINIMALISM: return blank;
        case TEMPEST: return blueRain;
    }
}
std::string  GraphicsParameters::getSecondPlayerTexture() const{
    switch (variant) {
        case CRYSTALS: return redCrystal;
        case MINIMALISM: return blank;
        case TEMPEST: return purpleLightning;
    }
}
std::string  GraphicsParameters::getTitleTexture() const{
    switch (variant) {
        case CRYSTALS: return crystalTitle;
        case MINIMALISM: return blank;
        case TEMPEST: return tempestTitle;
    }
}
std::string  GraphicsParameters::getBackgroundTexture() const{
    switch (variant) {
        case CRYSTALS: return crystalBackGround;
        case MINIMALISM: return blank;
        case TEMPEST: return tempestBackGround;
    }
}
