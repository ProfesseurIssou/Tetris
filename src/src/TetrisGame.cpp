#include "TetrisGame.h"

TetrisGame::TetrisGame(sf::RenderWindow *window){
  gameWindow = window;    //On récupere l'ecran de jeux
}

int TetrisGame::Random(int min, int max){ //range : [min, max]
   static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

void TetrisGame::ResetPlateau(){ //On remet chaque valeur du plateau a 0
  for(unsigned int y=0;y<plateau.hauteur;y++){    //Pour chaque ligne du plateau
    for(unsigned int x=0;x<plateau.largeur;x++){    //Pour chaque case de la ligne
      plateau.board[y][x] = 0;                        //On vide la case
    }
  }
}

void TetrisGame::ResetPiece(){     //On reinitialise la piece
  piece.posX = 0;        //On remet la position à 0
  piece.posY = 0;        //On remet la position à 0
  for(int y=0;y<4;y++){   //Pour chaque ligne de la piece
    for(int x=0;x<4;x++){   //Pour chaque case de la ligne
      piece.cases[y][x] = 0; //On vide la case
    }
  }
}

void TetrisGame::SetPiece(){       //On definie les case de la piece selon sont type et sont sens
  //[y][x]
  for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
    for(int x=0;x<4;x++){ //Pour chaque case de la ligne
      piece.cases[y][x] = 0;//On vide la case
    }
  }
  switch(piece.type){  //Pour chaque type de piece
    case 1://I
      switch(piece.sens){ //Pour chaque sens de la piece
        case 1:
          piece.cases[1][0] = 1;
          piece.cases[1][1] = 1;
          piece.cases[1][2] = 1;
          piece.cases[1][3] = 1;
          break;
        case 2:
          piece.cases[0][2] = 1;
          piece.cases[1][2] = 1;
          piece.cases[2][2] = 1;
          piece.cases[3][2] = 1;
          break;
      }
      break;
    case 2://J
      switch(piece.sens){ //Pour chaque sens de la piece
        case 1:
          piece.cases[1][1] = 1;
          piece.cases[1][2] = 1;
          piece.cases[1][3] = 1;
          piece.cases[2][3] = 1;
          break;
        case 2:
          piece.cases[0][2] = 1;
          piece.cases[0][3] = 1;
          piece.cases[1][2] = 1;
          piece.cases[2][2] = 1;
          break;
        case 3:
          piece.cases[0][1] = 1;
          piece.cases[1][1] = 1;
          piece.cases[1][2] = 1;
          piece.cases[1][3] = 1;
          break;
        case 4:
          piece.cases[0][2] = 1;
          piece.cases[1][2] = 1;
          piece.cases[2][2] = 1;
          piece.cases[2][1] = 1;
          break;
      }
      break;
    case 3://L
      switch(piece.sens){ //Pour chaque sens de la piece
        case 1:
          piece.cases[1][1] = 1;
          piece.cases[1][2] = 1;
          piece.cases[1][3] = 1;
          piece.cases[2][1] = 1;
          break;
        case 2:
          piece.cases[0][2] = 1;
          piece.cases[1][2] = 1;
          piece.cases[2][2] = 1;
          piece.cases[2][3] = 1;
          break;
        case 3:
          piece.cases[0][3] = 1;
          piece.cases[1][1] = 1;
          piece.cases[1][2] = 1;
          piece.cases[1][3] = 1;
          break;
        case 4:
          piece.cases[0][1] = 1;
          piece.cases[0][2] = 1;
          piece.cases[1][2] = 1;
          piece.cases[2][2] = 1;
          break;
      }
      break;
    case 4://O  Ne tourne pas
      piece.cases[1][1] = 1;
      piece.cases[1][2] = 1;
      piece.cases[2][1] = 1;
      piece.cases[2][2] = 1;
      break;
    case 5://S
      switch(piece.sens){ //Pour chaque sens de la piece
        case 1:
          piece.cases[1][2] = 1;
          piece.cases[1][3] = 1;
          piece.cases[2][1] = 1;
          piece.cases[2][2] = 1;
          break;
        case 2:
          piece.cases[0][1] = 1;
          piece.cases[1][1] = 1;
          piece.cases[1][2] = 1;
          piece.cases[2][2] = 1;
          break;
      }
      break;
    case 6://T
      switch(piece.sens){ //Pour chaque sens de la piece
        case 1:
          piece.cases[1][1] = 1;
          piece.cases[1][2] = 1;
          piece.cases[1][3] = 1;
          piece.cases[2][2] = 1;
          break;
        case 2:
          piece.cases[0][2] = 1;
          piece.cases[1][1] = 1;
          piece.cases[1][2] = 1;
          piece.cases[2][2] = 1;
          break;
        case 3:
          piece.cases[0][2] = 1;
          piece.cases[1][1] = 1;
          piece.cases[1][2] = 1;
          piece.cases[1][3] = 1;
          break;
        case 4:
          piece.cases[0][2] = 1;
          piece.cases[1][2] = 1;
          piece.cases[1][3] = 1;
          piece.cases[2][2] = 1;
          break;
      }
      break;
    case 7://Z
      switch(piece.sens){ //Pour chaque sens de la piece
        case 1:
          piece.cases[1][1] = 1;
          piece.cases[1][2] = 1;
          piece.cases[2][2] = 1;
          piece.cases[2][3] = 1;
          break;
        case 2:
          piece.cases[0][3] = 1;
          piece.cases[1][2] = 1;
          piece.cases[1][3] = 1;
          piece.cases[2][2] = 1;
          break;
      }
      break;
  }
}

