#include "TetrisMenu.h"


TetrisMenu::TetrisMenu(sf::RenderWindow *window){
  gameWindow = window;    //On récupere l'ecran de jeux
}

void TetrisMenu::Menu(){
  /*INITIALISATION MENU*/
  bool actifMenu = true;
  backgroundTexture.loadFromFile("img/menu/background.png");
  buttonSinglePlayerTexture.loadFromFile("img/menu/Solo.png");
  buttonMultiPlayerTexture.loadFromFile("img/menu/Multiplayer.png");
  backgroundSprite.setTexture(backgroundTexture);
  buttonSinglePlayerSprite.setTexture(buttonSinglePlayerTexture);
  buttonMultiPlayerSprite.setTexture(buttonMultiPlayerTexture);
  buttonSinglePlayerSprite.setPosition(480,300);
  buttonMultiPlayerSprite.setPosition(480,400);

  /*MENU*/
  while(actifMenu){
    //CONDITION
    sf::Event e;
    while(gameWindow->pollEvent(e)){
      if(e.type == sf::Event::Closed){  //Si on ferme la fenetre
        actifMenu = false;              //On stop le menu
        gameWindow->close();             //On ferme l'ecrant de jeux
      }
      if(e.type == sf::Event::MouseButtonPressed){
        //Si le bouton solo est cliquer
        if(CursorOnSprite(*gameWindow,buttonSinglePlayerSprite)){
          multiplayer = 0;  //Mode solo
          actifMenu = 0;    //On stop le menu
        }
        //Si le bouton multi est cliquer
        if(CursorOnSprite(*gameWindow,buttonMultiPlayerSprite)){
          multiplayer = 1;  //Mode multi
          actifMenu = 0;    //On stop le menu
        }
      }
    }
    //Affichage
    gameWindow->clear();

    gameWindow->draw(backgroundSprite);
    gameWindow->draw(buttonSinglePlayerSprite);
    gameWindow->draw(buttonMultiPlayerSprite);

    gameWindow->display();
  }
}

void TetrisMenu::MultiplayerMenu(){
  /*INITIALISATION MENU*/
  bool actifMenu = true;
  backgroundTexture.loadFromFile("img/multiplayerMenu/background.png");
  buttonCreateTexture.loadFromFile("img/multiplayerMenu/create.png");
  inputFieldTexture.loadFromFile("img/multiplayerMenu/inputField.png");
  font.loadFromFile("other/font/Tetris.ttf");
  backgroundSprite.setTexture(backgroundTexture);
  buttonCreateSprite.setTexture(buttonCreateTexture);
  inputFieldSprite.setTexture(inputFieldTexture);

  buttonCreateSprite.setScale(0.5,0.5);
  inputFieldSprite.setScale(1,0.5);
  inputFieldSprite.setPosition(400,300);
  buttonCreateSprite.setPosition(480,400);

  sf::Text ipServerDisplay;                       //On cree le texte du score
  ipServerDisplay.setFont(font);                  //On definie la police du texte
  ipServerDisplay.setFillColor(sf::Color::Black); //Couleur de texte en blanc
  ipServerDisplay.setCharacterSize(45);           //On met la taille a 24Pixels
  ipServerDisplay.setPosition(495,305);           //On definie la position


  /*MENU*/
  while(actifMenu){
    //CONDITION
    sf::Event e;
    while(gameWindow->pollEvent(e)){
      if(e.type == sf::Event::Closed){  //Si on ferme la fenetre
        actifMenu = false;              //On stop le menu
        gameWindow->close();             //On ferme l'ecrant de jeux
      }
      if(e.type == sf::Event::MouseButtonPressed){
        //Si le bouton create est cliquer
        if(CursorOnSprite(*gameWindow,buttonCreateSprite)){
          actifMenu = false;
          mode = 0; //Mode server
        }
      }
      if(e.type == sf::Event::KeyPressed){
        if(e.key.code==sf::Keyboard::Enter){
          //On rejoin le srv
          actifMenu = false;
          mode = 1; //Mode client
        }
        if(e.key.code==sf::Keyboard::BackSpace && ipServer.length() != 0){
          //On retire une case de l'ip
          ipServer = ipServer.substr(0, ipServer.size()-1);
        }
        if(e.key.code==sf::Keyboard::Numpad0){
          //On ajoute le caractere a l'ip
          ipServer += "0";
        }
        if(e.key.code==sf::Keyboard::Numpad1){
          //On ajoute le caractere a l'ip
          ipServer += "1";
        }
        if(e.key.code==sf::Keyboard::Numpad2){
          //On ajoute le caractere a l'ip
          ipServer += "2";
        }
        if(e.key.code==sf::Keyboard::Numpad3){
          //On ajoute le caractere a l'ip
          ipServer += "3";
        }
        if(e.key.code==sf::Keyboard::Numpad4){
          //On ajoute le caractere a l'ip
          ipServer += "4";
        }
        if(e.key.code==sf::Keyboard::Numpad5){
          //On ajoute le caractere a l'ip
          ipServer += "5";
        }
        if(e.key.code==sf::Keyboard::Numpad6){
          //On ajoute le caractere a l'ip
          ipServer += "6";
        }
        if(e.key.code==sf::Keyboard::Numpad7){
          //On ajoute le caractere a l'ip
          ipServer += "7";
        }
        if(e.key.code==sf::Keyboard::Numpad8){
          //On ajoute le caractere a l'ip
          ipServer += "8";
        }
        if(e.key.code==sf::Keyboard::Numpad9){
          //On ajoute le caractere a l'ip
          ipServer += "9";
        }
      }
    }
    //Affichage
    gameWindow->clear();

    gameWindow->draw(backgroundSprite);
    gameWindow->draw(inputFieldSprite);
    gameWindow->draw(buttonCreateSprite);
    ipServerDisplay.setString(ipServer);    //On definie le texte
    gameWindow->draw(ipServerDisplay);       //On affiche le texte


    gameWindow->display();
  }
}
