#include <stdio.h>

/*Déclaration des variables*/
int sudoku[9][9][10] = {0};     //le sudoku à résoudre avec les hypothèses dans la profondeur



void initSudoku(int sudokuhyp[9][9][10]){           //Initialisation du sudoku à 0 et des hypothèses à leur index

    for (int k=0 ; k<10 ; k++){
        for (int j=0 ; j<9 ; j++){
            for (int i=0 ; i<9 ; i++) {
                sudokuhyp[i][j][k] = k;
            }
        }
    }
}

int userSudoku(int sudokuhyp[9][9][10]) {           //Saisie des valeurs par l'utilisateur
    int x;
    int y;
    int val;
    int nbCases;
    int nbBon = 0;

    /*Remplissage des cases du sudoku selon l'utilisateur*/

    printf("Combien de cases voulez-vous remplir ?\n");
    scanf("%i", &nbCases);
    for (int i = 0; i < nbCases; ) {
        printf("Saisir les coordonnées x et y puis la valeur de la case à remplir, séparés par un espace à chaque fois. (1=<x,y et valeur=<9)\n");
        scanf("%i", &x);
        scanf("%i", &y);
        scanf("%i", &val);

        /* Tests des valeurs */


        if (x < 1 || x > 9) {
            printf("La valeur de x saisie est invalide, veuillez recommencer.\n");
        } else if (y < 1 || y > 9) {
            printf("La valeur de y saisie est invalide, veuillez recommencer.\n");
        } else if (val < 1 || val > 9) {
            printf("La valeur saisie est invalide, veuillez recommencer.\n");
        }

            /* si toutes les valeurs sont correctes*/

        else {
            sudokuhyp[x-1][y-1][0] = val;
            nbBon = nbBon + 1;
            i++;                                                   //On incrémente i ici pour éviter de devoir décaler le tableau
        }
    }
    return nbBon;
}

void afficherSudoku(int sudokuhyp[9][9][10]){                  /*Afficher le sudoku*/

    for (int j=0 ; j<9 ; j++) {
        printf("\n");
        for (int i=0 ; i<9 ; i++) {
            printf("%i", sudokuhyp[i][j][0]);
            printf(" ");
        }
    }
    printf("\n____________\n");

}

void afficherHyp(int sudokuhyp[9][9][10]){                      /* Afficher les hypothèses*/

    for (int k=1 ; k<10 ; k++) {
        for (int j=0 ; j<9 ; j++) {
            printf("\n");
            for (int i=0 ; i<9 ; i++) {
                printf("%i", sudokuhyp[i][j][k]);
                printf(" ");
            }
        }
        printf("\n____________\n");
    }

}

void supprHypColLine(int sudokuhyp[9][9][10]){                  //Supprimer les hypothèses des colonnes et des lignes

    for (int j = 0; j < 9; j++){
        for (int i = 0; i < 9; i++) {
            if (sudokuhyp[i][j][0] != 0){
                for (int j2 = 0; j2 < 9; j2++){
                    sudokuhyp[i][j2][sudokuhyp[i][j][0]] = 0;   //Colonnes
                }
                for (int i2=0 ; i2<9 ; i2++) {
                    sudokuhyp[i2][j][sudokuhyp[i][j][0]] = 0;   //Lignes
                }
            }
        }
    }
}

void carreChercheHyp(int jMin, int jMax, int iMin, int iMax, int hyp, int sudokuhyp[9][9][10]) {

    for (int j2 = jMin; j2 < jMax; j2++){
        for (int i2 = iMin; i2 < iMax; i2++){
            sudokuhyp[i2][j2][hyp] = 0;
        }
    }
}

