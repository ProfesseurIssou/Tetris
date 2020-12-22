//MultiJoueur - Selection mode (serveur/client)
//MultiJoueur - Serveur
//MultiJoueur - Client
//MultiJoueur - Envoie et reception de requete
//MultiJoueur - Dash partage

//Sounds

#include <iostream> //CIN COUT ENDL

#include <cstdlib> //Pour random
#include <string>   //std::string, std::to_string
#include <SFML/Graphics.hpp>

#include "lib/UtilSFML.h"
#include "TetrisMenu.h"
#include "TetrisGame.h"

/*VARIABLE GLOBAL*/
const unsigned int gameScreenHauteur = 1000;//Taille en pixel en hauteur
const unsigned int gameScreenLargeur = 1250;//Taille en pixel en largeur
sf::RenderWindow gameWindow;        //Ecran de jeux
/*###############*/


int main(){
  /*INITIALISATION JEUX*/
  bool gameRunning = true;  //Si le jeu tourne
  TetrisMenu menu(&gameWindow);   //On cree l'instance du menu
  TetrisGame game(&gameWindow);   //On cree l'instance du jeux

  gameWindow.create(sf::VideoMode(gameScreenLargeur,gameScreenHauteur),"Tetris");  //On créé l'ecran de jeux

  while(gameWindow.isOpen()){       //Tant que le jeux tourne
    menu.Menu();                    //On lance le menu principale
    if(menu.multiplayer == false){  //Si on est en mode solo
      gameRunning = !game.PlaySolo(); //On lance la partie en solo
    }else{                          //Si on est en mode multi
      menu.MultiplayerMenu();         //On lance le menu pour rejoindre un serveur
      if(menu.mode == 0){             //Si on est en mode serveur

      }else{                          //Si on est en mode client

      }
    }
  }
  return 0;
}





