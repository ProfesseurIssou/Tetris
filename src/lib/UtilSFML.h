#ifndef UTILSFML_H_INCLUDED
#define UTILSFML_H_INCLUDED

#include <sstream>              //String
#include <string>               //To string
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

//GRAPHICS
bool CursorOnSprite(sf::RenderWindow &window, sf::Sprite &sprite);    //Si le curseur est sur le sprite

//NETWORK
bool sendMessage(std::string msgOut, sf::TcpSocket &socket);          //Envoie d'un texte à un socket(client ou serveur connecte a celui si)
std::string receivedMessage(sf::TcpSocket &socket);                   //Reception d'un texte d'un socket

//NETWORK MULTI-CLIENTS
class Server{
  public:
    //Variables
    int serverPort;
    float timeoutSelectorWait = 0.1;          //Temp d'attente de connexion
    std::vector<sf::TcpSocket*> clientsList;  //Liste de tout les pointeurs de tout les clients
    int currentClientReceive = 0;             //Position du client dans la liste (receivePacket pour savoir quel client nous a envoyer la données et ne pas penaliser les derniers de la liste )

    //Functions
    Server();                             //Constructor
    bool start(int port);                 //Demarrage du server
    bool newClientRequest();              //Si un nouveau client essaye de se connecter
    int acceptClient();                   //Accepter le nouveau client et nous retourne la position du client
    int getPosClientRequests();           //Si un client de la liste nous a envoyer un packet (-1 pas de client sinon position du client)
    sf::Packet receivePacket(int clientPosition);//On recupere le packet recus d'un client precisement
    bool sendPacket(int clientPosition,sf::Packet sendPacket);//Envoyer un packet a un client
  private:
    //Variables
    sf::TcpListener listener;           //Socket d'ecoute
    sf::SocketSelector selector;        //Selecteur

    //Functions
};
class Client{
  public:
    //Variables
    std::string serverIp;     //IP du server
    int serverPort;           //Port du server
    sf::Packet receivePacket; //Packet recus

    //Functions
    Client();                             //Constructor
    bool connect(std::string ip,int port);//Connexion au server
    bool sendPacket(sf::Packet packet);   //Envoie d'un packet au server
    bool haveReceivePacket();             //Checker si le server envoie quelque chose

  private:
    //Variables
    sf::TcpSocket serverSocket;           //Socket du server

    //Functions
};


//OTHER
int strToInt(std::string text);
std::string intToStr(int number);

#endif // UTILSFML_H_INCLUDED
