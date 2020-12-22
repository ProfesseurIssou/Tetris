#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <SFML/Graphics.hpp>

class TetrisGame{
  public:
    TetrisGame(sf::RenderWindow *window);
    bool PlaySolo();  //La partie en solo (retourne si la fenetre a ete fermer

  private:
    //CONST
    const unsigned int boardPositionX = 440;    //Position du plateau sur l'ecran (pour les piece)
    const unsigned int boardPositionY = 70;     //Position du plateau sur l'ecran (pour les piece)
    const float caseScaleX = 2.2;           //Echelle de la piece
    const float caseScaleY = 2.2;           //Echelle de la piece

    //STRUCT
    struct boardStruct{
      unsigned int board[21][10];   //Plateau de données(0 = vide sinon couleur de la case)
      unsigned int hauteur = 21;    //Hauteur du plateau
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

    //VARIABLES
    unsigned int totalClearedLine = 0;  //Nombre de ligne efface au total
    unsigned int level = 0;             //Level actuel
    unsigned int score  = 0;            //Score de la partie
    struct boardStruct plateau;   //On créé le plateau
    struct pieceStruct piece;     //On créé la piece


    //SFML VARIABLES
    sf::RenderWindow *gameWindow;        //Ecran de jeux(pointeur)
    sf::Texture backgroundTexture;      //Texture du fond de la partie
    sf::Texture tileTexture;            //Texture des case (18x18)
    sf::Sprite backgroundSprite;        //Sprite du fond
    sf::Sprite tileSprite;              //Sprite de la case
    sf::Font font;                      //Police de texte

    //FUNCTIONS
    int Random(int min, int max);                     //Nombre aleatoire
    void ResetPlateau();   //Efface toute les case du plateau
    void ResetPiece();       //Remet la piece dans sont etat initial (position et contenue)
    void SetPiece();         //Mise en place du patern de la piece
    bool CheckSuperposition(int prmFuturePosX, int prmFuturePosY);//Si la piece a la position demande superposera une case du plateau
    bool PieceGenerator();//Generation de la piece
    bool Rotation();//Rotation de la piece
    bool LateralMovement(int direction); //Mouvement lateral de la piece
    bool CheckDescentePiece();  //Si la piece peut descendre
    void FixPiece();  //On fixe la piece au plateau
    void UpdateDisplay(); //Mise a jour de l'affichage du terrain
    void Dash();  //On dash la piece
};

#endif // TETRISGAME_H
