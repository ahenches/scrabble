#include "./scrabble.h"
char tabdico[TAILLE_DICO * 2][27];
char Plateau[COTE_CASES][COTE_CASES] = {{0}};
Point LettrePlacer[175];
int indice_lettre_placer = 0;
int main(void)
	{
	char pioche[101];
	chargeDico(FILEDICO);
    sprintf(pioche, "eeeeeeeeeeeeeeeaaaaaaaaaiiiiiiiinnnnnnoooooorrrrrrssssssttttttuuuuuullllldddmmmggbbccppffhhvvjqkwxyz");
	int n_pioche_restant = 100, i;
	int j_to_play = 0;
	Joueur joueurs[N_JOUEURS];
	for(i=0;i<N_JOUEURS;i++)
	    {
	    joueurs[i].points = 0;
	    joueurs[i].lettres_restantes = 0;
	    joueurs[i].action_choisie = 0;
	    printf("Entrer le nom de joueur %d\n",i+1);
	    scanf("%s", joueurs[i].name);
	    }
	affichage();
	actualiser();
	Joueur actuel;

	while(n_pioche_restant>0)
	    {
		actualiser();
	    actuel = joueurs[j_to_play];
	    printf("nombre de jetons restants dans la pioche: %d\n", n_pioche_restant);
        n_pioche_restant = distribution(actuel.lettres_restantes, n_pioche_restant, actuel.board, pioche);
        actuel.lettres_restantes = 7;
        printf("Vous, %s, avez maintenant: %s\n", actuel.name, actuel.board);
		actuel = joueur_joue(actuel);
        j_to_play = (j_to_play+1)%N_JOUEURS;
	    printf("Etat de la pioche: %s\n", pioche);
		actualiser();
        }

	attendre_clic();
	fermer_fenetre();
    return 0;
	}


int distribution(int jetons_joueur_restant, int n_pioche_restant, char board_joueur[JOUEUR_NMAX_LETTER], char pioche[102])
	{
	int i = 0, indice_char_tire;
	srand(time(NULL));
	while (n_pioche_restant > 0 && (jetons_joueur_restant+i)<=7)
	    {
	    do 
	        {
		    indice_char_tire = rand()%101;
	        //printf("%c\n", pioche[indice_char_tire]);
		    }
	    while (pioche[indice_char_tire] == ' ');
	    //printf("%c\n", pioche[indice_char_tire]);
	    board_joueur[jetons_joueur_restant-1+i] = pioche[indice_char_tire];
	    pioche[indice_char_tire] = ' ';
	    n_pioche_restant -= 1;
	    i++;
	    }
	return n_pioche_restant;
	}


















int chargeDico(char *filedico)
{
    FILE *f = fopen(filedico,"r"); // ouverture du fichier

    if (!f) // si ouverture ratée
        {
        fprintf(stderr,"fopen: problème d'ouverture du fichier '%s'\n'",filedico);
        return 0;
        }

    char line[MAXLENMOT]; // la ligne servant à la lecture du fichier

    int mots=0; // indice dans tabdico
    while(fgets(line,MAXLENMOT,f)) // tant que fgets ne renvoie pas nul (eof)
        {
        sscanf(line,"%s\n",tabdico[mots]); // je scanne line et écris dans tabdico
        mots++;
        }
    fclose(f); // fermeture du fichier
    return mots;
}















int is_mot_in_dico(char mot[MAXLENMOT])
	{
	int debut=0, fin=TAILLE_DICO-1, milieu, orientation, nb_comparaison=0;
	char mot_trouve = 0;
	while(!mot_trouve && debut<=fin)
		{
		milieu = (fin+debut)/2;
		printf("case %d: %s\n", milieu, tabdico[milieu]);
		orientation = strcmp(mot, tabdico[milieu]);
		if (orientation == 0)
			mot_trouve = 1;
		else if (orientation > 0)
			debut = milieu+1;
		else
			fin = milieu-1;
		nb_comparaison++;
		}
	if (mot_trouve)
	    {
		printf("le mot %s est bien un mot du dictionnaire\n", mot);
        return 1;
        }
	else
	    {
		printf("le mot %s n'est pas un mot du dictionnaire\n", mot);
		return 0;
		}
	}