bool TetrisGame::CheckSuperposition(int prmFuturePosX, int prmFuturePosY){//Si la piece superpose une case du plateau ou sort du plateau
  /*
    Vrai = La piece superpose
    False = La piece ne superpose pas
  */
  for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
    for(int x=0;x<4;x++){ //Pour chaque valeur de la ligne
      //Si la case de la piece est utilise ET que sa future position est utilise
      if(piece.cases[y][x] == 1 && (plateau.board[y+prmFuturePosY][x+prmFuturePosX] != 0 || x+prmFuturePosX < 0 || x+prmFuturePosX >= plateau.largeur || y+prmFuturePosY < 0 || y+prmFuturePosY >= plateau.hauteur)){
        return 1; //La piece superposera une case du plateau ou sort du plateau
      }
    }
  }
  return 0; //Ne superpose aucune case du plateau
}

bool TetrisGame::PieceGenerator(){      //Generation de la piece
  /*
    Vrai = la piece a ete pose
    False = la piece n'a pas ete pose
  */
  ResetPiece();      //On reset la piece (valeur par defaut)

  piece.sens = 1;                 //On remet le sens de la piece par defaut
  piece.color = Random(1,8);      //On prend une couleur aleatoire
  piece.type = Random(1,7);       //On prend un type de piece aleatoire
  piece.posX = plateau.largeur/2; //On centre la piece par rapport au plateau
  piece.posY = 0;                 //On met la piece tout en haut du plateau

  SetPiece();    //On genere le paterne de la nouvelle piece

  return !CheckSuperposition(piece.posX,piece.posY);  //On retourne si la piece peut etre pose ou non
}

bool TetrisGame::Rotation(){            //Rotation de la piece
  /*
  0 = a pus etre pose
  1 = n'a pas pus etre pose
  */
  int oldSens = piece.sens;   //On sauvegarde l'ancien sens de la piece si on ne peu pas la pose
  switch(piece.type){         //Pour chaque type de piece
    case 1://I
      piece.sens++;           //Position suivante
      if(piece.sens > 2){       //Si tour complet
        piece.sens = 1;           //Sens par defaut
      }
      break;
    case 2://J
      piece.sens++;           //Position suivante
      if(piece.sens > 4){       //Si tour complet
        piece.sens = 1;           //Sens par defaut
      }
      break;
    case 3://L
      piece.sens++;           //Position suivante
      if(piece.sens > 4){       //Si tour complet
        piece.sens = 1;           //Sens par defaut
      }
      break;
    //O  Ne tourne pas
    case 5://S
      piece.sens++;           //Position suivante
      if(piece.sens > 2){       //Si tour complet
        piece.sens = 1;           //Sens par defaut
      }
      break;
    case 6://T
      piece.sens++;           //Position suivante
      if(piece.sens > 4){       //Si tour complet
        piece.sens = 1;           //Sens par defaut
      }
      break;
    case 7://Z
      piece.sens++;           //Position suivante
      if(piece.sens > 2){       //Si tour complet
        piece.sens = 1;           //Sens par defaut
      }
      break;
  }
  SetPiece();            //On genere la piece
  if(CheckSuperposition(piece.posX,piece.posY)){//Si la piece superpose une case du plateau (na pas pus etre genere)
    piece.sens = oldSens;                                       //On remet l'ancien sens de la piece
    SetPiece();                                            //On genere l'ancienne piece
    return 0;                                                   //N'a pas ete pose
  }
  return 1; //A ete pose
}

bool TetrisGame::LateralMovement(int direction){ //Mouvement lateral de la piece
  /*
  0 = La piece n'a pas ete place
  1 = La piece a ete place
  */
  if(!CheckSuperposition(piece.posX + direction, piece.posY)){  //Si on peut deplace la piece dans la direction demande
    piece.posX = piece.posX + direction;  //On applique le mouvement lateral
    return 1; //La piece a ete place
  }
  return 0; //La piece n'a pas ete place
}

bool TetrisGame::CheckDescentePiece(){  //Si la piece peut descendre
  /*
  0 = ne peut pas descendre
  1 = peut descendre
  */
  return !CheckSuperposition(piece.posX,piece.posY+1);  //Si la piece qui descent superposera une case
}

void TetrisGame::FixPiece(){  //On fixe la piece au plateau
  for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
    for(int x=0;x<4;x++){ //Pour chaque case de la ligne
      if(piece.cases[y][x] == 1){ //Si la case est utilise
        plateau.board[piece.posY+y][piece.posX+x] = piece.color;  //On definie la case du plateau a la couleur de la case de la piece
      }
    }
  }
}

