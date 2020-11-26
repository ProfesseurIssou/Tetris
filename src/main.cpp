//GameOver
//Point
//Nettoyage du code
//MultiJoueur

#include <iostream> //CIN COUT ENDL

#include <cstdlib> //Pour random
#include <SFML/Graphics.hpp>

using namespace sf;

//case = 18x18

//Definition de la taille du plateau
const int hauteur = 20;
const int largeur = 10;

//Generation du plateau avec que des 0 en couleur
struct{
  int color = 0;  //0 = pas de case, et apres c'est la couleur de la case
}plateau[largeur][hauteur];

//Generation de la piece avec que des 0
bool piece[4][4] = {0};//Une table de 4*4 remplis de 0
//On definie la position du cadre de la piece a 0x0 par rapport au plateau
int piecePosX = 0;
int piecePosY = 0;
//La couleur de la piece qui tombe
int pieceCouleur = 0;
/*
0 = vide
1 = bleu
2 = violet
3 = rouge
4 = vert
5 = jaune
6 = bleu clair
7 = orange
8 = bleu
*/
//Le type de la piece qui tombe
int typePiece;
/*
1 = I
2 = J
3 = L
4 = O
5 = S
6 = T
7 = Z
*/
//Sens de la piece [1;4]
int pieceSens = 1;

//On créé le timer du jeux pour fair descendre les piece
Clock gameTimer;
float delay = 0.5;//temp (en seconde) entre chaque update du jeux (descente de piece)

