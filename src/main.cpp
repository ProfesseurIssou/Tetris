//MultiJoueur - Selection mode (serveur/client)
//MultiJoueur - Serveur
//MultiJoueur - Client
//MultiJoueur - Envoie et reception de requete
//MultiJoueur - Dash partage

//Sounds

#include <iostream> //CIN COUT ENDL
#include <vector>   //Liste dynamique
#include <cstdlib>  //Pour random
#include <string>   //std::string, std::to_string
#include <SFML/Graphics.hpp>

#include "lib/UtilSFML.h"
#include "TetrisMenu.h"
#include "TetrisGame.h"

/*VARIABLE GLOBAL*/
const unsigned int gameScreenHauteur = 1000;//Taille en pixel en hauteur
const unsigned int gameScreenLargeur = 1250;//Taille en pixel en largeur
const int Port = 5000;                        //Port du serveur
sf::RenderWindow gameWindow;              //Ecran de jeux
Server server;                              //Mode serveur
Client client;                              //Mode client
/*###############*/

int main(){
  /*INITIALISATION JEUX*/
  bool gameRunning = true;  //Si le jeu tourne
  TetrisMenu menu(&gameWindow);   //On cree l'instance du menu
  TetrisGame game(&gameWindow);   //On cree l'instance du jeux

  gameWindow.create(sf::VideoMode(gameScreenLargeur,gameScreenHauteur),"Tetris");  //On créé l'ecran de jeux

  while(gameWindow.isOpen()){       //Tant que le jeux tourne
    if(menu.modeMenu == 0){           //Si on est au menu principale
      menu.Menu();                      //On lance le menu principale
    }else if(menu.modeMenu == 1){     //Si on est au menu pour rejoindre un serveur
      menu.MultiplayerMenu();           //On lance le menu pour rejoindre un serveur
    }else if(menu.modeMenu == 2){     //Si on est au menu pour attendre les client (mode serveur)
      if(server.serverPort != Port){    //Si le serveur n'a toujour pas ete cree
        server.start(Port);               //On demarre le serveur
      }
      if(server.newClientRequest()){    //Si un nouveau client tente de se connecter
        server.acceptClient();            //On accepte le nouveau client
      }
      menu.MultiplayerServerMenu(server.clientsList.size());//On lance le menu d'attente de client en mode serveur
    }else if(menu.modeMenu == 3){     //Si on est au menu pour attendre les client (mode client)
      if(client.serverIp != menu.ipServer){//Si le client n'est pas encore connecter
        bool connected = client.connect(menu.ipServer,Port);//On se connecte au serveur
        if(!connected){                       //Si on arrive pas a ce connecter
          menu.modeMenu = 1;                    //On retourne au menu pour rejoindre un serveur
        }
      }else{
        if(client.haveReceivePacket()){ //Si on recois le packet de demarrage du serveur
          std::string message;
          client.receivePacket >> message;//On recupere le message
          if(message == "START"){         //Si c'est le message de demarrage
            gameRunning = !game.PlayMultiClient(&client);//On demarre la partie multi en mode client
          }
        }
        menu.MultiplayerClientMenu();         //On lance le menu d'attente de client (mode client)
      }
    }else if(menu.modeMenu == -1){    //Si on quitte le menu
      if(menu.multiplayer == false){    //Si on est en mode solo
        menu.modeMenu = 0;                //On remet le menu par defaut
        gameRunning = !game.PlaySolo();   //On lance la partie en solo
      }else{                            //Si on est en mode multi
        menu.modeMenu = 2;                //On remet le menu d'attente des clients (mode serveur)
        sf::Packet startPacket;           //On cree le packet a envoyer
        startPacket << "START";           //On met l'information de demarrage
        for(int i=0;i<server.clientsList.size();i++){ //Pour chaque client de la liste
          server.sendPacket(i,startPacket);            //On envoie un packet de demarrage a chaque client
        }
        gameRunning = !game.PlayMultiServer(&server);//On demarre le jeux en multi en mode serveur
      }
    }
  }
  return 0;
}
