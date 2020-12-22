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