int random(int min, int max){ //range : [min, max]
   static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

/*On verifie si la piece peu etre a l'endroit demander*/
bool checkSuperposition(int futurePosX, int futurePosY){
  /*
  0 = ne superpose aucune case du plateau
  1 = superpose une case du plateau
  */

  //Pour chaque case de la piece
  for(int x=0;x<4;x++){
    for(int y=0;y<4;y++){
      //Si la case de la piece est utilisé
      if(piece[x][y] == 1){
        //On verifie si sa future position au niveau du plateau est utilisé
        if(plateau[piecePosX+x+futurePosX][piecePosY+y+futurePosY].color != 0){
          return 1;//Superpose une case
        }
      }
    }
  }
  return 0;//Ne superpose aucune case du plateau
}

/*GENERATION DE LA PIECE*/
bool pieceGenerateur(){
  //Retourne 1 si la piece est posé
  //Retourne 0 si la piece est bloquer

  //On met le sens de la piece a 1
  pieceSens = 1;
  //On genere la couleur
  pieceCouleur = random(1,8);
  //On genere le type de piece
  typePiece = random(1,7);
  /*
  1 = I
  2 = J
  3 = L
  4 = O
  5 = S
  6 = T
  7 = Z
  */

  //On definie la position du cadre de la piece a la moitier de l'ecran et 0
  piecePosX = largeur/2;
  piecePosY = 0;

  //On reinitialise la piece
  for(int x=0;x<4;x++){
    for(int y=0;y<4;y++){
      piece[x][y] = 0;
    }
  }

  //Generer la piece
  switch(typePiece){
    case 1://I
      piece[0][1] = 1;
      piece[1][1] = 1;
      piece[2][1] = 1;
      piece[3][1] = 1;
      break;
    case 2://J
      piece[1][1] = 1;
      piece[2][1] = 1;
      piece[3][1] = 1;
      piece[3][2] = 1;
      break;
    case 3://L
      piece[1][1] = 1;
      piece[2][1] = 1;
      piece[3][1] = 1;
      piece[1][2] = 1;
      break;
    case 4://O
      piece[1][1] = 1;
      piece[2][1] = 1;
      piece[1][2] = 1;
      piece[2][2] = 1;
      break;
    case 5://S
      piece[2][1] = 1;
      piece[3][1] = 1;
      piece[1][2] = 1;
      piece[2][2] = 1;
      break;
    case 6://T
      piece[1][1] = 1;
      piece[2][1] = 1;
      piece[3][1] = 1;
      piece[2][2] = 1;
      break;
    case 7://Z
      piece[1][1] = 1;
      piece[2][1] = 1;
      piece[2][2] = 1;
      piece[3][2] = 1;
      break;
  }

  //verifier si elle ne superpose pas une autre piece (on inverse pour retourner vrai si la piece c'est bien créé)
  return !checkSuperposition(piecePosX, piecePosY);
}

/*On regarde si on peu deplacer dans la direction demander*/
bool checkLateralMovement(int direction){
  //Pour chaque case du plateau
  for(int x=0;x<4;x++){
    for(int y=0;y<4;y++){
      //Si la case de la piece est pleine
      if(piece[x][y] == 1){
        //On regarde si la case du plateau est utilisé ou qu'il sort du plateau
        if(plateau[piecePosX+x+direction][piecePosY+y].color != 0 || piecePosX+x+direction<0 || piecePosX+x+direction>=largeur){
          return 0;//On ne peu pas faire le mouvement demander
        }
      }
    }
  }
  return 1;//Le mouvement peu etre effectuer
}

/*On regarde si on peu effectuer la rotation, si oui on la fait*/
bool rotation(){
  /*
  0 = a pus etre posé
  1 = n'a pas pus etre posé
  */
  //on cree la liste de la future piece
  bool futurePiece[4][4] = {0};
  //On genere la future piece
  switch(typePiece){
    case 1://I
      //On change la position
      pieceSens++;
      if(pieceSens > 2){
        pieceSens = 1;
      }
      //Pour chaque position
      switch(pieceSens){
        case 1:
          futurePiece[0][1] = 1;
          futurePiece[1][1] = 1;
          futurePiece[2][1] = 1;
          futurePiece[3][1] = 1;
          break;
        case 2:
          futurePiece[2][0] = 1;
          futurePiece[2][1] = 1;
          futurePiece[2][2] = 1;
          futurePiece[2][3] = 1;
          break;
      }
      break;
    case 2://J
      //On change la position
      pieceSens++;
      if(pieceSens > 4){
        pieceSens = 1;
      }
      //Pour chaque position
      switch(pieceSens){
        case 1:
          futurePiece[1][1] = 1;
          futurePiece[2][1] = 1;
          futurePiece[3][1] = 1;
          futurePiece[3][2] = 1;
          break;
        case 2:
          futurePiece[2][0] = 1;
          futurePiece[3][0] = 1;
          futurePiece[2][1] = 1;
          futurePiece[2][2] = 1;
          break;
        case 3:
          futurePiece[1][0] = 1;
          futurePiece[1][1] = 1;
          futurePiece[2][1] = 1;
          futurePiece[3][1] = 1;
          break;
        case 4:
          futurePiece[2][0] = 1;
          futurePiece[2][1] = 1;
          futurePiece[2][2] = 1;
          futurePiece[1][2] = 1;
          break;
      }
      break;
    case 3://L
      //On change la position
      pieceSens++;
      if(pieceSens > 4){
        pieceSens = 1;
      }
      //Pour chaque position
      switch(pieceSens){
        case 1:
          futurePiece[1][1] = 1;
          futurePiece[2][1] = 1;
          futurePiece[3][1] = 1;
          futurePiece[1][2] = 1;
          break;
        case 2:
          futurePiece[2][0] = 1;
          futurePiece[2][1] = 1;
          futurePiece[2][2] = 1;
          futurePiece[3][2] = 1;
          break;
        case 3:
          futurePiece[3][0] = 1;
          futurePiece[1][1] = 1;
          futurePiece[2][1] = 1;
          futurePiece[3][1] = 1;
          break;
        case 4:
          futurePiece[1][0] = 1;
          futurePiece[2][0] = 1;
          futurePiece[2][1] = 1;
          futurePiece[2][2] = 1;
          break;
      }
      break;
    case 4://O
      return 0;//on ne peu pas tourné la piece
      break;
    case 5://S
      //On change la position
      pieceSens++;
      if(pieceSens > 2){
        pieceSens = 1;
      }
      //Pour chaque position
      switch(pieceSens){
        case 1:
          futurePiece[2][1] = 1;
          futurePiece[3][1] = 1;
          futurePiece[1][2] = 1;
          futurePiece[2][2] = 1;
          break;
        case 2:
          futurePiece[1][0] = 1;
          futurePiece[1][1] = 1;
          futurePiece[2][1] = 1;
          futurePiece[2][2] = 1;
          break;
      }
      break;
    case 6://T
      //On change la position
      pieceSens++;
      if(pieceSens > 4){
        pieceSens = 1;
      }
      //Pour chaque position
      switch(pieceSens){
        case 1:
          futurePiece[1][1] = 1;
          futurePiece[2][1] = 1;
          futurePiece[3][1] = 1;
          futurePiece[2][2] = 1;
          break;
        case 2:
          futurePiece[2][0] = 1;
          futurePiece[1][1] = 1;
          futurePiece[2][1] = 1;
          futurePiece[2][2] = 1;
          break;
        case 3:
          futurePiece[2][0] = 1;
          futurePiece[1][1] = 1;
          futurePiece[2][1] = 1;
          futurePiece[3][1] = 1;
          break;
        case 4:
          futurePiece[2][0] = 1;
          futurePiece[2][1] = 1;
          futurePiece[3][1] = 1;
          futurePiece[2][2] = 1;
          break;
      }
      break;
    case 7://Z
      //On change la position
      pieceSens++;
      if(pieceSens > 2){
        pieceSens = 1;
      }
      //Pour chaque position
      switch(pieceSens){
        case 1:
          futurePiece[1][1] = 1;
          futurePiece[2][1] = 1;
          futurePiece[2][2] = 1;
          futurePiece[3][2] = 1;
          break;
        case 2:
          futurePiece[3][0] = 1;
          futurePiece[2][1] = 1;
          futurePiece[3][1] = 1;
          futurePiece[2][2] = 1;
          break;
      }
      break;
  }
  //On check si la piece se superpose a d'autre bloc ou qu'il touche le bord de la fenetre
  //Pour chaque case de la future piece
  for(int x=0;x<4;x++){
    for(int y=0;y<4;y++){
      //Si la case de la future piece est utilisé
      if(futurePiece[x][y] == 1){
        //On verifie si sa position au niveau du plateau est utilisé et que la case ne sort pas du plateau
        if(plateau[piecePosX+x][piecePosY+y].color != 0 || piecePosX+x<0 || piecePosX+x>largeur){
          return 0;//impossible de tourner la piece
        }
      }
    }
  }
  //On applique la rotation
  for(int x=0;x<4;x++){
    for(int y=0;y<4;y++){
      piece[x][y] = futurePiece[x][y];
    }
  }
  return 1;//La rotation c'est bien effectuer
}

/*On regarde si la piece peu descendre*/
bool checkDescentePiece(){
  /*
  0 = La piece ne peu pas descendre
  1 = La piece peu descendre
  */
  //Pour chaque case de la piece
  for(int x=0;x<4;x++){
    for(int y=0;y<4;y++){
      //On regarde si la case de la piece est utilisé
      if(piece[x][y] == 1){
        //On regarde si il y a une case en dessous de la case actuel ou que c'est le bas du plateau
        if(plateau[piecePosX+x][piecePosY+y+1].color != 0 || piecePosY+y == hauteur-1){
          return 0;//La piece ne peu plus descendre
        }

      }
    }
  }
  return 1;//La piece peu descendre
}

/*On fixe la piece au plateau*/
bool fixPiece(){
  /*
  0 = La piece n'a pas pus etre fixé
  1 = La piece a ete fixé
  */
  //Pour chaque case de la piece
  for(int x=0;x<4;x++){
    for(int y=0;y<4;y++){
      //Si la case de la piece est pleine
      if(piece[x][y] == 1){
        //On la definie comme la case du plateau
        plateau[piecePosX+x][piecePosY+y].color = pieceCouleur;

      }
    }
  }
  return 1;//La piece a bien été fixé
}

/*DASH*/
bool dashPiece(){
  //tant que la piece peu descendre
  while(checkDescentePiece()){
    piecePosY++;
  }
  //Sinon la piece est déposé
  //on fixe la piece
  fixPiece();
  //On genere une nouvelle piece
  pieceGenerateur();
}

int main(){
  // Creation de la fenetre de jeux
  RenderWindow gameWindow(VideoMode(320, 480), "Tetris");

  /*CREATION DES TEXTURES*/
  //On cree la texture des cases des block
  Texture tileTexture;
  //On charge la texture des cases des block
  tileTexture.loadFromFile("img/tiles.png");
  /*#####################*/

  /*CREATION DES SPRITES*/
  //On cree le sprite de la case du block
  Sprite tileSprite(tileTexture);
  /*#####################*/

  //On reinitialise le timer du jeux
  gameTimer.restart();

  //On genere la piece TEMPORAIRE
  pieceGenerateur();



  //Tant que le jeux tourne
  while(gameWindow.isOpen()){
    /*EVENEMENT*/
    //On recupere l'evenement de la fenetre de jeux
    Event e;
    //Tant qu'il y a un evenement
    while(gameWindow.pollEvent(e)){
      //Si on arrete la fenetre
      if(e.type == Event::Closed){
        //On ferme la fenetre
        gameWindow.close();
      }
      //Si une touche du clavier
      if(e.type == Event::KeyPressed){
        //Si la touche UP
        if(e.key.code == Keyboard::Up){
          //On verifie si on peu tourner la piece et si oui on tourne la piece
          rotation();
        }
        //Si la touche GAUCHE
        if(e.key.code == Keyboard::Left){
          //On check si on peu deplacer la piece vers la gauche
          if(checkLateralMovement(-1)){
            //On deplace toute les case qui bouge vers la gauche
            piecePosX--;
          }
        }
        //Si la touche DROITE
        if(e.key.code == Keyboard::Right){
          //On check si on peu deplacer la piece vers la droite
          if(checkLateralMovement(1)){
            //On deplace toute les case qui bouge vers la droite
            piecePosX++;
          }
        }
        //Si la touche DOWN
        if(e.key.code == Keyboard::Down){
          //On dash la piece
          dashPiece();
        }
      }
    }

    //Si on doit mettre a jour le plateau
    if(gameTimer.getElapsedTime().asSeconds() > delay){
      //On remet le timer a 0
      gameTimer.restart();


      /*CHECK SI LIGNE COMPLETE*/
      //Pour chaque ligne du plateau en partant du haut
      for(int y=0;y<hauteur;y++){
        //Nombre de case pleine dans la ligne
        int nbCasePleine = 0;
        for(int x=0;x<largeur;x++){
          //Si la case est pleine
          if(plateau[x][y].color != 0){
            //On ajoute 1 au nombre de case pleine dans la ligne
            nbCasePleine++;
          }
        }
        //Si la ligne est pleine
        if(nbCasePleine == largeur){
          //On efface la ligne
          for(int x=0;x<largeur;x++){
            //On efface la case
            plateau[x][y].color = 0;
          }
          //On baisse toute les case au dessus
          //Pour chaque ligne en partant de la ligne juste au dessus de la ligne actuel et on se deplace vers le haut
          for(int tempY=y-1;tempY>0;tempY--){
            //Pour chaque case de la ligne
            for(int x=0;x<largeur;x++){
              //On baisse la case du plateau de 1 case vers le bas
              plateau[x][tempY+1].color = plateau[x][tempY].color;
            }
          }
        }
      }
      /*#######################*/


      /*DESCENTE DE LA PIECE*/
      //On regarde si la piece peu descendre
      if(checkDescentePiece()){
        piecePosY++;
      }else{//Sinon la piece est déposé
        //on fixe la piece
        fixPiece();
        //On genere une nouvelle piece
        pieceGenerateur();
      }
      /*####################*/
    }

    /*AFFICHAGE*/
    //On efface l'ecran et on le remplis de blanc
    //gameWindow.clear(Color::White);
    gameWindow.clear(Color::Black);

    //Affichage du plateau
    for(int x=0;x<largeur;x++){
      for(int y=0;y<hauteur;y++){
        //On reinitialise le sprite
        Sprite tileSprite(tileTexture);
        //On verifie si la case existe
        if(plateau[x][y].color != 0){
          //On definie la couleur
          int caseColor = (plateau[x][y].color);
          tileSprite.setTextureRect(IntRect((caseColor-1)*18,0,18,18)); //COULEUR
          //On definie sa position
          tileSprite.setPosition(x*18,y*18);
          //On affiche la case
          gameWindow.draw(tileSprite);
        }
      }
    }

    //Affichage de la piece
    //on change la couleur du sprite en la couleur de la piece
    //on reinitialise le sprite
    Sprite tileSprite(tileTexture);
    //On definie la couleur
    tileSprite.setTextureRect(IntRect((pieceCouleur-1)*18,0,18,18)); //COULEUR
    for(int x=0;x<4;x++){
      for(int y=0;y<4;y++){
        //Si il y a une case pleine
        if(piece[x][y] == 1){
          //On definie sa position
          tileSprite.setPosition((x+piecePosX)*18,(y+piecePosY)*18);
          //On affiche la case
          gameWindow.draw(tileSprite);
        }
      }
    };

    //On affiche l'ecran
    gameWindow.display();
    /*#####################*/
  }
  return 0;
}