char mots_tab_existe(char tab_mots[MAX_MOTS_CREE_1_TOUR][MAXLENMOT])
    {
    int i = 0, ts_mots_existent = 1;
    while(tab_mots[i][0] != 0 && ts_mots_existent == 1)
        {
        printf("test pour mot %s\n", tab_mots[i]);
        if (tab_mots[i][0] != 0)
        	ts_mots_existent = is_mot_in_dico(tab_mots[i]);
        i++;
        }
    if (ts_mots_existent == 0)
        return 0;
    else
        return 1;
    }






//PARTIE GRAPHIQUE :

void affichage() //Fonction qui ouvre une fenetre graphique et affiche le tableau.[
{
	ouvrir_fenetre(RESX, RESY);
	
	Point k = {DEBUT_BOARD_X-5, DEBUT_BOARD_Y-5},coin = {DEBUT_PLATEAU_X,DEBUT_PLATEAU_Y};
	Point point_validate = {RETOUR_VALIDATE_X_DEBUT,VALIDATE_Y_DEBUT},text_validate = {RETOUR_VALIDATE_X_DEBUT+45,VALIDATE_Y_DEBUT+30}, point_retour = {RETOUR_VALIDATE_X_DEBUT, RETOUR_Y_DEBUT},  texte_retour = {RETOUR_VALIDATE_X_DEBUT+45, RETOUR_Y_DEBUT+30};
	dessiner_rectangle(k, 353, 59, blanc);
	dessiner_rectangle(point_validate,RETOUR_VALIDATE_deltX,RETOUR_VALIDATE_deltY,gris);
	afficher_texte("Validez",40,text_validate,blanc);
	dessiner_rectangle(point_retour,RETOUR_VALIDATE_deltX,RETOUR_VALIDATE_deltY,gris);
	afficher_texte("Retour",40,texte_retour,blanc);
	afficher_image("plateau/projet.bmp",coin);

}//]




void afficher_board(char board[7]) //Fonction d'affichage de la main du joueur.[ 
	{
	char path_to_file[6];
	sprintf(path_to_file, "$.bmp");
	Point a = {DEBUT_BOARD_X, DEBUT_BOARD_Y};
	int i;
	for(i=0;i<7;i++)
		{
		path_to_file[0] = board[i];
		afficher_image(path_to_file, a);
		a.x += TAILLE_JETON;
		}
	actualiser();
	}//]


void memoire_plateau(void)
	{
	char path_to_file[6];
	sprintf(path_to_file, "$.bmp");
	int i, j;
	Point p;
	for(i=0;i<COTE_CASES;i++)
		for(j=0;j<COTE_CASES;j++)
			{
			if (Plateau[i][j] != 0)
				{
				p.x = j*TAILLE_CASE+DEBUT_PLATEAU_X;
				p.y = i*TAILLE_CASE+DEBUT_PLATEAU_Y;
				path_to_file[0] = Plateau[i][j];
				afficher_image(path_to_file, p);
				}
			}
	actualiser();
	}