void supprHypCarre(int sudokuhyp[9][9][10]){                    //Supprimer les hypothèses des "carrés"

    for (int j = 0; j < 9 ; j++) {
        for (int i = 0; i < 9; i++) {
            if (sudokuhyp[i][j][0] != 0){
                if (j < 3){                                 //Correspond à la première ligne de carrés
                    if (i < 3){                             //1er carré
                        carreChercheHyp(0, 3, 0, 3, sudokuhyp[i][j][0], sudoku);
                    }
                    if (i > 2 && i < 6){                    //2eme carré
                        carreChercheHyp(0, 3, 3, 6, sudokuhyp[i][j][0], sudoku);
                    }
                    if (i > 5 && i < 9){                    //3ème carré
                        carreChercheHyp(0, 3, 6, 9, sudokuhyp[i][j][0], sudoku);
                    }
                }
                if (j < 6 && j > 2){                         //Correspond à la deuxième ligne de carrés
                    if (i < 3){                                //1er carré
                        carreChercheHyp(3, 6, 0, 3, sudokuhyp[i][j][0], sudoku);
                    }
                    if (i > 2 && i < 6){                    //2ème carré
                        carreChercheHyp(3, 6, 3, 6, sudokuhyp[i][j][0], sudoku);
                    }
                    if (i > 5 && i < 9){                    //3ème carré
                        carreChercheHyp(3, 6, 6, 9, sudokuhyp[i][j][0], sudoku);
                    }
                }
                if (j < 9 && j > 5){                         //Correspond à la troisème ligne de carrés
                    if (i < 3){                             //1er carré
                        carreChercheHyp(6, 9, 0, 3, sudokuhyp[i][j][0], sudoku);
                    }
                    if (i > 2 && i < 6){                    //2ème carré
                        carreChercheHyp(6, 9, 3, 6, sudokuhyp[i][j][0], sudoku);
                    }
                    if (i > 5 && i < 9){                    //3ème carré
                        carreChercheHyp(6, 9, 6, 9, sudokuhyp[i][j][0], sudoku);
                    }
                }
            }
        }
    }
}

void supprHypProf(int sudokuhyp[9][9][10]){                 //Suppression des hypothèses de la case

    for (int k=1 ; k<10 ; k++){
        for (int j=0 ; j<9 ; j++){
            for (int i=0 ; i<9 ; i++){
                if (sudokuhyp[i][j][0] != 0)
                    sudokuhyp[i][j][k] = 0;
            }
        }
    }
}

void supprHyp(int sudokuhyp[9][9][10]){

    supprHypColLine(sudokuhyp);
    supprHypCarre(sudokuhyp);
    supprHypProf(sudokuhyp);
}

int completerSudokuInclusion(int sudokuhyp[9][9][10]){         //Methode de l'inclusion
    int nbHyp;
    int posHyp;
    int nbBon = 0;

    for (int j = 0; j < 9; j++){
        for (int i = 0; i < 9; i++) {
            if (sudokuhyp[i][j][0] == 0) {                  //Si la case du sudoku est vide...
                nbHyp = 0;
                posHyp = 0;
                for (int k = 1; k < 10; k++) {
                    if (sudokuhyp[i][j][k] != 0){           //On stocke les positions des hypothèses non nulles
                        nbHyp = nbHyp + 1;
                        posHyp = k;                         //Pas besoin de stocker toutes les positions puisqu'on cherche si il n'y en a qu'une
                    }
                }
                if (nbHyp == 1) {                           //Si il n'y en a qu'une, c'est la solution de cette case
                    sudokuhyp[i][j][0] = posHyp;
                    nbBon = nbBon + 1;
                }
            }
        }
    }
    return nbBon;
}