void TetrisGame::UpdateDisplay(){ //Mise a jour de l'affichage du terrain
  gameWindow->clear(sf::Color::Black); //On efface l'ecran et on le remplis de noir

  //Affichage du plateau
  gameWindow->draw(backgroundSprite);    //On affiche le plateau
  for(int y=0;y<plateau.hauteur;y++){     //Pour chaque ligne du plateau
    for(int x=0;x<plateau.largeur;x++){     //Pour chaque case de la ligne
      tileSprite.setTexture(tileTexture);     //On reinitialise le sprite
      if(plateau.board[y][x] != 0){           //Si la case du plateau est utilise
        int caseColor = (plateau.board[y][x]);  //On prend la couleur de la case(18x18)
        tileSprite.setTextureRect(sf::IntRect((caseColor-1)*18,0,18,18)); //COULEUR
        tileSprite.setPosition(boardPositionX+(x*18*caseScaleX),boardPositionY+(y*18*caseScaleY));//Position de la case
        gameWindow->draw(tileSprite);            //On affiche la case
      }
    }
  }

  //Affichage de la piece
  tileSprite.setTexture(tileTexture); //On reinitialise la couleur des cases
  tileSprite.setTextureRect(sf::IntRect((piece.color-1)*18,0,18,18)); //COULEUR
  for(int y=0;y<4;y++){               //Pour chaque ligne de la piece
    for(int x=0;x<4;x++){               //Pour chaque case de la ligne
      if(piece.cases[y][x] == 1){         //Si la case est utilise
        tileSprite.setPosition(boardPositionX+(x+piece.posX)*18*caseScaleX,boardPositionY+(y+piece.posY)*18*caseScaleY);//On definie la position a celle de la case
        gameWindow->draw(tileSprite);        //On affiche la case
      }
    }
  }

  //Affichage du score
  sf::Text scoreText;                       //On cree le texte du score
  scoreText.setFont(font);                  //On definie la police du texte
  scoreText.setFillColor(sf::Color::White); //Couleur de texte en blanc
  scoreText.setCharacterSize(45);           //On met la taille a 24Pixels
  scoreText.setPosition(870,50);            //On definie la position
  std::string tempText;             //Variable temporaire pour preparer le texte du score
  tempText = std::to_string(score); //On passe le score en texte
  while(tempText.size() < 6){       //Tant que le texte du score n'est pas egal a 6 caractere
    tempText = "0"+tempText;          //On ajoute un 0 avant le score
  }
  scoreText.setString(tempText);    //On definie le texte du score
  gameWindow->draw(scoreText);       //On affiche le texte du score

  //Afficher le level
  sf::Text levelText;                       //On cree le texte du level
  levelText.setFont(font);                  //On definie la police du texte
  levelText.setFillColor(sf::Color::White); //Couleur de texte en blanc
  levelText.setCharacterSize(45);           //On met la taille a 24Pixels
  levelText.setPosition(1075,112);          //On definie la position
  tempText = std::to_string(level); //On passe le level en texte
  while(tempText.size() < 3){       //Tant que le texte du level n'est pas egal a 3 caractere
    tempText = "0"+tempText;          //On ajoute un 0 avant le level
  }
  levelText.setString(tempText);    //On definie le texte du level
  gameWindow->draw(levelText);       //On affiche le texte du level

  //Afficher le nombre de ligne
  sf::Text lineText;                       //On cree le texte du nombre de lignes
  lineText.setFont(font);                  //On definie la police du texte
  lineText.setFillColor(sf::Color::White); //Couleur de texte en blanc
  lineText.setCharacterSize(45);           //On met la taille a 24Pixels
  lineText.setPosition(738,16);          //On definie la position
  tempText = std::to_string(totalClearedLine); //On passe le nombre de lignes en texte
  while(tempText.size() < 3){       //Tant que le texte du nombre de lignes n'est pas egal a 3 caractere
    tempText = "0"+tempText;          //On ajoute un 0 avant le nombre de lignes
  }
  lineText.setString(tempText);    //On definie le texte du nombre de lignes
  gameWindow->draw(lineText);       //On affiche le texte du nombre de lignes

  gameWindow->display(); //On affiche l'ecran
}

void TetrisGame::Dash(){  //On dash la piece
  while(CheckDescentePiece()){  //Tant que la piece peut descendre
    piece.posY++;                   //On descent la piece de 1
    UpdateDisplay();   //On met a jour l'affichage
    sf::sleep(sf::milliseconds(10));//On attend 10ms
  }
  FixPiece();  //On fixe la piece
  PieceGenerator();  //On genere une nouvelle piece
}

