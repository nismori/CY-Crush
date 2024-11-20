#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define CB_RED "\033[91m" 
#define CB_GREEN "\033[92m"
#define CB_YELLOW "\033[93m"
#define CB_BLUE "\033[94m"
#define CB_CYAN "\033[96m"
#define CB_WHITE "\033[37m"
#define CB_PURPLE "\033[95m"

#define BB_RED "\033[41m"
#define BB_DEFAULT "\033[0m"

#define TWO 2



void main()
{
    srand(time(NULL)); //pour avoir des symboles aléatoires
    time_t begin = time(NULL); //on démarre le chronomètre qui calcule temps de jeu
    int tab2[TWO], length, width, sign, totalTime = 0, roundNmb, score = 0; // longueur, largeur, nombre de symboles, temps de jeu, nombre de tous, score
    char** tab;
    if(checkGame()) //si on peut charger une sauvegarde...
    {
        if(wantLoadGame()) //et si le joueur le veut...
        {
            length = loadLength(); //alors on récupère la longueur et la largeur enregistré
            width = loadWidth(); 
            tab = malloc(width * sizeof(char*)); //on alloue de la mémoire en fonction de la longueur et de la largeur enregistré
            for (int i = 0; i < width; i++)
            {
                tab[i] = malloc(length * sizeof(char));
            }
            tab[width] = malloc(length * sizeof(int)); //on créé une ligne bonus pour stocker le score
            loadGame(tab,length,width); //on récupère le tableau et le score enregistré
            roundNmb = roundNumber(); //on demande si l'utilisateur veut un nombre de tours
        }
        else
        {
            system("clear"); //on remet à 0 le terminal
            createLength_and_Width(tab2); //on créé une longueur, une largeur, un nombre de signes, un tableau que l'on construit et on le transforme pour qu'il n'ait pas trois symboles côte à côte
            length = tab2[0];
            width = tab2[1];
            sign = createSign(tab2);
            roundNmb = roundNumber();
            tab = malloc(width * sizeof(char*));
            for (int i = 0; i < width; i++)
            {
                tab[i] = malloc(length * sizeof(char));
            }
            tab[width] = malloc(length * sizeof(int));
            buildTab(tab, length, width, sign);
            destroyTabforStart(tab, length, width, sign);
        }
    }
    else
    {
        system("clear");
        createLength_and_Width(tab2); //on créé une longueur, une largeur, un nombre de signes, un tableau que l'on construit et on le transforme pour qu'il n'ait pas trois symboles côte à côte
        length = tab2[0];
        width = tab2[1];
        sign = createSign(tab2);
        roundNmb = roundNumber();
        tab = malloc(width * sizeof(char*));
        for (int i = 0; i < width; i++)
        {
            tab[i] = malloc(length * sizeof(char));
        }
        tab[width] = malloc(length * sizeof(int)); //ligne bonus pour stocker le score
        buildTab(tab, length, width, sign);
        destroyTabforStart(tab, length, width, sign);
    }
    score = tab[width][0]; //le score est actualisé
    showTab(tab, length, width, score); //on affiche le tableau
    if(length<=32 && width<=99) //si les valeurs de length et de width sont corrects (voir les informations donnés au début du mode sans limite)
    {   
        game(tab,length,width,sign,score,roundNmb,begin); //le jeu commence
    }
    score = tab[width][0]; //le score est à nouveau actualisé
    time_t end = time(NULL); //on arrête le chronomètre
    totalTime = end - begin; //on calcule le temps de jeu total
    printf("\n");
    saveHighscore(score, totalTime);
    loadHighscore();
    changeHour(totalTime); //on affiche le temps de jeu total
    free(tab); //on libére l'espace mémoire alloué
}