Joueur joueur_joue(Joueur j) // Action du joueur [
    {
    int m, mm;
    Point coin = {DEBUT_PLATEAU_X,DEBUT_PLATEAU_Y};
    int indice_au_debut_du_tour = indice_lettre_placer;
	Point prenom_point = {NOM_X,SCORE_NOM_Y};
	Point score_point = {SCORE_X, SCORE_NOM_Y};
	Point test_point = {DEBUT_PLATEAU_X+PLATEAU_TAILLE + 100, DEBUT_PLATEAU_Y};
	dessiner_rectangle(test_point, 20, 20, red);
	dessiner_rectangle(prenom_point, 300, 70, black);
	dessiner_rectangle(score_point, 300, 70, black);
	afficher_texte(j.name, 40, prenom_point, blanc);
	char score_actuel[5];
	sprintf(score_actuel, "%d", j.points);
	afficher_texte(score_actuel, 40, score_point, blanc);
	afficher_board(j.board);
	int score = 0;
    //char action_finished = 0;
    Point p = {-500, -500}, p2, p_obsolete= {-500,-500};
    char is_lettre_selectionnee = 0, validate = 0;
    Point tableau_des_points_selectionnes[7];
    int tableau_des_points_selectionnes_indice_actuel = 0, tour = 1;
    char mots_crees[MAX_MOTS_CREE_1_TOUR][COTE_CASES + 1] = {{0}};
    char lettres_placees[COTE_CASES][COTE_CASES] = {{0}};
    int indice_du_board_selectionne;
    char fichier[6];
    int raz, razz;
    int c, l;
	sprintf(fichier, "$.bmp");
    while (!validate)
        {
        while (!is_lettre_selectionnee && !validate)
        	{
	        p = attendre_clic();
	        if ((p.x > RETOUR_VALIDATE_X_DEBUT && p.x < RETOUR_VALIDATE_X_DEBUT+RETOUR_VALIDATE_deltX) && (p.y>VALIDATE_Y_DEBUT && p.y<VALIDATE_Y_DEBUT+RETOUR_VALIDATE_deltY))
	        	{
	        	printf("VALIDATING...");
	        	if (score == -1)
	        		{
	        		printf("Vous n'avez pas bien placé vos jetons\n");
	        		
					for(raz=0;raz<7;raz++)
						{	
						tableau_des_points_selectionnes[raz]=p_obsolete;
						}

					for(raz=0;raz<COTE_CASES;raz++)
						for(razz=0;razz<COTE_CASES;razz++)
							lettres_placees[raz][razz]=0;

					for(raz=indice_au_debut_du_tour;raz<indice_lettre_placer;raz++)
						{
						printf("%d", score);
						LettrePlacer[raz]=p_obsolete;
						}
					indice_lettre_placer = indice_au_debut_du_tour;
	        		afficher_image("plateau/projet.bmp",coin);
					afficher_board(j.board);
					memoire_plateau();

	        		}
	        	else
	        		validate = 1;
	        	}
			if ((p.x > RETOUR_VALIDATE_X_DEBUT && p.x < RETOUR_VALIDATE_X_DEBUT+RETOUR_VALIDATE_deltX) && (p.y>RETOUR_Y_DEBUT && p.y<RETOUR_Y_DEBUT+RETOUR_VALIDATE_deltY))
	        	{
        		printf("Vous n'avez pas bien placé vos jetons\n");
        		
				for(raz=0;raz<7;raz++)
					{	
					tableau_des_points_selectionnes[raz]=p_obsolete;
					}

				for(raz=0;raz<COTE_CASES;raz++)
					for(razz=0;razz<COTE_CASES;razz++)
						lettres_placees[raz][razz]=0;

				for(raz=indice_au_debut_du_tour;raz<indice_lettre_placer;raz++)
					{
					printf("%d", score);
					LettrePlacer[raz]=p_obsolete;
					}
				indice_lettre_placer = indice_au_debut_du_tour;
        		afficher_image("plateau/projet.bmp",coin);
				afficher_board(j.board);
				memoire_plateau();

	        	}
	        

	        if (((p.x < DEBUT_BOARD_X) || (p.x > DEBUT_BOARD_X+7*TAILLE_JETON)) || ((p.y < DEBUT_BOARD_Y) || (p.y > DEBUT_BOARD_Y+TAILLE_JETON)) || point_in_board(p,tableau_des_points_selectionnes))
	        	printf("Vous n'avez pas selectionner un jeton\n");
	        else
	        	{
	        	indice_du_board_selectionne = (p.x - DEBUT_BOARD_X) / TAILLE_JETON;
	        	is_lettre_selectionnee = 1;
	        	}
        	}
        if (is_lettre_selectionnee)
        	{
            p.x = ((p.x - DEBUT_BOARD_X) / TAILLE_JETON) * TAILLE_JETON + DEBUT_BOARD_X;
        	p.y = ((p.y - DEBUT_BOARD_Y) / TAILLE_JETON) * TAILLE_JETON + DEBUT_BOARD_Y;
           	dessiner_rectangle(p, TAILLE_JETON, TAILLE_JETON, blanc);
           	tableau_des_points_selectionnes[tableau_des_points_selectionnes_indice_actuel] = p;
           	tableau_des_points_selectionnes_indice_actuel++;
           	actualiser();
            
            printf("la lettre selectionnée est %c\n", j.board[indice_du_board_selectionne]);
            do
            	p2 = attendre_clic();
		   	
		   	while(p2.x < DEBUT_PLATEAU_X || p2.y < DEBUT_PLATEAU_Y || p2.x > DEBUT_PLATEAU_X+PLATEAU_TAILLE || p2.y > DEBUT_PLATEAU_Y+PLATEAU_TAILLE || point_in_plateau(p2, LettrePlacer));
			c = (p2.x - DEBUT_PLATEAU_X) / TAILLE_CASE;
			l = (p2.y - DEBUT_PLATEAU_Y) / TAILLE_CASE;

			lettres_placees[l][c] = j.board[indice_du_board_selectionne];

			p2.x = (((p2.x - DEBUT_PLATEAU_X) / TAILLE_CASE) * TAILLE_CASE + DEBUT_PLATEAU_X);
			p2.y = (((p2.y - DEBUT_PLATEAU_Y) / TAILLE_CASE) * TAILLE_CASE + DEBUT_PLATEAU_Y);
			LettrePlacer[indice_lettre_placer]=p2;
			indice_lettre_placer++;
			p2.x++;
			p2.y++;
			is_lettre_selectionnee = 0;
			fichier[0] = j.board[indice_du_board_selectionne];
			afficher_image(fichier, p2);
			actualiser();
			tour++;
			score = lettresPlacees(mots_crees, lettres_placees);
			if (score != -1)
				dessiner_rectangle(test_point, 20, 20, green);
			else
				dessiner_rectangle(test_point, 20, 20, red);
			int i;
			for(i=0;i<MAX_MOTS_CREE_1_TOUR;i++)
				printf("Le %d mot créé est %s\n", i+1, mots_crees[i]);
			actualiser();
		}
	}
	if (mots_tab_existe(mots_crees))
		{
		for(m=0;m<COTE_CASES;m++)
			{
			for(mm=0;mm<COTE_CASES;mm++)
				if (lettres_placees[m][mm] != 0)
					{
					if (Plateau[m][mm] != 0)
						printf("case deja remplie at %d,%d", m, mm);
					Plateau[m][mm] = lettres_placees[m][mm];
					j.lettres_restantes--;
					}
			}
		j.points += score;
		}
	else 
		{
		printf("FAULT");
		j.lettres_restantes = 7; 
		}
	return j;
    }


