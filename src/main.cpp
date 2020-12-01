//Point
//MultiJoueur

#include <iostream> //CIN COUT ENDL


#include <cstdlib> //Pour random
#include <SFML/Graphics.hpp>

int random(int min, int max){ //range : [min, max]
   static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}


//case = 18x18
class Tetris{
  public:
    /*VARIABLES*/
    const int hauteur = 20; //Taille du plateau
    const int largeur = 10; //Taille du plateau

    int plateau[largeur][hauteur];  //0 = pas de case, et apres c'est la couleur de la case

    int piecePosX = 0;  //Position de la piece
    int piecePosY = 0;  //Position de la piece

    int pieceCouleur = 0; //Couleur de la piece
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

    sf::Clock gameTimer;  //Timer entre chaque descente de la piece
    float delay = 0.5;    //temp (en seconde) entre chaque update du jeux (descente de piece)

    sf::RenderWindow gameWindow(sf::VideoMode(320, 480), "Tetris"); //On cree l'ecran de jeux
    sf::Texture backgroundTexture;  //Texture du fond
    backgroundTexture.loadFromFile("img/Board.png");  //On charge la texture du fond
    sf::Texture tileTexture;  //Texture de la case des block
    tileTexture.loadFromFile("img/tiles.png");  //On charge la texture de la case
    sf::Sprite fondSprite(backgroundTexture); //Sprite du fond
    sf::Sprite tileSprite(tileTexture); //Sprite de la case