bool TetrisGame::PlaySolo(){
  /*INITIALISATION PARTIE*/
  //STATES
  bool partyRunning = true;   //Tant que la partie tourne
  bool windowClosed = false;  //Si la fenetre a ete fermer

  //VARIABLES
  float delay = 0.50;         //Temp à attendre avant de faire une update
  unsigned int nbClearedLine=0;   //Nombre de ligne nettoyees dans la frame

  totalClearedLine = 0;           //Nombre total de ligne nettoyees
  level = 0;                      //Level actuel
  score  = 0;                     //Score de la partie

  //SFML VARIABLES
  sf::Clock gameTimer;        //Temp entre chaque update du jeux

  ResetPlateau();  //On reset le plateau à 0(vide)
  ResetPiece();      //On reset la piece (valeur par defaut)

  backgroundTexture.loadFromFile("img/game/background.png");   //On charge la texture du fond
  tileTexture.loadFromFile("img/game/tiles.png");              //On charge la texture de toute les cases
  backgroundSprite.setTexture(backgroundTexture);             //On definie la texture du fond
  tileSprite.setTexture(tileTexture);                   //On definie la texture des cases
  tileSprite.setScale(caseScaleX,caseScaleY);             //Echelle de la piece
  font.loadFromFile("other/font/Tetris.ttf");             //On charge la police

  gameTimer.restart();            //On remet a 0 le timer de la partie
  PieceGenerator();  //On genere la premiere piece

  /*PARTIE*/
  while(partyRunning && windowClosed == false){  //Tant que la partie tourne et que la fenetre n'est pas fermer
    sf::Event e;          //On recupere l'evenement
    while(gameWindow->pollEvent(e)){ //Pour chaque evenement
      if(e.type == sf::Event::Closed){//Si on ferme la fenetre
        partyRunning = false;           //On stop la partie
        windowClosed = true;            //On stop le jeux
        gameWindow->close();             //On ferme l'ecrant de jeux
      }
      if(e.type == sf::Event::KeyPressed){//Si l'evenement est une touche du clavier
        if(e.key.code == sf::Keyboard::Up){   //Si la touche HAUT est presse
          Rotation();              //On effectue la rotation
        }
        if(e.key.code == sf::Keyboard::Left){ //Si la touche GAUCHE est presse
          LateralMovement(-1);    //On deplace la piece vers la gauche
        }
        if(e.key.code == sf::Keyboard::Right){//Si la touche DROITE est presse
          LateralMovement(1);     //On deplace la piece vers la droite
        }
        if(e.key.code == sf::Keyboard::Down){ //Si la touche BAS est press�
          Dash();                  //On dash la piece
        }
      }
    }
    if(gameTimer.getElapsedTime().asSeconds() > delay){ //Si on doit mettre a jour le plateau
      gameTimer.restart();  //On remet le timer a 0

      /*CHECK SI LIGNE COMPLETE*/
      unsigned int nbLineErased = 0;      //Nombre de ligne efface
      for(int y=0;y<plateau.hauteur;y++){ //Pour chaque ligne du plateau en partant du haut
        int nbCasePleine = 0;               //Nombre de case utilise par ligne
        for(int x=0;x<plateau.largeur;x++){ //Pour chaque case de la ligne
          if(plateau.board[y][x] != 0){       //Si la case du plateau est utilise
            nbCasePleine++;                     //On ajoute 1 au nombre de case utilise dans la ligne
          }
        }
        if(nbCasePleine == plateau.largeur){//Si la ligne est entiere
          nbLineErased++;                     //On ajoute 1 a la ligne efface
          for(int x=0;x<plateau.largeur;x++){ //Pour chaque case de la ligne
            plateau.board[y][x] = 0;            //On efface la case
          }
          for(int tempY=y-1;tempY>0;tempY--){ //Pour chaque ligne en partant de la ligne juste au dessus

            for(int x=0;x<plateau.largeur;x++){ //Pour chaque case de la ligne
              plateau.board[tempY+1][x] = plateau.board[tempY][x];//On deplace la valeur a la case juste en dessous
            }
          }
        }
      }
      /*#######################*/

      /*CALCUL DU SCORE*/
      switch(nbLineErased){ //Pour chaque nombre de ligne efface
        case 1: //Une lignes
          score = score + 40*(level+1);
          break;
        case 2: //Deux lignes
          score = score + 100*(level+1);
          break;
        case 3: //Trois lignes
          score = score + 300*(level+1);
          break;
        case 4: //Quatre lignes
          score = score + 1200*(level+1);
          break;
      }
      /*###############*/

      /*LEVEL SYSTEM*/
      if(nbLineErased != 0){  //Si il y a eu des lignes nettoyees
        totalClearedLine += nbLineErased; //On ajoute le nombre de ligne vide
        if(totalClearedLine-(10*level) >= 10){//Si le nombre total de ligne nettoyees moins le nombre de ligne nettoyees pour atteindre le niveau est superieur ou egal a 10 (donc level suivant)
          level++;  //Level suivant
        }
      }
      if(level < 10){ //Level de 0 a 9
        delay = 0.50-(level*0.05);
      }
      if((10 <= level) && (level < 13)){//Level de 10 a 12
        delay = 0.4;
      }
      if((13 <= level) && (level < 16)){//Level de 13 a 15
        delay = 0.3;
      }
      if((16 <= level) && (level < 19)){//Level de 16 a 18
        delay = 0.2;
      }
      if(19 <= level){//Level a partir de 19
        delay = 0.1;
      }
      /*############*/

      /*DESCENTE DE LA PIECE*/
      if(CheckDescentePiece()){  //Si la piece peut descendre
        piece.posY++;                           //On descent la piece
      }else{                                  //Sinon la piece est depose
        FixPiece();                //On fixe la piece
        bool isCreated = PieceGenerator(); //On genere une nouvelle piece
        if(isCreated == false){                 //Si la piece ne peut pas etre place
          partyRunning = false;                   //Partie finie : Perdu
        }
      }
      /*####################*/
    }

    UpdateDisplay(); //On met a jour l'affichage
  }
  return windowClosed;  //On retourne si la fenetre est fermer
}

void TetrisGame::UpdateDisplayMulti(int nbTotalPlayer,int nbAlivePlayer,int classement){ //Mise a jour de l'affichage du terrain en mode multi
  gameWindow->clear(sf::Color::Black); //On efface l'ecran et on le remplis de noir

  //Affichage du plateau
  gameWindow->draw(backgroundSprite);    //On affiche le plateau
  for(int y=0;y<plateau.hauteur;y++){     //Pour chaque ligne du plateau
    for(int x=0;x<plateau.largeur;x++){     //Pour chaque case de la ligne
      tileSprite.setTexture(tileTexture);     //On reinitialise le sprite
      if(plateau.board[y][x] != 0){           //Si la case du plateau est utilise
        int caseColor = (plateau.board[y][x]);  //On prend la couleur de la case(18x18)
        tileSprite.setTextureRect(sf::IntRect((caseColor-1)*18,0,18,18)); //COULEUR
        tileSprite.setPosition(boardPositionX+(x*18*caseScaleX),boardPositionY+(y*18*caseScaleY));//Position de la case
        gameWindow->draw(tileSprite);            //On affiche la case
      }
    }
  }

  //Affichage de la piece
  tileSprite.setTexture(tileTexture); //On reinitialise la couleur des cases
  tileSprite.setTextureRect(sf::IntRect((piece.color-1)*18,0,18,18)); //COULEUR
  for(int y=0;y<4;y++){               //Pour chaque ligne de la piece
    for(int x=0;x<4;x++){               //Pour chaque case de la ligne
      if(piece.cases[y][x] == 1){         //Si la case est utilise
        tileSprite.setPosition(boardPositionX+(x+piece.posX)*18*caseScaleX,boardPositionY+(y+piece.posY)*18*caseScaleY);//On definie la position a celle de la case
        gameWindow->draw(tileSprite);        //On affiche la case
      }
    }
  }

  //Affichage du score
  sf::Text scoreText;                       //On cree le texte du score
  scoreText.setFont(font);                  //On definie la police du texte
  scoreText.setFillColor(sf::Color::White); //Couleur de texte en blanc
  scoreText.setCharacterSize(45);           //On met la taille a 24Pixels
  scoreText.setPosition(870,50);            //On definie la position
  std::string tempText;             //Variable temporaire pour preparer le texte du score
  tempText = std::to_string(score); //On passe le score en texte
  while(tempText.size() < 6){       //Tant que le texte du score n'est pas egal a 6 caractere
    tempText = "0"+tempText;          //On ajoute un 0 avant le score
  }
  scoreText.setString(tempText);    //On definie le texte du score
  gameWindow->draw(scoreText);       //On affiche le texte du score

  //Afficher le level
  sf::Text levelText;                       //On cree le texte du level
  levelText.setFont(font);                  //On definie la police du texte
  levelText.setFillColor(sf::Color::White); //Couleur de texte en blanc
  levelText.setCharacterSize(45);           //On met la taille a 24Pixels
  levelText.setPosition(1075,112);          //On definie la position
  tempText = std::to_string(level); //On passe le level en texte
  while(tempText.size() < 3){       //Tant que le texte du level n'est pas egal a 3 caractere
    tempText = "0"+tempText;          //On ajoute un 0 avant le level
  }
  levelText.setString(tempText);    //On definie le texte du level
  gameWindow->draw(levelText);       //On affiche le texte du level

  //Afficher le nombre de ligne
  sf::Text lineText;                       //On cree le texte du nombre de lignes
  lineText.setFont(font);                  //On definie la police du texte
  lineText.setFillColor(sf::Color::White); //Couleur de texte en blanc
  lineText.setCharacterSize(45);           //On met la taille a 24Pixels
  lineText.setPosition(738,16);          //On definie la position
  tempText = std::to_string(totalClearedLine); //On passe le nombre de lignes en texte
  while(tempText.size() < 3){       //Tant que le texte du nombre de lignes n'est pas egal a 3 caractere
    tempText = "0"+tempText;          //On ajoute un 0 avant le nombre de lignes
  }
  lineText.setString(tempText);    //On definie le texte du nombre de lignes
  gameWindow->draw(lineText);       //On affiche le texte du nombre de lignes

  //Afficher le nombre de joueur
  sf::Text playerText;                      //On cree le texte du level
  playerText.setFont(font);                 //On definie la police du texte
  playerText.setFillColor(sf::Color::White);//Couleur de texte en blanc
  playerText.setCharacterSize(45);          //On met la taille a 24Pixels
  playerText.setPosition(150,112);          //On definie la position
  playerText.setString(intToStr(nbAlivePlayer)+"/"+intToStr(nbTotalPlayer));//On definie le texte du level
  gameWindow->draw(playerText);             //On affiche le texte du level

  //Afficher le classement
  sf::Text ClassementText;                  //On cree le texte du level
  ClassementText.setFont(font);             //On definie la police du texte
  ClassementText.setFillColor(sf::Color::White);//Couleur de texte en blanc
  ClassementText.setCharacterSize(45);      //On met la taille a 24Pixels
  ClassementText.setPosition(150,200);      //On definie la position
  ClassementText.setString(intToStr(classement)+"/"+intToStr(nbTotalPlayer));//On definie le texte du level
  gameWindow->draw(ClassementText);         //On affiche le texte du level

  gameWindow->display(); //On affiche l'ecran
}

