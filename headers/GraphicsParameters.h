//
// Created by PC on 24.05.2023.
//

#ifndef PROJECT1ALPHA3_GRAPHICSPARAMETERS_H
#define PROJECT1ALPHA3_GRAPHICSPARAMETERS_H
#include "SFML/Graphics.hpp"
#include <string>
/**
 * parametry do wyrysowywania gry
 */
enum graphicVariant{CRYSTALS,TEMPEST,MINIMALISM};
static const unsigned int height = 900,width= 1.6 * height,radius=28;
const float offset=4.f;
/**
 * pliki do wczytania - większość zrobiona przez Joannę Żebracką
 */
const static std::string blank="../assets/Blank.png",
redCrystal="../assets/RedCrystal.png",blueCrystal="../assets/BlueCrystal.png",
empty="../assets/EmptyField.png",crystalTitle="../assets/CrystalTitle.png",crystalBackGround="../assets/CrystalBackGround.png",
emptyTempest="../assets/EmptyTempest.png",purpleLightning="../assets/PurpleLightning.png",
blueRain="../assets/BlueRain.png",tempestTitle="../assets/TempestTitle.png",tempestBackGround="../assets/TempestBackGround.png";
//https://elements-video-cover-images-0.imgix.net/files/52ebf4e5-d3a6-494f-84e9-22de3a15358e/inline_image_preview.jpg?auto=compress%2Cformat&fit=min&h=394&w=700&s=738ccaee0c736dd522290109af353076
//https://www.treehugger.com/thmb/7u1isEt-R4cdJMDXKcrOlA4m3vc=/1500x0/filters:no_upscale():max_bytes(150000):strip_icc()/GettyImages-1199237495-85028588331d43689237e4e2ba60ce9e.jpg
/**
 * Klasa odpowiadająca za manipulację kolorami, tekstami i assetami
 */
class GraphicsParameters {
    /**
     * Pole przechowujace aktywny wariant graficzny
     */
    graphicVariant variant;
public:
    /**
     * szata graficzna
     */
    sf::Color background, field,player1,player2,selection1,selection2;
    /**
     * Konstruktor ustawiający domyślny tryb graficzny
     */
    GraphicsParameters();
    /**
     * Funkcja zmienijąca kolory w zalażności od trybu
     */
    void changeColors();
    /**
     * Zapewnia cykliczność wybieranych trybów graficznych
     */
    void cicleVariants();
    /**
     * Gettery na wariant graficzny i tekstury
     */
    std::string getVariant() const;
    std::string getFieldTexture() const;
    std::string getFirstPlayerTexture() const;
    std::string getSecondPlayerTexture() const;
    std::string getTitleTexture() const;
    std::string getBackgroundTexture() const;
};


#endif //PROJECT1ALPHA3_GRAPHICSPARAMETERS_H