int completerSudokuExclusionLigne(int sudokuhyp[9][9][10]){         //Sous-fonction de completerSudokuExclusion() -> Verif de la ligne
    int compteur;
    int nbBon = 0;

    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            if (sudokuhyp[i][j][0] == 0){                           //On regarde dans le sudoku quelles cases sont vides
                for (int k = 1; k < 10; k++) {                      //On regarde ses hypothèses
                    compteur = 0;
                    if (sudokuhyp[i][j][k] != 0){                   //Si on trouve une hypothèses non nulle...
                        for (int i2 = 0; i2 < 9; i2++) {
                            if (sudokuhyp[i2][j][k] != 0){          //On regarde combien de fois elle est présente sur la ligne
                                compteur = compteur + 1;
                            }
                        }
                        if (compteur == 1){                         //Si elle est présente une seule fois (dans la case recherchée), c'est le bon numéro
                            sudokuhyp[i][j][0] = k;
                            nbBon = nbBon + 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    return nbBon;
}

int completerSudokuExclusionColonne(int sudokuhyp[9][9][10]){      //Idem que completerSudokuExclusionLigne(), mais pour les colonnes
    int compteur;
    int nbBon = 0;

    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            if (sudokuhyp[i][j][0] == 0){
                for (int k = 1; k < 10; k++) {
                    compteur = 0;
                    if (sudokuhyp[i][j][k] != 0){
                        for (int j2 = 0; j2 < 9; j2++) {
                            if (sudokuhyp[i][j2][k] !=0){
                                compteur = compteur + 1;
                            }
                        }
                        if (compteur == 1){
                            sudokuhyp[i][j][0] = k;
                            nbBon = nbBon + 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    return nbBon;
}

int exclusionCarre(int jMin, int jMax, int iMin, int iMax, int prof, int sudokuhyp[9][9][10]) { //Sous-fonction de completerSudokuExclusionCarre() pour compacter le code dans les conditions.
    int compteur = 0;

    for (int j2 = jMin; j2 < jMax; j2++){
        for (int i2 = iMin; i2 < iMax; i2++){
            if (sudokuhyp[i2][j2][prof] !=0){
                compteur = compteur + 1;
            }
        }
    }
    return compteur;
}

int completerSudokuExclusionCarre(int sudokuhyp[9][9][10]){
    int compteur;
    int nbBon = 0;


    for (int j = 0; j < 9 ; j++) {
        for (int i = 0; i < 9; i++) {
            if (sudokuhyp[i][j][0] == 0){
                compteur = 0;
                for (int k = 1; k < 10; k++) {
                    if (sudokuhyp[i][j][k] != 0){
                        if (j < 3){                                 //Correspond à la première ligne de carrés
                            if (i < 3){                             //1er carré
                                compteur = exclusionCarre(0, 3, 0, 3, k, sudoku);
                            }
                            if (i > 2 && i < 6){                    //2eme carré
                                compteur = exclusionCarre(0, 3, 3, 6, k, sudoku);
                            }
                            if (i > 5 && i < 9){                    //3ème carré
                                compteur = exclusionCarre(0, 3, 6, 9, k, sudoku);
                            }
                        }
                        if (j < 6 && j > 2){                         //Correspond à la deuxième ligne de carrés
                            if (i < 3){                                //1er carré
                                compteur = exclusionCarre(3, 6, 0, 3, k, sudoku);
                            }
                            if (i > 2 && i < 6){                    //2ème carré
                                compteur = exclusionCarre(3, 6, 3, 6, k, sudoku);
                            }
                            if (i > 5 && i < 9){                    //3ème carré
                                compteur = exclusionCarre(3, 6, 6, 9, k, sudoku);
                            }
                        }
                        if (j < 9 && j > 5){                         //Correspond à la troisème ligne de carrés
                            if (i < 3){                             //1er carré
                                compteur = exclusionCarre(6, 9, 0, 3, k, sudoku);
                            }
                            if (i > 2 && i < 6){                    //2ème carré
                                compteur = exclusionCarre(6, 9, 3, 6, k, sudoku);
                            }
                            if (i > 5 && i < 9){                    //3ème carré
                                compteur = exclusionCarre(6, 9, 6, 9, k, sudoku);
                            }
                        }
                    }
                    if (compteur == 1){
                        sudokuhyp[i][j][0] = k;
                        nbBon = nbBon + 1;
                        break;
                    }
                }
            }
        }
    }
    return nbBon;
}

int completerSudokuExclusion(int sudokuhyp[9][9][10]){
    int nbBon = 0;

    nbBon += completerSudokuExclusionLigne(sudokuhyp);
    nbBon += completerSudokuExclusionColonne(sudokuhyp);
    nbBon += completerSudokuExclusionCarre(sudokuhyp);
    return nbBon;
}

int verifSudokuComplet(int sudokuhyp[9][9][10]){    //Verification si le sudoku est terminé ou pas
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            if (sudokuhyp[i][j][0] == 0) {          // Si au moins une case est à 0, le sudoku n'est pas complet
                return 0;
            }
        }
    }
    return 1;                                       // Aucune case à 0, sudoku complet
}

int setupEasyGrid1();
int setupEasyGrid2();
int setupEasyGrid3();

int main() {
    int etape = 0;
    int nbCorrect = 0;
    int choix = 0;

    /*Initialistaion du Sudoku et remplissage des valeurs par l'utilisateur*/

    initSudoku(sudoku);                         //Initialisation du sudoku
    printf("Voulez-vous rentrer vos valeurs ou utiliser un exemple ?\n  1- Rentrer ses valeurs\n  2- Utiliser un exemple\n");
    scanf("%i", &choix);
    while (choix != 1 && choix != 2){
        printf("Rentrez 1 pour rentrer vos valeurs, ou 2 pour utiliser un des exemples.\n");
        scanf("%i", &choix);
    }

    switch (choix) {
        case 1:
            nbCorrect += userSudoku(sudoku);          //Rentrée des valeurs du sudoku par le user
            break;

        case 2:
            choix = 0;
            printf("Quel exemple voulez-vous exécuter ?\n   1- Méthode de l'inclusion\n   2- Méthode de l'inclusion et de l'exclusion\n   3- Méthode de l'inclusion et de l'exclusion\n");
            scanf("%i", &choix);

            switch (choix) {
                case 1:
                    nbCorrect += setupEasyGrid1(sudoku);        //Grille prédéfinie
                    break;

                case 2:
                    nbCorrect += setupEasyGrid2(sudoku);        //Grille prédéfinie
                    break;

                case 3:
                    nbCorrect += setupEasyGrid3(sudoku);        //Grille prédéfinie
                    break;
            }

    }

    printf("Votre sudoku avant résolution :\n");
    afficherSudoku(sudoku);


    supprHypProf(sudoku);

    while (verifSudokuComplet(sudoku) != 1 && etape < 81) {
        etape = etape + 1;

        /*Suppression des hypothèses et résolution du Sudoku*/

        supprHyp(sudoku);

        nbCorrect += completerSudokuInclusion(sudoku);

        nbCorrect += completerSudokuExclusion(sudoku);

        verifSudokuComplet(sudoku);
    }
    /*Suppression des dernières hypothèses*/

    supprHyp(sudoku);

    printf("\nRESOLUTION\n____________");

    if (etape >= 81){
        afficherSudoku(sudoku);
        printf("\nHYPOTHESES RESTANTES\n____________");
        afficherHyp(sudoku);
        printf("Le sudoku est impossible ou est trop compliqué pour ce programme.\n");
        printf("Le nombre de cases remplies est %i\n", nbCorrect);
        printf("Le sudoku a été résolu jusqu'à ce niveau en %i étapes\n", etape);
    }
    else {
        /* Affichage du sudoku */

        afficherSudoku(sudoku);
        printf("Le nombre de cases remplies est %i\n", nbCorrect);
        printf("Le sudoku a été résolu en %i étapes\n", etape);
    }

    fflush(stdin);
    printf("Appuyez sur <Entrée> pour quitter le programme");
    getchar();
    getchar();

    return 0;
}

int setupEasyGrid1(int sudokuhyp[9][9][10]) {       //Résolu seulement avec la méthode de l'inclusion
    sudokuhyp[0][4][0] = 7;
    sudokuhyp[0][8][0] = 4;

    sudokuhyp[1][1][0] = 7;
    sudokuhyp[1][3][0] = 9;
    sudokuhyp[1][5][0] = 1;
    sudokuhyp[1][6][0] = 3;

    sudokuhyp[2][0][0] = 1;
    sudokuhyp[2][1][0] = 4;
    sudokuhyp[2][4][0] = 3;
    sudokuhyp[2][7][0] = 9;
    sudokuhyp[2][8][0] = 7;

    sudokuhyp[3][4][0] = 9;

    sudokuhyp[4][0][0] = 8;
    sudokuhyp[4][2][0] = 4;
    sudokuhyp[4][6][0] = 2;

    sudokuhyp[5][0][0] = 5;
    sudokuhyp[5][1][0] = 3;
    sudokuhyp[5][3][0] = 1;
    sudokuhyp[5][5][0] = 2;

    sudokuhyp[6][1][0] = 8;
    sudokuhyp[6][4][0] = 5;
    sudokuhyp[6][7][0] = 3;

    sudokuhyp[7][2][0] = 7;
    sudokuhyp[7][3][0] = 2;

    sudokuhyp[8][0][0] = 4;
    sudokuhyp[8][4][0] = 7;
    sudokuhyp[8][6][0] = 5;
    sudokuhyp[8][7][0] = 2;

    int nbBon = 26;
    return nbBon;
}

int setupEasyGrid2(int sudokuhyp[9][9][10]) {          //Résolu avec l'inclusion et l'exclusion
    sudokuhyp[0][2][0] = 1;
    sudokuhyp[0][6][0] = 5;
    sudokuhyp[0][8][0] = 9;

    sudokuhyp[1][0][0] = 2;
    sudokuhyp[1][4][0] = 3;

    sudokuhyp[2][1][0] = 7;
    sudokuhyp[2][3][0] = 5;
    sudokuhyp[2][7][0] = 3;

    sudokuhyp[3][4][0] = 8;
    sudokuhyp[3][5][0] = 4;
    sudokuhyp[3][8][0] = 5;

    sudokuhyp[4][4][0] = 1;
    sudokuhyp[4][6][0] = 6;
    sudokuhyp[4][7][0] = 4;
    sudokuhyp[4][8][0] = 7;

    sudokuhyp[5][0][0] = 7;
    sudokuhyp[5][2][0] = 2;
    sudokuhyp[5][4][0] = 6;
    sudokuhyp[5][6][0] = 1;


    sudokuhyp[6][0][0] = 5;
    sudokuhyp[6][1][0] = 3;
    sudokuhyp[6][3][0] = 4;
    sudokuhyp[6][6][0] = 8;
    sudokuhyp[6][7][0] = 6;

    sudokuhyp[7][2][0] = 6;
    sudokuhyp[7][5][0] = 8;
    sudokuhyp[7][8][0] = 4;

    sudokuhyp[8][0][0] = 8;

    int nbBon = 27;
    return nbBon;
}

int setupEasyGrid3(int sudokuhyp[9][9][10]) {           //Résolu avec l'inclusion et l'exclusion
    sudokuhyp[0][2][0] = 9;
    sudokuhyp[0][3][0] = 6;
    sudokuhyp[0][4][0] = 1;

    sudokuhyp[1][1][0] = 3;
    sudokuhyp[1][2][0] = 6;
    sudokuhyp[1][3][0] = 9;
    sudokuhyp[1][6][0] = 2;
    sudokuhyp[1][7][0] = 5;

    sudokuhyp[2][5][0] = 8;
    sudokuhyp[2][7][0] = 4;

    sudokuhyp[3][2][0] = 7;
    sudokuhyp[3][3][0] = 5;
    sudokuhyp[3][7][0] = 1;

    sudokuhyp[4][0][0] = 6;
    sudokuhyp[4][3][0] = 4;

    sudokuhyp[5][4][0] = 9;

    sudokuhyp[6][3][0] = 1;
    sudokuhyp[6][5][0] = 4;
    sudokuhyp[6][7][0] = 9;

    sudokuhyp[7][1][0] = 2;
    sudokuhyp[7][4][0] = 6;
    sudokuhyp[7][6][0] = 3;

    sudokuhyp[8][0][0] = 5;
    sudokuhyp[8][1][0] = 6;
    sudokuhyp[8][8][0] = 8;
    int nbBon = 25;
    return nbBon;
}