    /*FUNCTIONS*/
    bool pieceGenerateur(){ //Generation de la piece
      /*
      1 si la piece est posé
      0 si la piece est bloquer
      */
      pieceSens = 1;  //Sens a 1
      pieceCouleur = random(1,8); //Couleur aleatoire
      typePiece = random(1,7);  //Type de piece aleatoire
      /*
      1 = I
      2 = J
      3 = L
      4 = O
      5 = S
      6 = T
      7 = Z
      */
      piecePosX = largeur/2;  //Centre de l'ecran X
      piecePosY = 0;  //En haut de l'ecran
      for(int y=0;y<4;y++){ //Pour chaque ligne
        for(int x=0;x<4;x++){ //Pour chaque valeur
          piece[x][y] = 0;    //On reinitialise la piece
        }
      }
      switch(typePiece){  //Generation de chaque type de piece
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
      return !checkSuperposition(piecePosX, piecePosY); //Verification si superposition d'une case du plateau
    }
    bool checkLateralMovement(int direction){ //Si on peut déplacer la piece dans la direction demandé
      for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
        for(int x=0;x<4;x++){ //Pour chaque valeur de la ligne
          if(piece[x][y] == 1 && (plateau[piecePosX+x+direction][piecePosY+y] != 0 || piecePosX+x+direction<0 || piecePosX+x+direction>=largeur)){  //Si la case de la piece est pleine ET (La future case est utilisé OU sort du plateau)
            return 0; //Le mouvement lateral est impossible
          }
        }
      }
      return 1; //Le mouvement peu etre effectuer
    }
    bool rotation(){  //Effectuer la rotation
      /*
      0 = a pus etre posé
      1 = n'a pas pus etre posé
      */
      bool futurePiece[4][4] = {0}; //Future piece
      switch(typePiece){  //Pour chaque type de piece
        case 1://I
          pieceSens++;    //Sens suivant
          if(pieceSens > 2){  //Si la piece a dépassé le dernier sens possible
            pieceSens = 1;  //On met le sens par defaut
          }
          switch(pieceSens){  //Pour chaque position
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
          pieceSens++;  //Sens suivant
          if(pieceSens > 4){  //Si la piece a dépassé le dernier sens possible
            pieceSens = 1;  //On met le sens par defaut
          }
          switch(pieceSens){  //Pour chaque position
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
          pieceSens++;  //Sens suivant
          if(pieceSens > 4){  //Si la piece a dépassé le dernier sens possible
            pieceSens = 1;  //On met le sens par defaut
          }
          switch(pieceSens){  //Pour chaque position
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
          pieceSens++;  //Sens suivant
          if(pieceSens > 2){  //Si la piece a dépassé le dernier sens possible
            pieceSens = 1;  //On met le sens par defaut
          }
          switch(pieceSens){  //Pour chaque position
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
          pieceSens++;  //Sens suivant
          if(pieceSens > 4){  //Si la piece a dépassé le dernier sens possible
            pieceSens = 1;  //On met le sens par defaut
          }
          switch(pieceSens){  //Pour chaque position
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
          pieceSens++;  //Sens suivant
          if(pieceSens > 2){  //Si la piece a dépassé le dernier sens possible
            pieceSens = 1;  //On met le sens par defaut
          }
          switch(pieceSens){  //Pour chaque position
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
      /*VERIFICATION SUPERPOSITION*/
      for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
        for(int x=0;x<4;x++){ //Pour chaque valeur de la ligne
          if(futurePiece[x][y] == 1 && (plateau[piecePosX+x][piecePosY+y] != 0 || piecePosX+x<0 || piecePosX+x>largeur)){ //Si la case de la piece est pleine ET (que la case sort pas du terrain OU que la case superpose une case pleine du plateau)
            return 0; //Impossible de tourner la piece
          }
        }
      }
      //On applique la rotation
      for(int y=0;y<4;y++){ //Pour chaque ligne de la piece/future piece
        for(int x=0;x<4;x++){ //Pour chaque valeur de la ligne
          piece[x][y] = futurePiece[x][y];  //On place la case dans la piece
        }
      }
      return 1; //La rotation c'est bien effectuer
    }
    bool checkDescentePiece(){  //Si la piece peut descendre
      /*
      0 = La piece ne peu pas descendre
      1 = La piece peu descendre
      */
      for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
        for(int x=0;x<4;x++){ //Pour chaque valeur de la ligne
          //On regarde si la case de la piece est utilisé
          if(piece[x][y] == 1 && (plateau[piecePosX+x][piecePosY+y+1] != 0 || piecePosY+y == hauteur-1)){ //Si la case de la piece est pleine ET (la case de la piece superpose une case OU que la case touche le bas de l'ecran)
            return 0; //La piece ne peut plus descendre
          }
        }
      }
      return 1; //La piece peut descendre
    }
    bool fixPiece(){  //On fixe la piece au plateau
      /*
      0 = La piece n'a pas pus etre fixé
      1 = La piece a ete fixé
      */
      for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
        for(int x=0;x<4;x++){ //Pour chaque valeur de la ligne
          if(piece[x][y] == 1){ //Si la case de la piece est utilisé
            plateau[piecePosX+x][piecePosY+y] = pieceCouleur; //On definie la couleur de la case du plateau
          }
        }
      }
      return 1; //La piece a bien été fixé
    }
    bool dashPiece(){ //Dash la piece
      while(checkDescentePiece()){  //Tant que la piece peu descendre
        piecePosY++;  //On descent la piece de 1
      }
      fixPiece(); //On fixe la piece
      pieceGenerateur();  //On genere une nouvelle piece
    }

  private:
    /*VARIABLES*/
    bool piece[4][4] = {0};         //Une table de 4*4 remplis de 0

    int typePiece;  //Type de la piece qui tombe
    /*
      1 = I
      2 = J
      3 = L
      4 = O
      5 = S
      6 = T
      7 = Z
    */

    int pieceSens = 1; //Sens de la piece [1;4]

    /*FUNCTIONS*/
    bool checkSuperposition(int futurePosX, int futurePosY){  //Si la piece superpose une autre piece
      /*
      0 = ne superpose aucune case du plateau
      1 = superpose une case du plateau
      */

      //Pour chaque case de la piece
      for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
        for(int x=0;x<4;x++){ //Pour chaque valeur de la ligne
          //Si la case de la piece est utilisé
          if(piece[x][y] == 1 && plateau[x+futurePosX][y+futurePosY] != 0){  //Si la case de la piece est pleine ET la future position du plateau est utilisé
            return 1; //La piece superpose une case du plateau
          }
        }
      }
      return 0;//La piece ne superpose aucune case du plateau
    }

};

int main(){
  Tetris Game;  //Creation de l'instance

  Game.gameTimer.restart(); //On reinitialise le timer du jeux
  Game.pieceGenerateur(); //On genere la premiere piece

  while(Game.gameWindow.isOpen()){  //Tant que la fenetre est ouverte
    sf::Event e;  //Liste des evenement
    while(Game.gameWindow.pollEvent(e)){ //Tant qu'il y a un evenement
      if(e.type == sf::Event::Closed){  //Si la croix est cliquer
        Game.gameWindow.close();  //On ferme la fenetre de jeux
      }
      if(e.type == sf::Event::KeyPressed){  //Si une touche est presser
        if(e.key.code == sf::Keyboard::Up){ //Si la touche UP est pressé
          Game.rotation();  //On tourne la piece
        }
        if(e.key.code == sf::Keyboard::Left){ //Si la touche LEFT est pressé
          if(Game.checkLateralMovement(-1)){  //On regarde si on peu deplacer vers la gauche
            Game.piecePosX--; //On deplace la piece de 1 vers la gauche
          }
        }
        if(e.key.code == sf::Keyboard::Right){  //Si la touche RIGHT est pressé
          if(checkLateralMovement(1)){  //On regarde si on peu deplacer vers la droite
            piecePosX++; //On deplace la piece de 1 vers la droite
          }
        }
        if(e.key.code == sf::Keyboard::Down){ //Si la touche DOWN est pressé
          dashPiece();  //On dash la piece
        }
      }
    }

    if(Game.gameTimer.getElapsedTime().asSeconds() > delay){  //Si on doit mettre a jour le plateau
      Game.gameTimer.restart(); //On remet le timer a 0

      /*CHECK SI LIGNE COMPLETE*/
      for(int y=0;y<Game.hauteur;y++){ //Pour chaque ligne du plateau en partent du haut
        int nbCasePleine = 0; //Le nombre de case pleine de la ligne
        for(int x=0;x<Game.largeur;x++){ //Pour chaque valeur de la ligne
          if(Game.plateau[x][y] != 0){ //Si la case est pleine
            nbCasePleine++; //On ajoute 1 au nombre de case pleine de la ligne
          }
        }
        if(nbCasePleine == Game.largeur){  //Si la ligne est pleine
          for(int x=0;x<Game.largeur;x++){  //Pour chaque case de la ligne
            Game.plateau[x][y] = 0; //On efface la case
          }
          //On baisse toute les case au dessus
          for(int tempY=y-1;tempY>0;tempY--){ //Pour chaque ligne en partent de la ligne juste au dessus de la ligne actuel et on se deplace vers le haut
            for(int x=0;x<Game.largeur;x++){ //Pour chaque case de la ligne
              Game.plateau[x][tempY+1] = Game.plateau[x][tempY]; //On baisse la case du plateau de 1 case vers le bas
            }
          }
        }
      }
      /*#######################*/


      /*DESCENTE DE LA PIECE*/
      if(Game.checkDescentePiece()){ //Si la piece peu descendre
        piecePosY++;  //On descend la piece de 1
      }else{//Sinon la piece est déposé
        Game.fixPiece();  //On fixe la piece
        bool isCreated = Game.pieceGenerateur();  //On genere une nouvelle piece
        if(isCreated == false){ //Si la piece n'a pas pus etre generé
          Game.gameWindow.close();
        }
      }
      /*####################*/
    }

    /*AFFICHAGE*/
    //On efface l'ecran et on le remplis de blanc
    //gameWindow.clear(Color::White);
    Game.gameWindow.clear(sf::Color::Black);

    //Affichage du fond
    Game.gameWindow.draw(fondSprite);

    //Affichage du plateau
    for(int x=0;x<Game.largeur;x++){
      for(int y=0;y<Game.hauteur;y++){
        //On reinitialise le sprite
        Game.tileSprite.setTexture(Game.tileTexture);
        //On verifie si la case existe
        if(Game.plateau[x][y] != 0){
          //On definie la couleur
          int caseColor = (Game.plateau[x][y]);
          Game.tileSprite.setTextureRect(sf::IntRect((caseColor-1)*18,0,18,18)); //COULEUR
          //On definie sa position
          Game.tileSprite.setPosition(x*18,y*18);
          //On affiche la case
          Game.gameWindow.draw(Game.tileSprite);
        }
      }
    }

    //Affichage de la piece
    //on change la couleur du sprite en la couleur de la piece
    //on reinitialise le sprite
    Game.tileSprite.setTexture(Game.tileTexture);
    //On definie la couleur
    Game.tileSprite.setTextureRect(sf::IntRect((Game.pieceCouleur-1)*18,0,18,18)); //COULEUR
    for(int x=0;x<4;x++){
      for(int y=0;y<4;y++){
        //Si il y a une case pleine
        if(Game.piece[x][y] == 1){
          //On definie sa position
          Game.tileSprite.setPosition((x+Game.piecePosX)*18,(y+Game.piecePosY)*18);
          //On affiche la case
          Game.gameWindow.draw(Game.tileSprite);
        }
      }
    };

    //On affiche l'ecran
    Game.gameWindow.display();
    /*#####################*/
  }
  return 0;
}

