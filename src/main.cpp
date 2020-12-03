//Point
//MultiJoueur

#include <iostream> //CIN COUT ENDL

#include <cstdlib> //Pour random
#include <string> //Pour les string
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

class Board{  //Plateau de la partie (Gestion du plateau et de la piece)
  private:
    /*VARIABLES*/
    /*FUNCTIONS*/
    bool setPiece(){  //On definie les case de la piece selon sont type et sont sens
      /*
        Vrai = La piece a bien été généré
        False = La piece n'a pas été généré
      */
      //[y][x]
      bool prmFuturePiece[4][4] = {0}; //On génére une nouvelle piece temporaire
      switch(piece.type){  //Pour chaque type de piece
        case 1://I
          switch(piece.sens){ //Pour chaque sens de la piece
            case 1:
              prmFuturePiece[1][0] = 1;
              prmFuturePiece[1][1] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[1][3] = 1;
              break;
            case 2:
              prmFuturePiece[0][2] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[2][2] = 1;
              prmFuturePiece[3][2] = 1;
              break;
          }
          break;
        case 2://J
          switch(piece.sens){ //Pour chaque sens de la piece
            case 1:
              prmFuturePiece[1][1] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[1][3] = 1;
              prmFuturePiece[2][3] = 1;
              break;
            case 2:
              prmFuturePiece[0][2] = 1;
              prmFuturePiece[0][3] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[2][2] = 1;
              break;
            case 3:
              prmFuturePiece[0][1] = 1;
              prmFuturePiece[1][1] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[1][3] = 1;
              break;
            case 4:
              prmFuturePiece[0][2] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[2][2] = 1;
              prmFuturePiece[2][1] = 1;
              break;
          }
          break;
        case 3://L
          switch(piece.sens){ //Pour chaque sens de la piece
            case 1:
              prmFuturePiece[1][1] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[1][3] = 1;
              prmFuturePiece[2][1] = 1;
              break;
            case 2:
              prmFuturePiece[0][2] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[2][2] = 1;
              prmFuturePiece[2][3] = 1;
              break;
            case 3:
              prmFuturePiece[0][3] = 1;
              prmFuturePiece[1][1] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[1][3] = 1;
              break;
            case 4:
              prmFuturePiece[0][1] = 1;
              prmFuturePiece[0][2] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[2][2] = 1;
              break;
          }
          break;
        case 4://O  Ne tourne pas
          prmFuturePiece[1][1] = 1;
          prmFuturePiece[1][2] = 1;
          prmFuturePiece[2][1] = 1;
          prmFuturePiece[2][2] = 1;
          break;
        case 5://S
          switch(piece.sens){ //Pour chaque sens de la piece
            case 1:
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[1][3] = 1;
              prmFuturePiece[2][1] = 1;
              prmFuturePiece[2][2] = 1;
              break;
            case 2:
              prmFuturePiece[0][1] = 1;
              prmFuturePiece[1][1] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[2][2] = 1;
              break;
          }
          break;
        case 6://T
          switch(piece.sens){ //Pour chaque sens de la piece
            case 1:
              prmFuturePiece[1][1] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[1][3] = 1;
              prmFuturePiece[2][2] = 1;
              break;
            case 2:
              prmFuturePiece[0][2] = 1;
              prmFuturePiece[1][1] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[2][2] = 1;
              break;
            case 3:
              prmFuturePiece[0][2] = 1;
              prmFuturePiece[1][1] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[1][3] = 1;
              break;
            case 4:
              prmFuturePiece[0][2] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[1][3] = 1;
              prmFuturePiece[2][2] = 1;
              break;
          }
          break;
        case 7://Z
          switch(piece.sens){ //Pour chaque sens de la piece
            case 1:
              prmFuturePiece[1][1] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[2][2] = 1;
              prmFuturePiece[2][3] = 1;
              break;
            case 2:
              prmFuturePiece[0][3] = 1;
              prmFuturePiece[1][2] = 1;
              prmFuturePiece[1][3] = 1;
              prmFuturePiece[2][2] = 1;
              break;
          }
          break;
      }
      for(int y=0;y<4;y++){ //Pour chaque ligne de la futurePiece
        for(int x=0;x<4;x++){ //Pour chaque valeur de la ligne
          if((plateau[y][x] != 0 || x+piece.posX < 0 || x+piece.posX >= largeur || y+piece.posY < 0 || y+piece.posY >= hauteur) && prmFuturePiece[y][x] == 1){ //Si la case de la futurePiece est utilisé ET que sa future position est utilisé
            return 0; //La piece superposera une case du plateau
          }
        }
      }
      for(int y=0;y<4;y++){ //Pour chaque ligne de la futurePiece
        for(int x=0;x<4;x++){ //Pour chaque valeur de la ligne
            piece.cases[y][x] = prmFuturePiece[y][x]; //On applique le changement
        }
      }
      return 1; //Ne superpose aucune case du plateau
    }
    bool checkSuperposition(int prmFuturePosX, int prmFuturePosY){  //Si la piece superpose une case du plateau ou sort du plateau
      /*
        Vrai = La piece superpose
        False = La piece ne superpose pas
      */
      for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
        for(int x=0;x<4;x++){ //Pour chaque valeur de la ligne
          if(piece.cases[y][x] == 1 && (plateau[y+prmFuturePosY][x+prmFuturePosX] != 0 || x+prmFuturePosX < 0 || x+prmFuturePosX >= largeur || y+prmFuturePosY < 0 || y+prmFuturePosY >= hauteur)){ //Si la case de la piece est utilisé ET que sa future position est utilisé
            return 1; //La piece superposera une case du plateau ou sort du plateau
          }
        }
      }
      return 0; //Ne superpose aucune case du plateau
    }
  public:
    /*VARIABLES*/
    sf::Sprite fondSprite;  //Sprite du fond
    sf::Sprite tileSprite;  //Sprite de la case
    unsigned int hauteur = 20; //Hauteur du plateau
    unsigned int largeur = 10; //Largeur du plateau
    int plateau[20][10]; //Plateau  (0 = vide sinon couleur de la case)

    struct{
      bool cases[4][4]; //Toute les case de la piece
      int posX = 0; //Position de la piece par rapport au plateau
      int posY = 0; //Position de la piece par rapport au plateau
      int type; //Type de la piece
      int sens = 1; //Sens de 1 a 4 max
      int color;  //La couleur de la piece
    }piece;
    /*
    1 = I
    2 = J
    3 = L
    4 = O
    5 = S
    6 = T
    7 = Z
    */
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

    sf::Texture backgroundTexture;  //Texture du fond
    //case = 18x18
    sf::Texture tileTexture;  //Texture des case

    /*FUNCTIONS*/
    void resetPlateau(){ //Initialisation du plateau
      for(unsigned int y=0;y<hauteur;y++){ //Pour chaque ligne du plateau
        for(unsigned int x=0;x<largeur;x++){ //Pour chaque valeur de la ligne
          plateau[y][x] = 0;  //On vide la case
        }
      }
    }
    void resetPiece(){  //Initialisation de la piece
      piece.posX = 0;  //On remet la position à 0
      piece.posY = 0;  //On remet la position à 0
      for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
        for(int x=0;x<4;x++){ //Pour chaque valeur de la ligne
          piece.cases[y][x] = 0;  //On vide la case
        }
      }
    }
    void loadTexture(){ //On charge les textures
      backgroundTexture.loadFromFile("img/Board.png");  //On charge la texture du fond
      tileTexture.loadFromFile("img/tiles.png");  //On charge la texture de toute les cases
    }
    void loadSprite(){  //On charge les sprites
      fondSprite.setTexture(backgroundTexture); //On definie la texture du fond
      tileSprite.setTexture(tileTexture); //On definie la texture des cases
    }
    bool checkDescentePiece(){  //Si la piece peut descendre
      /*
      0 = ne peut pas descendre
      1 = peut descendre
      */
      return !checkSuperposition(piece.posX,piece.posY+1);  //Si la piece qui descent superposera une case
    }
    bool pieceGenerator(){  //Generation de la piece
      /*
        Vrai = la piece a été posé
        False = la piece n'a pas été posé
      */
      resetPiece(); //On remet la piece à 0
      piece.sens = 1; //On remet le sens de la piece par defaut
      piece.color = random(1,8);  //On prend une couleur aleatoire
      piece.type = random(1,7); //On prend un type de piece aleatoire
      piece.posX = largeur/2; //On centre la piece par rapport au plateau
      piece.posY = 0; //On met la piece tout en haut du plateau
      setPiece(); //On definie les cases de la piece
      return !checkSuperposition(piece.posX,piece.posY);  //On retourne si la piece peut etre posé ou non
    }
    void fixPiece(){  //On fixe la piece au plateau
      for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
        for(int x=0;x<4;x++){ //Pour chaque valeur de la ligne
          if(piece.cases[y][x] == 1){ //Si la case est utilisé
            plateau[piece.posY+y][piece.posX+x] = piece.color; //On definie la case du plateau à la couleur de la case de la piece
          }
        }
      }
    }
    bool rotation(){
      /*
      0 = a pus etre posé
      1 = n'a pas pus etre posé
      */
      int oldSens = piece.sens; //L'ancien sens de la piece si elle ne peu pas etre posé
      switch(piece.type){  //Pour chaque type de piece
        case 1://I
          piece.sens++;  //Position suivante
          if(piece.sens > 2){  //Si tour complet
            piece.sens = 1; //Sens par defaut
          }
          break;
        case 2://J
          piece.sens++;  //Position suivante
          if(piece.sens > 4){  //Si tour complet
            piece.sens = 1; //Sens par defaut
          }
          break;
        case 3://L
          piece.sens++;  //Position suivante
          if(piece.sens > 4){  //Si tour complet
            piece.sens = 1; //Sens par defaut
          }
          break;
        //O  Ne tourne pas
        case 5://S
          piece.sens++;  //Position suivante
          if(piece.sens > 2){  //Si tour complet
            piece.sens = 1; //Sens par defaut
          }
          break;
        case 6://T
          piece.sens++;  //Position suivante
          if(piece.sens > 4){  //Si tour complet
            piece.sens = 1; //Sens par defaut
          }
          break;
        case 7://Z
          piece.sens++;  //Position suivante
          if(piece.sens > 2){  //Si tour complet
            piece.sens = 1; //Sens par defaut
          }
          break;
      }
      if(!setPiece()){  //Si la piece superpose une case du plateau
        piece.sens = oldSens; //On remet l'ancien sens de la piece
        return 0; //N'a pas été posé
      }
      return 1; //A été posé
    }
    bool lateralMovement(int sens){ //Mouvement lateral de la piece
      /*
      0 = La piece n'a pas été placé
      1 = La piece a été placé
      */
      if(!checkSuperposition(piece.posX + sens, piece.posY)){ //Si on peut déplacé la piece dans la direction demandé
        piece.posX = piece.posX + sens; //On applique le mouvement lateral
        return 1; //La piece a été placé
      }
      return 0; //La piece n'a pas été placé
    }
    void dash(){  //On dash la piece
      //tant que la piece peu descendre
      while(checkDescentePiece()){ //Tant que la piece peut descendre
        piece.posY++; //On descent la piece de 1
      }
      fixPiece(); //On fixe la piece
      pieceGenerator(); //On genere une nouvelle piece
    }
};

