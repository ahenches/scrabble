#include<stdio.h>
#include "../lib/libgraphique.h"
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define N_JOUEURS 2
#define FILEDICO "../dictionnaire_fr_ss_accents" // chemin du fichier dico
#define SIZEDICO 319000                     // taille large du dico
#define MAXMOTSCREES 8                          // nb maximum de mots crées 
#define MAXLENMOT 16 		                  // taille du mot max + \0
#define TAILLE_DICO 318897
#define DEBUT_PLATEAU_X 375
#define DEBUT_PLATEAU_Y 25
#define DEBUT_BOARD_X 575
#define DEBUT_BOARD_Y 800
#define TAILLE_JETON 49
#define TAILLE_CASE 50
#define PLATEAU_TAILLE 750
#define RESX 1500
#define RESY 900
#define COTE_CASES 15
#define MAX_MOTS_CREE_1_TOUR 8
#define RETOUR_VALIDATE_X_DEBUT 1200
#define RETOUR_VALIDATE_deltX 235
#define RETOUR_VALIDATE_deltY 115
#define VALIDATE_Y_DEBUT 650
#define RETOUR_Y_DEBUT 450
#define SCORE_NOM_Y 100
#define SCORE_X 1225
#define NOM_X 75
#define JOUEUR_NMAX_LETTER 7
#define N_LETTRE_DOUBLE 24
#define N_LETTRE_TRIPLE 12 
#define N_MOTS_DOUBLE 17
#define N_MOTS_TRIPLE 8


enum{REPIOCHE, PLACE_UN_MOT};
enum{DIRECTION_X=-1, UNE_LETTRE, DIRECTION_Y};

typedef struct {
    char name[30];
    char board[JOUEUR_NMAX_LETTER];
    int points;
    int lettres_restantes;
    int action_choisie;
} Joueur;

void affichage();
void afficher_board(char board[JOUEUR_NMAX_LETTER]);
Joueur joueur_joue(Joueur);
void RetourArriere(Joueur j);
char point_in_board(Point p, Point tab[JOUEUR_NMAX_LETTER]);
char point_in_plateau(Point p, Point tab[175]);
char is_in_tab(int x, int y, Point *tab, int taille_tab);
char is_in_tabint(int x, int *tab);
void tab_to_zero(int *tab, int taille_tab);
int chargeDico(char *filedico);
int is_mot_in_dico(char mot[MAXLENMOT]); 
char mots_tab_existe(char tab_mots[MAXMOTSCREES][MAXLENMOT]); // renvoie 1 si tous les mots font parti du dictionnaire
int distribution(int, int, char board_joueur[7], char pioche[103]);
int lettresPlacees(char mot_crees[MAX_MOTS_CREE_1_TOUR][MAXLENMOT], char lettres_placees[COTE_CASES][COTE_CASES]);
int cherche_mots_et_compte_points(char mots_crees[MAX_MOTS_CREE_1_TOUR][MAXLENMOT], int l, int c, char direction, int len_lettres_placees, char mot_principal_cree[COTE_CASES]);