char point_in_board(Point p, Point tab[7])
	{
	char is_in = 0;
	int i = 0;
	while (i < 7 && is_in == 0)
		{
		if (p.x > tab[i].x && p.x < tab[i].x+TAILLE_JETON && p.y > DEBUT_BOARD_Y)
			is_in = 1;
		i++;
		}
	return is_in;
	}




char point_in_plateau(Point p, Point tab[175])
	{
	char is_in = 0;
	int i = 0;
	while (i < 175 && is_in == 0)
		{
		if (p.x > tab[i].x && p.x < tab[i].x+TAILLE_CASE && p.y > tab[i].y && p.y < tab[i].y+TAILLE_CASE)
			is_in = 1;
		i++;
		}
	return is_in;
	}

char is_in_tab(int x, int y, Point *tab, int taille_tab)
	{
	int i=0;
	char found = 0;
	while(i<taille_tab && found)
		{
		if (x == tab[i].x && y == tab[i].y)
			found = 1;
		}
	return found;
	}

char is_in_tabint(int x, int *tab)
	{
	int i=0;
	char found = 0;
	while(tab[i] != -1 && found)
		{
		if (x == tab[i])
			found = 1;
		}
	return found;
	}


void tab_to_zero(int *tab, int taille_tab)
	{
	int i;
	for(i=0;i<taille_tab;i++)
		{
		tab[i] = 0;
		}
	}

