//Taille piece
//Dash animation
//Point
//MultiJoueur

#include <iostream> //CIN COUT ENDL

#include <cstdlib> //Pour random
#include <string> //Pour les string
#include <SFML/Graphics.hpp>

/*VARIABLE GLOBAL*/
const unsigned int gameScreenHauteur = 1000;//Taille en pixel en hauteur
const unsigned int gameScreenLargeur = 1250;//Taille en pixel en largeur
const unsigned int boardPositionX = 432;    //Position du plateau sur l'ecran (pour les piece)
const unsigned int boardPositionY = 93;     //Position du plateau sur l'ecran (pour les piece)
struct boardStruct{
  unsigned int board[20][10];   //Plateau de données(0 = vide sinon couleur de la case)
  unsigned int hauteur = 20;    //Hauteur du plateau
  unsigned int largeur = 10;    //Largeur plateau
};
struct pieceStruct{
  bool cases[4][4];         //Toute les case de la piece
  int posX = 0;             //Position de la piece par rapport au plateau
  int posY = 0;             //Position de la piece par rapport au plateau
  int type;                 //Type de la piece(1=I,2=J,3=L,4=O,5=S,6=T,7=Z)
  int sens = 1;             //Sens de 1 a 4 max
  int color;                //La couleur de la piece(0=vide,1=bleu,2=violet,3=rouge,4=vert,5=jaune,6=bleu clair,7=orange,8=bleu)
};

sf::RenderWindow gameWindow;  //Ecran de jeux
sf::Texture backgroundTexture;//Texture du fond
sf::Texture tileTexture;      //Texture des case (18x18)
sf::Sprite fondSprite;        //Sprite du fond
sf::Sprite tileSprite;        //Sprite de la case
/*###############*/