class Party{  //Partie en cour (affichage du score actuel, et timer)
  private:
    /*VARIABLES*/
    Board Plateau;  //On créé l'instance du plateau
    sf::Clock gameTimer;  //Temp entre chaque update du jeux
    float delay = 0.5;  //Temp à attendre avant de faire une update

    /*FUNCTIONS*/

  public:
    /*VARIABLES*/
    /*FUNCTIONS*/
    void load(){  //On charge tout ce qu'il faut pour la partie
      Plateau.resetPlateau();  //On charge le plateau
      Plateau.resetPiece(); //On charge la piece
      Plateau.loadTexture();  //On charge les textures
      Plateau.loadSprite(); //On charge les sprites
    }
    int start(){ //On lance la partie
      gameTimer.restart();  //On remet le timer à 0
      Plateau.pieceGenerator(); //On genere la premiere piece
      return 0; //La partie a bien commencé
    }
    void event(sf::Event e){  //On execute l'evenement
      if(e.type == sf::Event::KeyPressed){  //Si l'evenement est une touche du clavier
        if(e.key.code == sf::Keyboard::Up){  //Si la touche HAUT est pressé
          Plateau.rotation(); //On effectue la rotation
        }
        if(e.key.code == sf::Keyboard::Left){  //Si la touche GAUCHE est pressé
          Plateau.lateralMovement(-1);  //On deplace la piece vers la gauche
        }
        if(e.key.code == sf::Keyboard::Right){  //Si la touche DROITE est pressé
          Plateau.lateralMovement(1);  //On deplace la piece vers la droite
        }
        if(e.key.code == sf::Keyboard::Down){  //Si la touche BAS est pressé
          Plateau.dash(); //On dash la piece
        }
      }
    }
    int update(sf::RenderWindow *gameWindow){ //On avance la partie
      /*
      -1 = Perdu
      0 = La partie continue
      1 = Gagné
      */

      if(gameTimer.getElapsedTime().asSeconds() > delay){ //Si on doit mettre à jour le plateau
        gameTimer.restart();  //On remet le timer a 0

        /*CHECK SI LIGNE COMPLETE*/
        for(int y=0;y<Plateau.hauteur;y++){ //Pour chaque ligne du plateau en partant du haut
          int nbCasePleine = 0; //Nombre de case utilisé par ligne
          for(int x=0;x<Plateau.largeur;x++){ //Pour chaque case de la ligne
            if(Plateau.plateau[y][x] != 0){ //Si la case du plateau est utilisé
              nbCasePleine++; //On ajoute 1 au nombre de case utilisé dans la ligne
            }
          }
          if(nbCasePleine == Plateau.largeur){  //Si la ligne est entière
            for(int x=0;x<Plateau.largeur;x++){ //Pour chaque case de la ligne
              Plateau.plateau[y][x] = 0;  //On efface la case
            }
            for(int tempY=y-1;tempY>0;tempY--){ //Pour chaque ligne en partant de la ligne juste au dessus
              for(int x=0;x<Plateau.largeur;x++){ //Pour chaque case de la ligne
                Plateau.plateau[tempY+1][x] = Plateau.plateau[tempY][x];  //On deplace la valeur a la case juste en dessous
              }
            }
          }
        }
        /*#######################*/

        /*DESCENTE DE LA PIECE*/
        if(Plateau.checkDescentePiece()){ //Si la piece peut descendre
          Plateau.piece.posY++;  //On descent la piece
        }else{  //Sinon la piece est déposé
          Plateau.fixPiece(); //On fixe la piece
          bool isCreated = Plateau.pieceGenerator(); //On genere une nouvelle piece
          if(isCreated == false){ //Si la piece ne peut pas etre placé
            return -1;  //Partie finie : Perdu
          }
        }
        /*####################*/

      }

      gameWindow->clear(sf::Color::Black); //On efface l'ecran et on le met en noir
      int prmDispX = 5; //Position initial du plateau
      int prmDispY = 5; //Position initial du plateau

      //Affichage du plateau
      Plateau.fondSprite.setPosition(prmDispX,prmDispY);  //On place le plateau a la position demandé
      gameWindow->draw(Plateau.fondSprite); //On affiche le plateau
      for(int y=0;y<Plateau.hauteur;y++){ //Pour chaque ligne du plateau
        for(int x=0;x<Plateau.largeur;x++){ //Pour chaque case de la ligne
          Plateau.tileSprite.setTexture(Plateau.tileTexture); //On reinitialise le sprite
          if(Plateau.plateau[y][x] != 0){ //Si la case du plateau est utilisé
            int caseColor = (Plateau.plateau[y][x]);  //On prend la couleur de la case
            //Case 18x18
            Plateau.tileSprite.setTextureRect(sf::IntRect((caseColor-1)*18,0,18,18)); //COULEUR
            Plateau.tileSprite.setPosition(prmDispX+(x*18),prmDispY+(y*18));  //Position de la case
            gameWindow->draw(Plateau.tileSprite); //On affiche la case
          }
        }
      }

      //Affichage de la piece
      Plateau.tileSprite.setTexture(Plateau.tileTexture); //On reinitialise la couleur des cases
      Plateau.tileSprite.setTextureRect(sf::IntRect((Plateau.piece.color-1)*18,0,18,18)); //COULEUR
      for(int y=0;y<4;y++){ //Pour chaque ligne de la piece
        for(int x=0;x<4;x++){ //Pour chaque case de la ligne
          if(Plateau.piece.cases[y][x] == 1){ //Si la case est utilisé
            Plateau.tileSprite.setPosition(prmDispX+(x+Plateau.piece.posX)*18,prmDispY+(y+Plateau.piece.posY)*18);  //On definie la position a celle de la case
            gameWindow->draw(Plateau.tileSprite); //On affiche la case
          }
        }
      }
      return 0; //Le jeux continue
    }

};