int cherche_mots_et_compte_points(char mots_crees[MAX_MOTS_CREE_1_TOUR][MAXLENMOT], int l, int c, char direction, int len_lettres_placees, char mot_principal_cree[JOUEUR_NMAX_LETTER])
	{
	Point tabMDouble[N_MOTS_DOUBLE] = {{50, 50}, {650, 50}, {650, 650}, {50, 650}, {100, 100}, {600, 100}, {600, 600}, {100, 600}, {150, 150}, {550, 150}, {550, 550}, {150, 550}, {200, 200}, {500, 200}, {500, 500}, {200, 500}, {350, 350}};
	Point tabMTriple[N_MOTS_TRIPLE] = {{0,0}, {350, 0}, {700, 0}, {0, 350}, {0, 700}, {350, 700}, {700, 700}, {700, 350}};
	Point tabLDouble[N_LETTRE_DOUBLE] = {{150, 0}, {550, 0}, {150, 700}, {550, 750}, {0, 150}, {0, 550}, {700, 150}, {750, 550}};
	Point tabLTriple[N_LETTRE_TRIPLE] = {{50, 250}, {50, 450}, {250, 50}, {250, 250}, {250, 450}, {250, 650}, {450, 50}, {450, 250}, {450, 450}, {450, 650}, {650, 250}, {650, 450}};
	char letter_to_points[2][27] = {{0}, {0,1,1,1,1,1,1,1,1,1,2,2,2,3,3,3,4,4,4,8,8,10,10,10,10,10}};
	int points = 0;
	int ind = 0, mot_points = 0, j;
	sprintf(letter_to_points[0], "einorstuldmgbcpfhvjqkwxyz");
	int indice_mot=1, indice_lettre = 0;
	int r_tab_lettreT[N_LETTRE_TRIPLE] = {-1}, r_tab_lettreD[N_LETTRE_DOUBLE] = {-1};
	int indice_lettreT = 0, indice_lettreD = 0; 
	int count_mdouble = 0, count_mtriple = 0;
	int i, ii = 1, jj = 1, kk;
	int n = 1, o = 1, kkk;
	printf("Nombre de lettres placées: %d\n", len_lettres_placees);
	if (direction == DIRECTION_Y)
		{
		while (Plateau[l-n][c] != 0)
			n++;
		while (Plateau[l+len_lettres_placees+o][c] != 0)
			o++;
		for(kkk=l-n+1;kkk<l+len_lettres_placees+o;kkk++)
			{
			mots_crees[0][indice_lettre] = Plateau[kkk][c];
			if (is_in_tab(kkk, c, tabMDouble, N_MOTS_DOUBLE))
				count_mdouble++;
			else if (is_in_tab(kkk, c, tabLDouble, N_MOTS_TRIPLE))
				count_mtriple++;
			else if (is_in_tab(kkk, c, tabLDouble, N_LETTRE_DOUBLE))
				{
				r_tab_lettreD[indice_lettreD] = indice_lettre;
				indice_lettreD++;
				}
			else if (is_in_tab(kkk, c, tabLTriple, N_LETTRE_TRIPLE))
				{
				r_tab_lettreT[indice_lettreT] = indice_lettre;
				indice_lettreT++;
				}

			indice_lettre++;
			}
		for(kkk=0;kkk<len_lettres_placees;kkk++)
			mots_crees[0][c-o+kkk] = mot_principal_cree[kkk];
		}
	else if (direction == DIRECTION_X)
		{
		while (Plateau[l][c-n] != 0)
			n++;
		while (Plateau[l][c+len_lettres_placees+o] != 0)
			o++;
		for(kkk=c-n+1;kkk<c+len_lettres_placees+o;kkk++)
			{	
			mots_crees[0][indice_lettre] = Plateau[l][kkk];
			indice_lettre++;
			}
		for(kkk=0;kkk<len_lettres_placees;kkk++)
			mots_crees[0][n-o+kkk] = mot_principal_cree[kkk];
		}
	while(mots_crees[0][ind] != 0)
		{
		j = 0;
		while (j < 26 && letter_to_points[0][j] != ind)
			j++;
		if (is_in_tabint(ind, r_tab_lettreD))
			mot_points += letter_to_points[1][j]*2;
		else if (is_in_tabint(ind, r_tab_lettreT))
			mot_points += letter_to_points[1][j]*3;
		else
			mot_points += letter_to_points[1][j];
		ind++;
		}
	for(ind=0;ind<count_mdouble;i++)
		mot_points *= 2;

	for(ind=0;ind<count_mtriple;i++)
		mot_points *= 3;
	printf("%d", mot_points);
	points += mot_points;
	count_mdouble = 0;
	count_mtriple = 0;
	indice_lettreT = 0;
	indice_lettreD = 0;
	tab_to_zero(r_tab_lettreD, N_LETTRE_DOUBLE);
	tab_to_zero(r_tab_lettreT, N_LETTRE_TRIPLE);
	indice_mot++;
	ind = 0;


	if (direction == DIRECTION_X)
		{
		for(i=0;i<len_lettres_placees;i++)
			{
			printf("%d, %dtour: %d\n", l, c, i);
			indice_lettre = 0;
			while (Plateau[l-ii][c] != 0)
				ii++;
			while (Plateau[l+jj][c] != 0)
				jj++;
			printf("%d,%d\n\n", ii, jj);
			printf("Direction X: Il y a des lettres de : %d, %d à %d, %d\n", l-ii+1, c, l+jj-1, c);
			for(kk=l-ii+1;kk<l+jj;kk++)
				{
				//printf("changing my %d word %d letter to %c at %d,%d\n", indice_mot, indice_lettre, Plateau[kk][c], kk, c);
				if (is_in_tab(kkk, c, tabMDouble, N_MOTS_DOUBLE))
					count_mdouble++;
				else if (is_in_tab(kkk, c, tabMTriple, N_MOTS_TRIPLE))
					count_mtriple++;
				else if (is_in_tab(kkk, c, tabLDouble, N_LETTRE_DOUBLE))
					{
					r_tab_lettreD[indice_lettreD] = indice_lettre;
					indice_lettreD++;
					}
				else if (is_in_tab(kkk, c, tabLTriple, N_LETTRE_TRIPLE))
					{
					r_tab_lettreT[indice_lettreT] = indice_lettre;
					indice_lettreT++;
					}
				mots_crees[indice_mot][indice_lettre] = Plateau[kk][c];
				indice_lettre++;
				}
			c ++;
			if (strcmp(mots_crees[indice_mot], ""))
				mots_crees[indice_mot][ii-jj] = mot_principal_cree[i];
			while(mots_crees[indice_mot][ind] != 0)
				{
				j = 0;
				while (j < 26 && letter_to_points[0][j] != ind)
					j++;
				if (is_in_tabint(ind, r_tab_lettreD))
					mot_points += letter_to_points[1][j]*2;
				else if (is_in_tabint(ind, r_tab_lettreT))
					mot_points += letter_to_points[1][j]*3;
				else
					mot_points += letter_to_points[1][j];
				ind++;
				}
			for(ind=0;ind<count_mdouble;i++)
				mot_points *= 2;

			for(ind=0;ind<count_mtriple;i++)
				mot_points *= 3;

			points += mot_points;
			count_mdouble = 0;
			count_mtriple = 0;
			indice_lettreT = 0;
			indice_lettreD = 0;
			tab_to_zero(r_tab_lettreD, N_LETTRE_DOUBLE);
			tab_to_zero(r_tab_lettreT, N_LETTRE_TRIPLE);
			indice_mot++;
			ind = 0;
			}
		}
	else if (direction == DIRECTION_Y) // direction == DIRECTION_Y
		{ 
		for(i=0;i<len_lettres_placees;i++)
			{
			printf("%d, %dtour: %d\n", l, c, i);
			indice_lettre = 0;
			while (Plateau[l][c-ii] != 0)
				ii++;
			while (Plateau[l][c+jj] != 0)
				jj++;
			//printf("Direction Y: Il y a des lettres de : %d, %d à %d, %d\n",l, c-ii+1, l, c+jj-1);
			for(kk=c-ii+1;kk<=c+jj;kk++)
				{
				if (is_in_tab(kkk, c, tabMDouble, N_MOTS_DOUBLE))
					count_mdouble++;
				else if (is_in_tab(kkk, c, tabMTriple, N_MOTS_TRIPLE))
					count_mtriple++;
				else if (is_in_tab(kkk, c, tabLDouble, N_LETTRE_DOUBLE))
					{
					r_tab_lettreD[indice_lettreD] = indice_lettre;
					indice_lettreD++;
					}
				else if (is_in_tab(kkk, c, tabLTriple, N_LETTRE_TRIPLE))
					{
					r_tab_lettreT[indice_lettreT] = indice_lettre;
					indice_lettreT++;
					}
				printf("changing my %d word %d letter to %c at %d,%d\n", indice_mot, indice_lettre, Plateau[l][kk], l, kk);
				mots_crees[indice_mot][indice_lettre] = Plateau[l][kk];
				indice_lettre++;
				}
			l ++;
			if (strcmp(mots_crees[indice_mot], ""))
				mots_crees[indice_mot][ii-jj] = mot_principal_cree[i];
			while(mots_crees[indice_mot][ind] != 0)
				{
				j = 0;
				while (j < 26 && letter_to_points[0][j] != ind)
					j++;
				if (is_in_tabint(ind, r_tab_lettreD))
					mot_points += letter_to_points[1][j]*2;
				else if (is_in_tabint(ind, r_tab_lettreT))
					mot_points += letter_to_points[1][j]*3;
				else
					mot_points += letter_to_points[1][j];
				ind++;
				}
			for(ind=0;ind<count_mdouble;i++)
				mot_points *= 2;

			for(ind=0;ind<count_mtriple;i++)
				mot_points *= 3;

			points += mot_points;
			count_mdouble = 0;
			count_mtriple = 0;
			indice_lettreT = 0;
			indice_lettreD = 0;
			tab_to_zero(r_tab_lettreD, N_LETTRE_DOUBLE);
			tab_to_zero(r_tab_lettreT, N_LETTRE_TRIPLE);
			indice_mot++;
			ind = 0;
			}
		}
	else 
		printf("One Letter-Word\n");

	printf("POINTS %d", points);
	return points;
	}