int Random(int min, int max){ //range : [min, max]
   static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

void ResetPlateau(struct boardStruct &plateau){ //On remet chaque valeur du plateau a 0
  for(unsigned int y=0;y<plateau.hauteur;y++){    //Pour chaque ligne du plateau
    for(unsigned int x=0;x<plateau.largeur;x++){    //Pour chaque case de la ligne
      plateau.board[y][x] = 0;                        //On vide la case
    }
  }
}

void ResetPiece(struct pieceStruct &piece){     //On reinitialise la piece
  piece.posX = 0;        //On remet la position à 0
  piece.posY = 0;        //On remet la position à 0
  for(int y=0;y<4;y++){   //Pour chaque ligne de la piece
    for(int x=0;x<4;x++){   //Pour chaque case de la ligne
      piece.cases[y][x] = 0; //On vide la case
    }
  }
}

void SetPiece(struct pieceStruct &piece){       //On definie les case de la piece selon sont type et sont sens
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

bool CheckSuperposition(struct pieceStruct &piece,struct boardStruct &plateau,int prmFuturePosX, int prmFuturePosY){//Si la piece superpose une case du plateau ou sort du plateau
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

bool PieceGenerator(struct pieceStruct &piece, struct boardStruct &plateau){      //Generation de la piece
  /*
    Vrai = la piece a ete pose
    False = la piece n'a pas ete pose
  */
  ResetPiece(piece);      //On reset la piece (valeur par defaut)

  piece.sens = 1;                 //On remet le sens de la piece par defaut
  piece.color = Random(1,8);      //On prend une couleur aleatoire
  piece.type = Random(1,7);       //On prend un type de piece aleatoire
  piece.posX = plateau.largeur/2; //On centre la piece par rapport au plateau
  piece.posY = 0;                 //On met la piece tout en haut du plateau

  SetPiece(piece);    //On genere le paterne de la nouvelle piece

  return !CheckSuperposition(piece,plateau,piece.posX,piece.posY);  //On retourne si la piece peut etre pose ou non
}

bool Rotation(struct pieceStruct &piece, struct boardStruct &plateau){            //Rotation de la piece
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
  SetPiece(piece);            //On genere la piece
  if(CheckSuperposition(piece,plateau,piece.posX,piece.posY)){//Si la piece superpose une case du plateau (na pas pus etre genere)
    piece.sens = oldSens;                                       //On remet l'ancien sens de la piece
    SetPiece(piece);                                            //On genere l'ancienne piece
    return 0;                                                   //N'a pas ete pose
  }
  return 1; //A ete pose
}

bool LateralMovement(struct pieceStruct &piece, struct boardStruct &plateau,int direction){ //Mouvement lateral de la piece
  /*
  0 = La piece n'a pas ete place
  1 = La piece a ete place
  */
  if(!CheckSuperposition(piece,plateau,piece.posX + direction, piece.posY)){  //Si on peut deplace la piece dans la direction demande
    piece.posX = piece.posX + direction;  //On applique le mouvement lateral
    return 1; //La piece a ete place
  }
  return 0; //La piece n'a pas ete place
}

bool CheckDescentePiece(struct pieceStruct &piece, struct boardStruct &plateau){  //Si la piece peut descendre
  /*
  0 = ne peut pas descendre
  1 = peut descendre
  */
  return !CheckSuperposition(piece,plateau,piece.posX,piece.posY+1);  //Si la piece qui descent superposera une case
}

void FixPiece(struct pieceStruct &piece, struct boardStruct &plateau){  //On fixe la piece au plateau
  for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
    for(int x=0;x<4;x++){ //Pour chaque case de la ligne
      if(piece.cases[y][x] == 1){ //Si la case est utilise
        plateau.board[piece.posY+y][piece.posX+x] = piece.color;  //On definie la case du plateau a la couleur de la case de la piece
      }
    }
  }
}

void Dash(struct pieceStruct &piece, struct boardStruct &plateau){  //On dash la piece
  while(CheckDescentePiece(piece,plateau)){  //Tant que la piece peut descendre
    piece.posY++;                 //On descent la piece de 1
  }
  FixPiece(piece,plateau);  //On fixe la piece
  PieceGenerator(piece,plateau);  //On genere une nouvelle piece
}

void UpdateDisplay(struct pieceStruct &piece, struct boardStruct &plateau){ //Mise a jour de l'affichage du terrain
  gameWindow.clear(sf::Color::Black); //On efface l'ecran et on le remplis de noir

  //Affichage du plateau
  gameWindow.draw(fondSprite);            //On affiche le plateau
  for(int y=0;y<plateau.hauteur;y++){     //Pour chaque ligne du plateau
    for(int x=0;x<plateau.largeur;x++){     //Pour chaque case de la ligne
      tileSprite.setTexture(tileTexture);     //On reinitialise le sprite
      if(plateau.board[y][x] != 0){           //Si la case du plateau est utilise
        int caseColor = (plateau.board[y][x]);  //On prend la couleur de la case(18x18)
        tileSprite.setTextureRect(sf::IntRect((caseColor-1)*18,0,18,18)); //COULEUR
        tileSprite.setPosition(boardPositionX+(x*18),boardPositionY+(y*18));//Position de la case
        gameWindow.draw(tileSprite);            //On affiche la case
      }
    }
  }

  //Affichage de la piece
  tileSprite.setTexture(tileTexture); //On reinitialise la couleur des cases
  tileSprite.setTextureRect(sf::IntRect((piece.color-1)*18,0,18,18)); //COULEUR
  for(int y=0;y<4;y++){               //Pour chaque ligne de la piece
    for(int x=0;x<4;x++){               //Pour chaque case de la ligne
      if(piece.cases[y][x] == 1){         //Si la case est utilise
        tileSprite.setPosition(boardPositionX+(x+piece.posX)*18,boardPositionY+(y+piece.posY)*18);//On definie la position a celle de la case
        gameWindow.draw(tileSprite);        //On affiche la case
      }
    }
  }

  gameWindow.display(); //On affiche l'ecran
}

int main(){
  /*INITIALISATION JEUX*/
  bool gameRunning = true;  //Si le jeu tourne
  gameWindow.create(sf::VideoMode(gameScreenLargeur,gameScreenHauteur),"Tetris");  //On créé l'ecran de jeux

  /*JEUX*/
  while (gameRunning){        //Tant que le jeux tourne
    /*MENU*/

    /*####*/

    /*INITIALISATION PARTIE*/
    bool partyRunning = true;   //Si la partie tourne
    struct boardStruct plateau;   //On créé le plateau
    struct pieceStruct piece;     //On créé la piece
    sf::Clock gameTimer;            //Temp entre chaque update du jeux
    float delay = 0.5;          //Temp à attendre avant de faire une update

    ResetPlateau(plateau);  //On reset le plateau à 0(vide)
    ResetPiece(piece);      //On reset la piece (valeur par defaut)

    backgroundTexture.loadFromFile("img/background.png");   //On charge la texture du fond
    tileTexture.loadFromFile("img/tiles.png");              //On charge la texture de toute les cases
    fondSprite.setTexture(backgroundTexture);             //On definie la texture du fond
    tileSprite.setTexture(tileTexture);                   //On definie la texture des cases

    gameTimer.restart();            //On remet a 0 le timer de la partie
    PieceGenerator(piece,plateau);  //On genere la premiere piece

    /*PARTIE*/
    while (partyRunning){ //Tant que la partie tourne
      sf::Event e;          //On recupere l'evenement
      while(gameWindow.pollEvent(e)){ //Pour chaque evenement
        if(e.type == sf::Event::Closed){//Si on ferme la fenetre
          partyRunning = false;           //On stop la partie
          gameRunning = false;            //On stop le jeux
          gameWindow.close();             //On ferme l'ecrant de jeux
        }
        if(e.type == sf::Event::KeyPressed){//Si l'evenement est une touche du clavier
          if(e.key.code == sf::Keyboard::Up){   //Si la touche HAUT est presse
            Rotation(piece,plateau);              //On effectue la rotation
          }
          if(e.key.code == sf::Keyboard::Left){ //Si la touche GAUCHE est presse
            LateralMovement(piece,plateau,-1);    //On deplace la piece vers la gauche
          }
          if(e.key.code == sf::Keyboard::Right){//Si la touche DROITE est presse
            LateralMovement(piece,plateau,1);     //On deplace la piece vers la droite
          }
          if(e.key.code == sf::Keyboard::Down){ //Si la touche BAS est press�
            Dash(piece,plateau);                  //On dash la piece
          }
        }
      }
      if(gameTimer.getElapsedTime().asSeconds() > delay){ //Si on doit mettre a jour le plateau
        gameTimer.restart();  //On remet le timer a 0
        /*CHECK SI LIGNE COMPLETE*/
        for(int y=0;y<plateau.hauteur;y++){ //Pour chaque ligne du plateau en partant du haut
          int nbCasePleine = 0;               //Nombre de case utilise par ligne
          for(int x=0;x<plateau.largeur;x++){ //Pour chaque case de la ligne
            if(plateau.board[y][x] != 0){       //Si la case du plateau est utilise
              nbCasePleine++;                     //On ajoute 1 au nombre de case utilise dans la ligne
            }
          }
          if(nbCasePleine == plateau.largeur){//Si la ligne est entiere
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


        /*DESCENTE DE LA PIECE*/
        if(CheckDescentePiece(piece,plateau)){  //Si la piece peut descendre
          piece.posY++;                           //On descent la piece
        }else{                                  //Sinon la piece est depose
          FixPiece(piece,plateau);                //On fixe la piece
          bool isCreated = PieceGenerator(piece,plateau); //On genere une nouvelle piece
          if(isCreated == false){                 //Si la piece ne peut pas etre place
            partyRunning = false;                   //Partie finie : Perdu
          }
        }
        /*####################*/


    }

      UpdateDisplay(piece,plateau); //On met a jour l'affichage
    }
  }
  return 0;
}