class Tetris{ //Menu est gestion
  private:
    /*VARIABLES*/
    Party Partie;  //On créé l'instance de la partie
    /*FUNCTIONS*/

  public:
    /*VARIABLES*/
    sf::RenderWindow gameWindow;  //Ecran de jeux

    /*FUNCTIONS*/
    void setScreen(std::string prmTitle, const int prmHauteur, const int prmLargeur){ //Mise en place de l'ecran de jeux
      gameWindow.create(sf::VideoMode(prmHauteur,prmLargeur), prmTitle);  //On créé l'ecran de jeux
    }
    void start(){ //On demarre le jeux
      //MENU
      //...
      //...
      //...
      Partie.load();  //On charge tout ce qu'il faut pour la partie
      int result = Partie.start(); //On commence la partie
      while(result == 0){ //Tant que la partie se joue
        sf::Event e;  //On récupère l'evenement
        while(gameWindow.pollEvent(e)){ //Pour chaque evenement
          if(e.type == sf::Event::Closed){  //Si on ferme la fenetre
            gameWindow.close(); //On ferme la fenetre de jeux
            result = -1;  //Perdu
          }
          Partie.event(e); //On effectue les evenements
        }
        result = Partie.update(&gameWindow);  //On met a jour la partie

        gameWindow.display(); //On affiche l'ecran
      }
      //result;
    }
};

int main(){
  Tetris Game;  //On créé l'instance du jeux
  Game.setScreen("Tetris", 320, 480); //On créé l'ecran de jeux

  Game.start(); //On demarre le jeux

  return 0;
}
