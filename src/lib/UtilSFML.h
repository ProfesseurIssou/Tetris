#ifndef UTILSFML_H_INCLUDED
#define UTILSFML_H_INCLUDED

#include <sstream>              //String
#include <string>               //To string
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

//GRAPHICS
bool CursorOnSprite(sf::RenderWindow &window, sf::Sprite &sprite);    //Si le curseur est sur le sprite

//NETWORK
bool sendMessage(std::string msgOut, sf::TcpSocket &socket);          //Envoie d'un texte à un socket(client ou serveur connecte a celui si)
std::string receivedMessage(sf::TcpSocket &socket);                   //Reception d'un texte d'un socket

//OTHER
int strToInt(std::string text);
std::string intToStr(int number);

#endif // UTILSFML_H_INCLUDED