int lettresPlacees(char mots_crees[MAX_MOTS_CREE_1_TOUR][COTE_CASES+1], char lettres_placees[COTE_CASES][COTE_CASES])
	{
	int first_indice_col = 0, first_indice_lig = 0, len_lettres_placees = 0;
	char direction;
	int i, j, k, ii, iii=0;
	int tab_pos_lettre_composant_mot_principal[6][2] = {{0}};
	int indice_tab_pos_lettre_composant_mot_principal = 0;
	char mot_principal_cree[COTE_CASES] = {0};
	char mot_already_created = 0;
	int works = 1, points_faits = 0;
	char boolean;	// Verifie que la lettre fait partie des lettres chainnées entre elles

	for(i=0;i<COTE_CASES;i++)
		{
		for(j=0;j<COTE_CASES;j++)
			{
			for(ii=0;ii<7;ii++)
				{
				if (tab_pos_lettre_composant_mot_principal[ii][0] == i && tab_pos_lettre_composant_mot_principal[ii][1] == j)
					boolean = 1; 
				}
			if (lettres_placees[i][j] != 0 && boolean == 0)
				{
				if (mot_already_created)
					works = 0;	

				k = 1;
				mot_already_created = 1;
				mot_principal_cree[0] = lettres_placees[i][j];
				len_lettres_placees++;
				first_indice_lig = i;
				first_indice_col = j;

				if (lettres_placees[i+1][j] != 0)
					{
					printf("mot colonne\n");
					direction = DIRECTION_Y;
					while (lettres_placees[i+k][j] != 0)
						{
						
						mot_principal_cree[k] = lettres_placees[i+k][j];
						tab_pos_lettre_composant_mot_principal[indice_tab_pos_lettre_composant_mot_principal][0] = i+k;
						tab_pos_lettre_composant_mot_principal[indice_tab_pos_lettre_composant_mot_principal][1] = j;
						k++;
						indice_tab_pos_lettre_composant_mot_principal++;
						len_lettres_placees++;
						}
					}
				else if (lettres_placees[i][j+1] != 0)
					{
					direction = DIRECTION_X;
					printf("mot ligne\n");
					while (lettres_placees[i][j+k] != 0) 
						{
						
						mot_principal_cree[k] = lettres_placees[i][j+k];
						tab_pos_lettre_composant_mot_principal[indice_tab_pos_lettre_composant_mot_principal][0] = i;
						tab_pos_lettre_composant_mot_principal[indice_tab_pos_lettre_composant_mot_principal][1] = j+k;
						k++;
						indice_tab_pos_lettre_composant_mot_principal++;
						len_lettres_placees++;
						}
					}
				else
					{
					direction = UNE_LETTRE;
					printf("Le mot principal créé contient une lettre: %c\n", lettres_placees[i][j]);
					}
				}

			boolean = 0;
			}
		}
	
	
	printf("Lettre chainées créées: ");
	while (iii < COTE_CASES && mot_principal_cree[iii] != 0)
		{
		printf("%c", mot_principal_cree[iii]);
		iii++;
		}
	printf("\n");

	if (works)
		{
		points_faits = cherche_mots_et_compte_points(mots_crees, first_indice_lig, first_indice_col, direction, len_lettres_placees, mot_principal_cree);
		return points_faits;
		}
	printf("\nworks? : %d\n", works);
	return -1;
	}
