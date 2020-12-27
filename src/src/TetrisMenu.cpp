#include "TetrisMenu.h"


TetrisMenu::TetrisMenu(sf::RenderWindow *window){
  gameWindow = window;    //On récupere l'ecran de jeux
}

void TetrisMenu::Menu(){
  /*INITIALISATION MENU*/
  modeMenu = 0;         //On met le menu principale
  backgroundTexture.loadFromFile("img/menu/background.png");
  buttonSinglePlayerTexture.loadFromFile("img/menu/Solo.png");
  buttonMultiPlayerTexture.loadFromFile("img/menu/Multiplayer.png");
  backgroundSprite.setTexture(backgroundTexture);
  buttonSinglePlayerSprite.setTexture(buttonSinglePlayerTexture);
  buttonMultiPlayerSprite.setTexture(buttonMultiPlayerTexture);
  buttonSinglePlayerSprite.setPosition(480,300);
  buttonMultiPlayerSprite.setPosition(480,400);

  /*MENU*/
  //CONDITION
  sf::Event e;
  while(gameWindow->pollEvent(e)){
    if(e.type == sf::Event::Closed){  //Si on ferme la fenetre
      gameWindow->close();             //On ferme l'ecrant de jeux
    }
    if(e.type == sf::Event::MouseButtonPressed){
      //Si le bouton solo est cliquer
      if(CursorOnSprite(*gameWindow,buttonSinglePlayerSprite)){
        modeMenu = -1;    //On quitte le menu
        multiplayer = 0;  //Mode solo
      }
      //Si le bouton multi est cliquer
      if(CursorOnSprite(*gameWindow,buttonMultiPlayerSprite)){
        modeMenu = 1;     //On passe sur le menu pour rejoindre un serveur
        multiplayer = 1;  //Mode multi
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

void TetrisMenu::MultiplayerMenu(){
  /*INITIALISATION MENU*/
  modeMenu = 1;         //On met le menu pour rejoindre un serveur
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

  sf::Text ipServerDisplay;                       //On cree le text de l'input de l'ip du serveur
  ipServerDisplay.setFont(font);                  //On definie la police du texte
  ipServerDisplay.setFillColor(sf::Color::Black); //Couleur de texte en blanc
  ipServerDisplay.setCharacterSize(45);           //On met la taille a 24Pixels
  ipServerDisplay.setPosition(495,305);           //On definie la position


  /*MENU*/
  //CONDITION
  sf::Event e;
  while(gameWindow->pollEvent(e)){
    if(e.type == sf::Event::Closed){  //Si on ferme la fenetre
      gameWindow->close();             //On ferme l'ecrant de jeux
    }
    if(e.type == sf::Event::MouseButtonPressed){
      //Si le bouton create est cliquer
      if(CursorOnSprite(*gameWindow,buttonCreateSprite)){
        modeMenu = 2;     //Menu ou on attend les clients (mode serveur)
        mode = 0; //Mode server
      }
    }
    if(e.type == sf::Event::KeyPressed){
      if(e.key.code==sf::Keyboard::Enter){//On rejoin le srv
        modeMenu = 3;     //On attend les clients (mode client)
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
      if(e.key.code==sf::Keyboard::Period || e.key.code==sf::Keyboard::Unknown){
        //On ajoute le caractere a l'ip
        ipServer += ".";
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


void TetrisMenu::MultiplayerServerMenu(int nbPlayer){
  /*INITIALISATION MENU*/
  modeMenu = 2;         //On met le menu pour attendre les client (mode serveur)
  backgroundTexture.loadFromFile("img/multiplayerMenu/background.png");
  buttonPlayTexture.loadFromFile("img/multiplayerMenu/Server/Play.png");
  font.loadFromFile("other/font/Tetris.ttf");
  backgroundSprite.setTexture(backgroundTexture);
  buttonPlaySprite.setTexture(buttonPlayTexture);

  sf::Text nbPlayerText;                          //On cree le texte du nombre de joeur
  nbPlayerText.setFont(font);                     //On definie la police du texte
  nbPlayerText.setFillColor(sf::Color::White);    //Couleur de texte en blanc
  nbPlayerText.setCharacterSize(60);              //On met la taille a 24Pixels
  nbPlayerText.setPosition(495,305);              //On definie la position

  buttonPlaySprite.setScale(1,1);
  buttonPlaySprite.setPosition(480,400);


  /*MENU*/
  //CONDITION
  sf::Event e;
  while(gameWindow->pollEvent(e)){
    if(e.type == sf::Event::Closed){  //Si on ferme la fenetre
      gameWindow->close();             //On ferme l'ecrant de jeux
    }
    if(e.type == sf::Event::MouseButtonPressed){
      //Si le bouton play est cliquer
      if(CursorOnSprite(*gameWindow,buttonPlaySprite)){
        modeMenu = -1;    //On quitte le menu
      }
    }
  }

  nbPlayerText.setString(intToStr(nbPlayer)+" players");

  //Affichage
  gameWindow->clear();

  gameWindow->draw(backgroundSprite);
  gameWindow->draw(buttonPlaySprite);
  gameWindow->draw(nbPlayerText);

  gameWindow->display();
}


void TetrisMenu::MultiplayerClientMenu(){
  /*INITIALISATION MENU*/
  modeMenu = 3;         //On met le menu pour attendre les client (mode client)
  backgroundTexture.loadFromFile("img/multiplayerMenu/background.png");
  font.loadFromFile("other/font/Tetris.ttf");
  backgroundSprite.setTexture(backgroundTexture);

  sf::Text waitText;                              //On cree le texte du nombre de joeur
  waitText.setFont(font);                         //On definie la police du texte
  waitText.setFillColor(sf::Color::White);        //Couleur de texte en blanc
  waitText.setCharacterSize(45);                  //On met la taille a 24Pixels
  waitText.setPosition(485,305);                  //On definie la position


  /*MENU*/
  //CONDITION
  sf::Event e;
  while(gameWindow->pollEvent(e)){
    if(e.type == sf::Event::Closed){  //Si on ferme la fenetre
      gameWindow->close();             //On ferme l'ecrant de jeux
    }
  }

  waitText.setString("Connected : please wait ...");

  //Affichage
  gameWindow->clear();

  gameWindow->draw(backgroundSprite);
  gameWindow->draw(waitText);

  gameWindow->display();
}