bool TetrisGame::PlayMultiServer(Server *server){
  /*INITIALISATION PARTIE*/
  //STATES
  bool partyRunning = true;   //Tant que la partie tourne
  bool windowClosed = false;  //Si la fenetre a ete fermer

  //VARIABLES
  float delay = 0.50;         //Temp à attendre avant de faire une update
  unsigned int nbClearedLine=0;   //Nombre de ligne nettoyees dans la frame

  totalClearedLine = 0;           //Nombre total de ligne nettoyees
  level = 0;                      //Level actuel
  score  = 0;                     //Score de la partie

  int nbTotalPlayer;              //Nombre de joueur au total
  int nbAlivePlayer;              //Nombre de joueur non mort
  int classement = 0;             //Position dans le classement
  bool lastDash = false;          //Si c'est nous qui avons fait les dernier dash

  sf::Packet sendPacket;          //On cree le packet d'envoie

  //SFML VARIABLES
  sf::Clock gameTimer;        //Temp entre chaque update du jeux

  ResetPlateau();  //On reset le plateau à 0(vide)
  ResetPiece();      //On reset la piece (valeur par defaut)

  backgroundTexture.loadFromFile("img/game/background.png");   //On charge la texture du fond
  tileTexture.loadFromFile("img/game/tiles.png");              //On charge la texture de toute les cases
  backgroundSprite.setTexture(backgroundTexture);             //On definie la texture du fond
  tileSprite.setTexture(tileTexture);                   //On definie la texture des cases
  tileSprite.setScale(caseScaleX,caseScaleY);             //Echelle de la piece
  font.loadFromFile("other/font/Tetris.ttf");             //On charge la police

  gameTimer.restart();            //On remet a 0 le timer de la partie
  PieceGenerator();  //On genere la premiere piece

  /*ENVOIE DU NOMBRE DE JOUEUR AU TOTAL*/
  sendPacket << intToStr(server->clientsList.size()+1);//On met l'information de demarrage
  for(int i=0;i<server->clientsList.size();i++){ //Pour chaque client de la liste
    server->sendPacket(i,sendPacket);            //On envoie un packet de demarrage a chaque client
  }
  sendPacket.clear();                         //On vide le packet
  nbTotalPlayer = server->clientsList.size()+1;
  nbAlivePlayer = nbTotalPlayer;
  /*###################################*/

  /*PARTIE*/
  while(partyRunning && windowClosed == false){  //Tant que la partie tourne et que la fenetre n'est pas fermer
    /*RECEPTION DES CLIENTS*/
    int posClient;                            //Position du client qui nous envoie une données
    posClient = server->getPosClientRequests();//On recupere la position du client qui nous envoie une données
    if(posClient != -1){                      //Si on a bien un client qui nous envoie une données
      sf::Packet receivePacket;                 //On prepare le packet a recevoir
      std::string message;                      //Le pseudo du client qui nous envoie une données
      receivePacket = server->receivePacket(posClient);//On recupere le packet que le client nous a envoyer
      receivePacket >> message;                 //On extrait le packet
      if(message == "DASH"){                    //Si c'est le message de dash
        lastDash = false;                         //On debloque le dash
        Dash();                                   //On dash
        sendPacket << "DASH";                     //On met les données dans le packet
        for(int i=0;i<server->clientsList.size();i++){//Pour chaque client de la liste
          if(i!=posClient){                         //Si ce n'est pas le client de base
            server->sendPacket(i,sendPacket);          //On envoie le packet au client
          }
        }
        sendPacket.clear();                         //On vide le packet
      }
      if(message == "DIE"){                       //Si un joueur est mort
        nbAlivePlayer--;                          //On baisse de 1 le nombre de joueur en vie
        sendPacket << "DIE";                      //On met les données dans le packet
        for(int i=0;i<server->clientsList.size();i++){//Pour chaque client de la liste
          if(i!=posClient){                         //Si ce n'est pas le client de base
            server->sendPacket(i,sendPacket);          //On envoie le packet au client
          }
        }
        sendPacket.clear();                         //On vide le packet
      }
    }
    /*##############*/

    sf::Event e;          //On recupere l'evenement
    while(gameWindow->pollEvent(e)){ //Pour chaque evenement
      if(e.type == sf::Event::Closed){//Si on ferme la fenetre
        partyRunning = false;           //On stop la partie
        windowClosed = true;            //On stop le jeux
        gameWindow->close();             //On ferme l'ecrant de jeux
      }
      if(e.type == sf::Event::KeyPressed){//Si l'evenement est une touche du clavier
        if(e.key.code == sf::Keyboard::Up){   //Si la touche HAUT est presse
          Rotation();              //On effectue la rotation
        }
        if(e.key.code == sf::Keyboard::Left){ //Si la touche GAUCHE est presse
          LateralMovement(-1);    //On deplace la piece vers la gauche
        }
        if(e.key.code == sf::Keyboard::Right){//Si la touche DROITE est presse
          LateralMovement(1);     //On deplace la piece vers la droite
        }
        if(e.key.code == sf::Keyboard::Down && (lastDash == false || nbAlivePlayer == 1)){ //Si la touche BAS est presse et que nous ne somme pas le dernier dash fait OU que nous somme tout seul
          lastDash = true;          //On bloque le dash (pour evite le spam) tant qu'un autre joueur n'a pas dash
          Dash();                   //On dash la piece
          sendPacket << "DASH";                         //On met l'information du dash
          for(int i=0;i<server->clientsList.size();i++){//Pour chaque client de la liste
            server->sendPacket(i,sendPacket);           //On envoie un packet de demarrage a chaque client
          }
          sendPacket.clear();                         //On vide le packet
        }
      }
    }
    if(gameTimer.getElapsedTime().asSeconds() > delay){ //Si on doit mettre a jour le plateau
      gameTimer.restart();  //On remet le timer a 0

      /*CHECK SI LIGNE COMPLETE*/
      unsigned int nbLineErased = 0;      //Nombre de ligne efface
      for(int y=0;y<plateau.hauteur;y++){ //Pour chaque ligne du plateau en partant du haut
        int nbCasePleine = 0;               //Nombre de case utilise par ligne
        for(int x=0;x<plateau.largeur;x++){ //Pour chaque case de la ligne
          if(plateau.board[y][x] != 0){       //Si la case du plateau est utilise
            nbCasePleine++;                     //On ajoute 1 au nombre de case utilise dans la ligne
          }
        }
        if(nbCasePleine == plateau.largeur){//Si la ligne est entiere
          nbLineErased++;                     //On ajoute 1 a la ligne efface
          for(int x=0;x<plateau.largeur;x++){ //Pour chaque case de la ligne
            plateau.board[y][x] = 0;            //On efface la case
          }
          for(int tempY=y-1;tempY>0;tempY--){ //Pour chaque ligne en partant de la ligne juste au dessus

            for(int x=0;x<plateau.largeur;x++){ //Pour chaque case de la ligne
              plateau.board[tempY+1][x] = plateau.board[tempY][x];//On deplace la valeur a la case juste en dessous
            }
          }
        }
      }
      /*#######################*/

      /*CALCUL DU SCORE*/
      switch(nbLineErased){ //Pour chaque nombre de ligne efface
        case 1: //Une lignes
          score = score + 40*(level+1);
          break;
        case 2: //Deux lignes
          score = score + 100*(level+1);
          break;
        case 3: //Trois lignes
          score = score + 300*(level+1);
          break;
        case 4: //Quatre lignes
          score = score + 1200*(level+1);
          break;
      }
      /*###############*/

      /*LEVEL SYSTEM*/
      if(nbLineErased != 0){  //Si il y a eu des lignes nettoyees
        totalClearedLine += nbLineErased; //On ajoute le nombre de ligne vide
        if(totalClearedLine-(10*level) >= 10){//Si le nombre total de ligne nettoyees moins le nombre de ligne nettoyees pour atteindre le niveau est superieur ou egal a 10 (donc level suivant)
          level++;  //Level suivant
        }
      }
      if(level < 10){ //Level de 0 a 9
        delay = 0.50-(level*0.05);
      }
      if((10 <= level) && (level < 13)){//Level de 10 a 12
        delay = 0.4;
      }
      if((13 <= level) && (level < 16)){//Level de 13 a 15
        delay = 0.3;
      }
      if((16 <= level) && (level < 19)){//Level de 16 a 18
        delay = 0.2;
      }
      if(19 <= level){//Level a partir de 19
        delay = 0.1;
      }
      /*############*/

      /*DESCENTE DE LA PIECE*/
      if(CheckDescentePiece()){  //Si la piece peut descendre
        piece.posY++;                           //On descent la piece
      }else{                                  //Sinon la piece est depose
        FixPiece();                //On fixe la piece
        bool isCreated = PieceGenerator(); //On genere une nouvelle piece
        if(isCreated == false){                 //Si la piece ne peut pas etre place
          classement = nbAlivePlayer;             //On definie le classement du joueur
          nbAlivePlayer--;                        //On baisse le nombre de joueur vivant
          partyRunning = false;                   //Partie finie : Perdu
        }
      }
      /*####################*/
    }

    UpdateDisplayMulti(nbTotalPlayer,nbAlivePlayer,classement); //On met a jour l'affichage
  }
  //JOUEUR MORT
  //On envoie le packet a tout les client
  sendPacket << "DIE";            //On met la donnee de mort dans le packet
  for(int i=0;i<server->clientsList.size();i++){//Pour chaque client de la liste
    server->sendPacket(i,sendPacket);             //On envoie le packet au client
  }
  sendPacket.clear();                         //On vide le packet
  while(nbAlivePlayer != 0){      //Tant qu'il reste des joueur
    /*RECEPTION DES CLIENTS*/
    int posClient;                            //Position du client qui nous envoie une données
    posClient = server->getPosClientRequests();//On recupere la position du client qui nous envoie une données
    if(posClient != -1){                      //Si on a bien un client qui nous envoie une données
      sf::Packet receivePacket;                 //On prepare le packet a recevoir
      std::string message;                      //Le pseudo du client qui nous envoie une données
      receivePacket = server->receivePacket(posClient);//On recupere le packet que le client nous a envoyer
      receivePacket >> message;                 //On extrait le packet
      if(message == "DASH"){                    //Si c'est le message de dash
        sendPacket << "DASH";                     //On met les données dans le packet
        for(int i=0;i<server->clientsList.size();i++){//Pour chaque client de la liste
          if(i!=posClient){                         //Si ce n'est pas le client de base
            server->sendPacket(i,sendPacket);          //On envoie le packet au client
          }
        }
        sendPacket.clear();                         //On vide le packet
      }
      if(message == "DIE"){                       //Si un joueur est mort
        nbAlivePlayer--;                          //On baisse de 1 le nombre de joueur en vie
        sf::Packet sendPacket;                    //On prepare un packet a envoyer
        sendPacket << "DIE";                      //On met les données dans le packet
        for(int i=0;i<server->clientsList.size();i++){//Pour chaque client de la liste
          if(i!=posClient){                         //Si ce n'est pas le client de base
            server->sendPacket(i,sendPacket);          //On envoie le packet au client
          }
        }
        sendPacket.clear();                         //On vide le packet
      }
    }
    /*##############*/
    //On affiche le jeux
    sf::Event e;          //On recupere l'evenement
    while(gameWindow->pollEvent(e)){ //Pour chaque evenement
      if(e.type == sf::Event::Closed){//Si on ferme la fenetre
        partyRunning = false;           //On stop la partie
        windowClosed = true;            //On stop le jeux
        gameWindow->close();             //On ferme l'ecrant de jeux
      }
    }
    UpdateDisplayMulti(nbTotalPlayer,nbAlivePlayer,classement);
  }
  return windowClosed;  //On retourne si la fenetre est fermer
}

