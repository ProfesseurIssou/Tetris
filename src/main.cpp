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
#include "TetrisGame.h"

/*VARIABLE GLOBAL*/
const unsigned int gameScreenHauteur = 1000;//Taille en pixel en hauteur
const unsigned int gameScreenLargeur = 1250;//Taille en pixel en largeur

sf::RenderWindow gameWindow;        //Ecran de jeux
sf::Texture menuBackgroundTexture;  //Texture du fond du menu
sf::Texture buttonSinglePlayerTexture;//Bouton 1 joueur
sf::Texture buttonMultiPlayerTexture; //Bouton multijoueur
sf::Sprite fondMenuSprite;            //Fond du menu
sf::Sprite buttonSinglePlayerSprite;  //Bouton solo
sf::Sprite buttonMultiPlayerSprite;   //Bouton multijoueur

sf::Font font;                      //Police de texte
/*###############*/


class MainMenu{

};

void Menu(bool &multiplayer, bool &gameRunning);

int main(){
  /*INITIALISATION JEUX*/
  bool gameRunning = true;  //Si le jeu tourne
  bool multiplayer = false; //Si on est en multi ou non
  bool mode = 0;            //0 = serveur, 1 = client
  gameWindow.create(sf::VideoMode(gameScreenLargeur,gameScreenHauteur),"Tetris");  //On créé l'ecran de jeux
  TetrisGame game(&gameWindow);  //On cree l'instance du jeux

  /*JEUX*/
  while(gameRunning){         //Tant que le jeux tourne
    /*MENU*/
    Menu(multiplayer,gameRunning);
    /*####*/

    /*INITIALISATION PARTIE*/
    if(multiplayer == false && gameRunning == 1){ //Si on joue en solo
      gameRunning = !game.PlaySolo();        //On lance la partie en solo
    }
    //Multiplayer menu
  }
  return 0;
}

void Menu(bool &multiplayer, bool &gameRunning){
  /*INITIALISATION PARTIE*/
  bool actifMenu = true;    //Tant que le menu est en route
  menuBackgroundTexture.loadFromFile("img/menu/background.png");
  buttonSinglePlayerTexture.loadFromFile("img/menu/Solo.png");
  buttonMultiPlayerTexture.loadFromFile("img/menu/Multiplayer.png");
  fondMenuSprite.setTexture(menuBackgroundTexture);
  buttonSinglePlayerSprite.setTexture(buttonSinglePlayerTexture);
  buttonMultiPlayerSprite.setTexture(buttonMultiPlayerTexture);
  buttonSinglePlayerSprite.setPosition(480,300);
  buttonMultiPlayerSprite.setPosition(480,400);

  /*MENU*/
  while(actifMenu){
    //Condition
    sf::Event e;          //On recupere l'evenement
    while(gameWindow.pollEvent(e)){
      if(e.type == sf::Event::Closed){//Si on ferme la fenetre
        actifMenu = false;              //On stop la partie
        gameRunning = false;            //On stop le jeux
        gameWindow.close();             //On ferme l'ecrant de jeux
      }
      if(e.type == sf::Event::MouseButtonPressed){
        //Si le bouton solo est cliquer
        if(CursorOnSprite(gameWindow,buttonSinglePlayerSprite)){
          multiplayer = 0;
          actifMenu = 0;
        }
        //Si le bouton multi est cliquer
        if(CursorOnSprite(gameWindow,buttonMultiPlayerSprite)){
          multiplayer = 1;
          actifMenu = 0;
        }
      }
    }

    //Affichage
    gameWindow.clear();

    gameWindow.draw(fondMenuSprite);
    gameWindow.draw(buttonSinglePlayerSprite);
    gameWindow.draw(buttonMultiPlayerSprite);

    gameWindow.display();
  }
}

