#ifndef TETRISMENU_H
#define TETRISMENU_H

#include "../lib/UtilSFML.h"
#include <sstream>          //String
#include <SFML/Graphics.hpp>

class TetrisMenu{
  public:
    //CONST

    //STRUCT

    //VARIABLES
    bool multiplayer = false; //Si on est en multi ou non
    bool mode = 1;            //0 = serveur, 1 = client
    std::string ipServer;     //Ip du serveur

    //SFML VARIABLES

    //FUNCTIONS
    TetrisMenu(sf::RenderWindow *window); //Constructeur
    void Menu();                          //Menu principale
    void MultiplayerMenu();               //Menu pour rejoindre un serveur
  private:
    //CONST

    //STRUCT

    //VARIABLES

    //SFML VARIABLES
    sf::RenderWindow *gameWindow;         //Ecran de jeux(pointeur)
    sf::Texture backgroundTexture;        //Texture du fond du menu
    sf::Sprite backgroundSprite;          //Sprite du fond
    sf::Font font;                        //Police de texte
    //(Menu Principale)
    sf::Texture buttonSinglePlayerTexture;//Bouton 1 joueur
    sf::Texture buttonMultiPlayerTexture; //Bouton multijoueur
    sf::Sprite buttonSinglePlayerSprite;  //Bouton solo
    sf::Sprite buttonMultiPlayerSprite;   //Bouton multijoueur
    //(Menu Multi)
    sf::Texture buttonCreateTexture;      //Bouton creer (un serveur)
    sf::Texture inputFieldTexture;        //Input de l'ip du serveur
    sf::Sprite buttonCreateSprite;        //Bouton creer (un serveur)
    sf::Sprite inputFieldSprite;          //Input de l'ip du serveur

    //FUNCTIONS

};

#endif // TETRISMENU_H
