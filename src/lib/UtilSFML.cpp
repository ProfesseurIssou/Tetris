#include "UtilSFML.h"

//GRAPHICS
bool CursorOnSprite(sf::RenderWindow &window, sf::Sprite &sprite){
  sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
  return sprite.getGlobalBounds().contains(mousePosition);
}


//NETWORK
bool sendMessage(std::string msgOut, sf::TcpSocket &socket){
  //On cree la variable qui va contenir le packet a envoyer
  sf::Packet packetSend;
  //On met le message dans le packet (du premier thread)
  packetSend << msgOut;
  //On envoye le packet
  socket.send(packetSend);
}
std::string receivedMessage(sf::TcpSocket &socket){
  //Le message recus
  std::string msgIn;
	//On cree une variable qui va contenir le packet recus
	sf::Packet packetReceive;
  //On recois le message
	socket.receive(packetReceive);
  //Si on arrive a recuperer le message
  packetReceive >> msgIn;
  return msgIn;
}

//NETWORK MULTI-CLIENTS
//Server
Server::Server(){

}
bool Server::start(int port){
  if(listener.listen(port) == sf::Socket::Done){//Si on reussi a cree le server
    selector.add(listener); //On ajoute le socket d'ecoute au selecteur
    serverPort = port;      //On definie le port du serveur
    return true;            //Done
  }
  return false; //Error
}
bool Server::newClientRequest(){
  if(selector.wait(sf::seconds(timeoutSelectorWait))){//Si l'un des sockets a recus une requete
    if(selector.isReady(listener)){ //Si le socket d'ecoute a recus une requete
      return true;                    //nouveau client
    }
  }
  return false;                   //Pas de nouveau client
}
int Server::acceptClient(){
  sf::TcpSocket *newClient = new sf::TcpSocket; //On cree un nouveau socket
  listener.accept(*newClient);                  //On accepte le client
  selector.add(*newClient);                     //On ajoute le socket client dans le selecteur
  clientsList.push_back(newClient);             //On ajoute le pointeurs du socket du client dans la liste
  return clientsList.size()-1;                  //On retourne la position du client
}
int Server::getPosClientRequests(){
  if(selector.wait(sf::seconds(timeoutSelectorWait))){//Si l'un des socket a recus un packet
    currentClientReceive = 0;                           //On repart au premier client
    for(int i = 0;i<clientsList.size();i++){ //Pour chaque client de la liste
      if(selector.isReady(*clientsList[i])){                      //Si le client a envoyer un packet
        currentClientReceive = i+1;                                 //On sauvegarde la position du future client (suivant)
        return i;                                                   //On retourne la position du client
      }
    }
  }
  return -1;  //Aucun packet recus
}
sf::Packet Server::receivePacket(int clientPosition){
  sf::Packet receivePacket;                             //On prepare la reception du packet
  clientsList[clientPosition]->receive(receivePacket);  //On recupere le packet
  return receivePacket;                                 //On retourne le packet recus
}
bool Server::sendPacket(int clientPosition,sf::Packet sendPacket){
  clientsList[clientPosition]->send(sendPacket);  //On envoie le packet au client
  return true;                                    //Envoyer
}
//Client
Client::Client(){

}
bool Client::connect(std::string ip,int port){
  serverSocket.setBlocking(true);  //On active le blockage pour laisser la connexion se faire
  if(serverSocket.connect(ip,port) != sf::Socket::Done){//Si on ne peu pas se connecter au serveur
    return false;//Error
  }
  serverSocket.setBlocking(false);  //On desactive le blockage de reponse
  serverIp = ip;
  return true;  //Done
}
bool Client::sendPacket(sf::Packet packet){
  /* EXEMPLE OF CALL:
  Client client;
  ...
  sf::Packet packet;
  packet << data1 << data2 << data3 << ...;
  client.sendPacket(packet);
  */
  serverSocket.send(packet);        //On envoie le packet
  return true;                      //Packet envoyer
}
bool Client::haveReceivePacket(){
  if(serverSocket.receive(receivePacket) == sf::Socket::Done){//Si on recois un packet du server
    return true;  //Packet recus est stocket dans receivePacket
  }
  return false; //Aucun packet recus
}


//OTHER
int strToInt(std::string text){
  //On cree l'objet de la classe sstream
  std::stringstream convert(text);
  //On convertie
  int x;
  convert >> x;
  return x;
}
std::string intToStr(int number){
  std::string text = std::to_string(number);
  return text;
}