bool TetrisGame::PlayMultiClient(Client *client){
  /*INITIALISATION PARTIE*/
  //STATES
  bool partyRunning = true;   //Tant que la partie tourne
  bool windowClosed = false;  //Si la fenetre a ete fermer

  //VARIABLES
  float delay = 0.50;         //Temp à attendre avant de faire une update
  unsigned int nbClearedLine=0;   //Nombre de ligne nettoyees dans la frame

  totalClearedLine = 0;           //Nombre total de ligne nettoyees
  level = 0;                      //Level actuel
  score  = 0;                     //Score de la partie

  int nbTotalPlayer = 0;          //Nombre de joueur au total
  int nbAlivePlayer = 0;          //Nombre de joueur non mort
  int classement = 0;             //Position dans le classement
  bool lastDash = false;          //Si c'est nous qui avons fait les dernier dash

  sf::Packet sendPacket;          //Packet a envoyer

  //SFML VARIABLES
  sf::Clock gameTimer;        //Temp entre chaque update du jeux

  ResetPlateau();  //On reset le plateau à 0(vide)
  ResetPiece();      //On reset la piece (valeur par defaut)

  backgroundTexture.loadFromFile("img/game/background.png");   //On charge la texture du fond
  tileTexture.loadFromFile("img/game/tiles.png");              //On charge la texture de toute les cases
  backgroundSprite.setTexture(backgroundTexture);             //On definie la texture du fond
  tileSprite.setTexture(tileTexture);                   //On definie la texture des cases
  tileSprite.setScale(caseScaleX,caseScaleY);             //Echelle de la piece
  font.loadFromFile("other/font/Tetris.ttf");             //On charge la police

  gameTimer.restart();            //On remet a 0 le timer de la partie
  PieceGenerator();  //On genere la premiere piece

  /*RECEPTION DU NOMBRE DE JOUEUR AU TOTAL*/
  while(nbTotalPlayer == 0){      //Tant qu'on a pas recus le packet
    if(client->haveReceivePacket()){ //Si on recois le packet du nombre de joeur au total
      std::string message;
      client->receivePacket >> message;  //On recupere le message
      nbTotalPlayer = strToInt(message);//On stocke le nombre de joueur total
    }
  }
  nbAlivePlayer = nbTotalPlayer;
  /*######################################*/

  /*PARTIE*/
  while(partyRunning && windowClosed == false){  //Tant que la partie tourne et que la fenetre n'est pas fermer
    /*RECEPTION DU SERVEUR*/
    if(client->haveReceivePacket()){ //Si on recois le packet de dash
      std::string message;
      client->receivePacket >> message;//On recupere le message
      if(message == "DASH"){          //Si c'est le message de dash
        lastDash = false;               //On debloque le dash
        Dash();                         //On dash
      }
      if(message == "DIE"){           //Si un joueur est mort
        nbAlivePlayer--;              //On baisse de 1 le nombre de joueur en vie
      }
    }
    /*##############*/

    sf::Event e;          //On recupere l'evenement
    while(gameWindow->pollEvent(e)){ //Pour chaque evenement
      if(e.type == sf::Event::Closed){//Si on ferme la fenetre
        partyRunning = false;           //On stop la partie
        windowClosed = true;            //On stop le jeux
        gameWindow->close();             //On ferme l'ecrant de jeux
      }
      if(e.type == sf::Event::KeyPressed){//Si l'evenement est une touche du clavier
        if(e.key.code == sf::Keyboard::Up){   //Si la touche HAUT est presse
          Rotation();              //On effectue la rotation
        }
        if(e.key.code == sf::Keyboard::Left){ //Si la touche GAUCHE est presse
          LateralMovement(-1);    //On deplace la piece vers la gauche
        }
        if(e.key.code == sf::Keyboard::Right){//Si la touche DROITE est presse
          LateralMovement(1);     //On deplace la piece vers la droite
        }
        if(e.key.code == sf::Keyboard::Down && (lastDash == false || nbAlivePlayer == 1)){ //Si la touche BAS est presse et que nous ne somme pas le dernier dash fait OU que nous somme tout seul
          lastDash = true;          //On bloque le dash (pour evite le spam) tant qu'un autre joueur n'a pas dash
          Dash();                   //On dash la piece
          sendPacket << "DASH";     //Le message du DASH
          client->sendPacket(sendPacket);//On envoie le packet au serveur
          sendPacket.clear();                         //On vide le packet
        }
      }
    }
    if(gameTimer.getElapsedTime().asSeconds() > delay){ //Si on doit mettre a jour le plateau
      gameTimer.restart();  //On remet le timer a 0

      /*CHECK SI LIGNE COMPLETE*/
      unsigned int nbLineErased = 0;      //Nombre de ligne efface
      for(int y=0;y<plateau.hauteur;y++){ //Pour chaque ligne du plateau en partant du haut
        int nbCasePleine = 0;               //Nombre de case utilise par ligne
        for(int x=0;x<plateau.largeur;x++){ //Pour chaque case de la ligne
          if(plateau.board[y][x] != 0){       //Si la case du plateau est utilise
            nbCasePleine++;                     //On ajoute 1 au nombre de case utilise dans la ligne
          }
        }
        if(nbCasePleine == plateau.largeur){//Si la ligne est entiere
          nbLineErased++;                     //On ajoute 1 a la ligne efface
          for(int x=0;x<plateau.largeur;x++){ //Pour chaque case de la ligne
            plateau.board[y][x] = 0;            //On efface la case
          }
          for(int tempY=y-1;tempY>0;tempY--){ //Pour chaque ligne en partant de la ligne juste au dessus

            for(int x=0;x<plateau.largeur;x++){ //Pour chaque case de la ligne
              plateau.board[tempY+1][x] = plateau.board[tempY][x];//On deplace la valeur a la case juste en dessous
            }
          }
        }
      }
      /*#######################*/

      /*CALCUL DU SCORE*/
      switch(nbLineErased){ //Pour chaque nombre de ligne efface
        case 1: //Une lignes
          score = score + 40*(level+1);
          break;
        case 2: //Deux lignes
          score = score + 100*(level+1);
          break;
        case 3: //Trois lignes
          score = score + 300*(level+1);
          break;
        case 4: //Quatre lignes
          score = score + 1200*(level+1);
          break;
      }
      /*###############*/

      /*LEVEL SYSTEM*/
      if(nbLineErased != 0){  //Si il y a eu des lignes nettoyees
        totalClearedLine += nbLineErased; //On ajoute le nombre de ligne vide
        if(totalClearedLine-(10*level) >= 10){//Si le nombre total de ligne nettoyees moins le nombre de ligne nettoyees pour atteindre le niveau est superieur ou egal a 10 (donc level suivant)
          level++;  //Level suivant
        }
      }
      if(level < 10){ //Level de 0 a 9
        delay = 0.50-(level*0.05);
      }
      if((10 <= level) && (level < 13)){//Level de 10 a 12
        delay = 0.4;
      }
      if((13 <= level) && (level < 16)){//Level de 13 a 15
        delay = 0.3;
      }
      if((16 <= level) && (level < 19)){//Level de 16 a 18
        delay = 0.2;
      }
      if(19 <= level){//Level a partir de 19
        delay = 0.1;
      }
      /*############*/

      /*DESCENTE DE LA PIECE*/
      if(CheckDescentePiece()){  //Si la piece peut descendre
        piece.posY++;                           //On descent la piece
      }else{                                  //Sinon la piece est depose
        FixPiece();                //On fixe la piece
        bool isCreated = PieceGenerator(); //On genere une nouvelle piece
        if(isCreated == false){                 //Si la piece ne peut pas etre place
          classement = nbAlivePlayer;             //On definie le classement du joueur
          nbAlivePlayer--;                        //On baisse le nombre de joueur vivant
          partyRunning = false;                   //Partie finie : Perdu
        }
      }
      /*####################*/
    }

    UpdateDisplayMulti(nbTotalPlayer,nbAlivePlayer,classement); //On met a jour l'affichage
  }
  //JOUEUR MORT
  //On envoie le packet au serveur
  sendPacket << "DIE";            //On met la donnee de mort dans le packet
  client->sendPacket(sendPacket); //On envoie le packet
  sendPacket.clear();                         //On vide le packet
  while(nbAlivePlayer != 0){      //Tant qu'il reste des joueur
    /*RECEPTION DU SERVEUR*/
    if(client->haveReceivePacket()){ //Si on recois le packet de dash
      std::string message;
      client->receivePacket >> message;//On recupere le message
      if(message == "DIE"){           //Si un joueur est mort
        nbAlivePlayer--;              //On baisse de 1 le nombre de joueur en vie
      }
    }
    /*##############*/
    //On affiche le jeux
    sf::Event e;          //On recupere l'evenement
    while(gameWindow->pollEvent(e)){ //Pour chaque evenement
      if(e.type == sf::Event::Closed){//Si on ferme la fenetre
        partyRunning = false;           //On stop la partie
        windowClosed = true;            //On stop le jeux
        gameWindow->close();             //On ferme l'ecrant de jeux
      }
    }
    UpdateDisplayMulti(nbTotalPlayer,nbAlivePlayer,classement);
  }
  return windowClosed;  //On retourne si la fenetre est fermer
}
