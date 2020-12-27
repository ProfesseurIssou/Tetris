#ifndef TETRISMENU_H
#define TETRISMENU_H

#include "../lib/UtilSFML.h"
#include <sstream>          //String
#include <vector>           //Liste dynamique
#include <SFML/Graphics.hpp>

class TetrisMenu{
  public:
    //CONST

    //STATES
    int modeMenu = 0;         //Quel menu on est
    /*-1 =  On quitte le menu
      0  =  Menu Principale
      1  =  Menu pour rejoindre un serveur
      2  =  Menu ou on attent les clients (serveur)
      3  =  Menu ou on attent les clients (client)
    */
    bool multiplayer = false; //Si on est en multi ou non
    bool mode = 1;            //0 = serveur, 1 = client

    //STRUCT

    //VARIABLES
    std::string ipServer;     //Ip du serveur

    //SFML VARIABLES

    //FUNCTIONS
    TetrisMenu(sf::RenderWindow *window); //Constructeur
    void Menu();                          //Menu principale
    void MultiplayerMenu();               //Menu pour rejoindre un serveur
    void MultiplayerServerMenu(int nbPlayer);//Menu en attente de connection des clients et bouton start
    void MultiplayerClientMenu();         //Menu en attente de connection des clients et attente du start du serveur
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
    //(Menu Multi server)
    sf::Texture buttonPlayTexture;        //Bouton lance la partie (un serveur)
    sf::Sprite buttonPlaySprite;          //Bouton lance la partie (un serveur)

    //FUNCTIONS

};

#endif // TETRISMENU_H
