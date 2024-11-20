#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "main.h"

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

void buildTab(char **tab, int length, int width, int sign) //programme pour construire le tableau avec sa longueur, sa largeur et son nombre de symboles
{
    int NmbofSymbol;
    for (int i = 0; i < width; i++) //parcours complet de chaque case du tableau
    {
        for (int j = 0; j < length; j++)
        {
            switch (sign) //configure le nombre de symboles
            {
            case 4:
                NmbofSymbol = rand() % 4;
                break;
            case 5:
                NmbofSymbol = rand() % 5;
                break;
            default:
                NmbofSymbol = rand() % 6;
                break;
            }
            switch (NmbofSymbol) //en fonction du nombre de symboles, génère aléatoirement un symbole parmi ceux possibles pour la case. Les symboles sont : U,X,I,O,L,N
            {
            case 0:
                tab[i][j] = 'U';
                break;
            case 1:
                tab[i][j] = 'X';
                break;
            case 2:
                tab[i][j] = 'I';
                break;
            case 3:
                tab[i][j] = 'O';
                break;
            case 4:
                tab[i][j] = 'L';
                break;
            default:
                tab[i][j] = 'N';
                break;
            }
        }
    }
}

char buildoneTab(char **tab, int i, int j, int sign) // fonctionne exactement de la même façon que buildTab, mais ne génère que pour une seule case
{
    int NmbofSymbol;
    switch (sign)
    {
    case 4:
        NmbofSymbol = rand() % 4;
        break;
    case 5:
        NmbofSymbol = rand() % 5;
        break;
    default:
        NmbofSymbol = rand() % 6;
        break;
    }
    switch (NmbofSymbol)
    {
    case 0:
        tab[i][j] = 'U';
        break;
    case 1:
        tab[i][j] = 'X';
        break;
    case 2:
        tab[i][j] = 'I';
        break;
    case 3:
        tab[i][j] = 'O';
        break;
    case 4:
        tab[i][j] = 'L';
        break;
    default:
        tab[i][j] = 'N';
        break;
    }
    return tab[i][j];
}



void showTab(char **tab, int length, int width, int score)
{
    printf("\n"); //on revient à la ligne pour espacer ce qu'il y avait d'écrit précédemment
    printf("    "); //on laisse un espace et on écrit les lettres pour les colonnes en fonction de la longueur
    for (int j = 0; j < length; j++)
    {
        printf("%c ", j + 65);
    }
    printf("\n"); //puis on revient à la ligne et on met des '_' en dessous de chaque lettre
    printf("    ");
    for (int j = 0; j < length; j++)
    {
        printf("_ ");
    }
    printf("\n");
    for (int i = 0; i < width; i++) //ensuite à l'emplacement où l'on a mit les espaces précédemment, on vient mettre des chiffres et des nombres correspondant au nombres : quand c'est un chiffre, on laisse un espace pour qu'un chiffre et un nombre prenne le même espace
    {
        if (i + 1 < 10)
        {
            printf("%d | ", i + 1);
        }
        else
        {
            printf("%d| ", i + 1);
        }
        for (int j = 0; j < length; j++) //puis en fonction du symbole et du nombre de symbole, on attribue une couleur à ce symbole et on laisse un espace pour le suivant. L'espace supplémentaire à la fin n'est pas important. On affiche aussi les espaces(' ') pour montrer la gravité
        {
            switch (tab[i][j])
            {
            case 'U':
                printf("%s%c ", CB_CYAN, tab[i][j]); //U en cyan
                break;
            case 'X':
                printf("%s%c ", CB_RED, tab[i][j]); //X en rouge
                break;
            case 'I':
                printf("%s%c ", CB_PURPLE, tab[i][j]); //I en violet
                break;
            case 'O':
                printf("%s%c ", CB_GREEN, tab[i][j]); //O en vert
                break;
            case 'L':
                printf("%s%c ", CB_BLUE, tab[i][j]); //L en bleu
                break;
            case ' ':
                printf("  ");
                break;
            default:
                printf("%s%c ", CB_YELLOW, tab[i][j]); //N en jaune
                break;
            }
        }
        printf("%s\n", CB_WHITE); //on remet la suite du texte en blanc
    }
    printf("\n"); //on saute une ligne et on affiche le score puis on resaute une ligne derrière
    printf("score = %d\n\n", score);
}



void showTabTransition(char **tab, char **tab2, int length, int width, int score) //fait la même chose que showTab a quelques exceptions. Il faut d'abord voir destroyTab pour mieux la comprendre
{
    printf("\n");
    printf("    ");
    for (int j = 0; j < length; j++)
    {
        printf("%c ", j + 65);
    }
    printf("\n");
    printf("    ");
    for (int j = 0; j < length; j++)
    {
        printf("_ ");
    }
    printf("\n");
    for (int i = 0; i < width; i++)
    {
        if (i + 1 < 10)
        {
            printf("%d | ", i + 1);
        }
        else
        {
            printf("%d| ", i + 1);
        }
        for (int j = 0; j < length; j++)
        {
            if (tab2[i][j] == ' ') //si tab2[i][j] a un espace (qu'on appelle vide), alors ça signifie que le symbole de cette case fait parti d'un groupe de 3 symboles. Il faut alors prendre le symbole qui correspond à ce vide et lui mettre un fond rouge pour faire une transition avec gravity. 
            {
                switch (tab[i][j]) //en fonction du symbole et de si tab2[i][j] a un vide, on attribue la couleur et le fond
                {
                case 'U':
                    printf("%s%s%c%s ", BB_RED, CB_CYAN, tab[i][j], BB_DEFAULT);
                    break;
                case 'X':
                    printf("%s%s%c%s ", BB_RED, CB_RED, tab[i][j], BB_DEFAULT);
                    break;
                case 'I':
                    printf("%s%s%c%s ", BB_RED, CB_PURPLE, tab[i][j], BB_DEFAULT);
                    break;
                case 'O':
                    printf("%s%s%c%s ", BB_RED, CB_GREEN, tab[i][j], BB_DEFAULT);
                    break;
                case 'L':
                    printf("%s%s%c%s ", BB_RED, CB_BLUE, tab[i][j], BB_DEFAULT);
                    break;
                default:
                    printf("%s%s%c%s ", BB_RED, CB_YELLOW, tab[i][j], BB_DEFAULT);
                    break;
                }
            }
            else //s'il n'y a pas d'espace, on fait comme dans un showTab classique
            {
                switch (tab[i][j])
                {
                case 'U':
                    printf("%s%c ", CB_CYAN, tab[i][j]);
                    break;
                case 'X':
                    printf("%s%c ", CB_RED, tab[i][j]);
                    break;
                case 'I':
                    printf("%s%c ", CB_PURPLE, tab[i][j]);
                    break;
                case 'O':
                    printf("%s%c ", CB_GREEN, tab[i][j]);
                    break;
                case 'L':
                    printf("%s%c ", CB_BLUE, tab[i][j]);
                    break;
                default:
                    printf("%s%c ", CB_YELLOW, tab[i][j]);
                    break;
                }
            }
        }
        printf("%s\n", CB_WHITE);
    }
    printf("\n");
    printf("score = %d\n\n", score);
}




void gravityCol(char **tab, int i, int j, int length, int width, int sign) //fait monter les vides en haut du tableau et les transforment les vides en symboles par récurrence
{
    if (i == 0)
    {
        if (tab[i][j] == ' ') //on vérifie que la case est vide par précaution 
        {
            tab[i][j] = buildoneTab(tab, i, j, sign); //puis on donne au vide un symbole aléatoire
        }
    }
    else //on échange la case du tableau (qui est vide) avec celle du dessus et on la fait remonter jusqu'en haut 
    {
        char x;
        x = tab[i - 1][j];
        tab[i][j] = x;
        tab[i - 1][j] = ' ';
        return gravityCol(tab, i - 1, j, length, width, sign); //i désignant la largeur on remonte en executant la fonction en boucle
    }
}



int checkSpace(char **tab, int length, int width) //si le tableau contient des vides, renvoie 1, sinon 0
{
    int v = 0;
    for (int i = 0; i < width; i++) //parcours du tableau
    {
        for (int j = 0; j < length; j++)
        {
            if (tab[i][j] == ' ') //renvoie 1 s'il y'a un vide
            {
                v = 1;
                break; //puis sort du parcours
            }
        }
    }
    return v;
}



void gravity(char **tab, int length, int width, int sign, int score)
{
    system("clear"); //avec ces 3 lignes, on enchaîne rapidement les tableaux avec les symboles qui descendent petit à petit 
    showTab(tab, length, width, score);
    usleep(100000);
    while (checkSpace(tab, length, width)) //tant que le tableau contient des espaces, on continue à faire descendre une ligne de symbole
    {
        for (int j = 0; j < length; j++) //on fait un parcours en colonne à l'envers, c'est à dire que l'on part du bas de la colonne et on la remonte avant de passer à la suivante
        {
            for (int i = width - 1; i >= 0; i--)
            {
                if (tab[i][j] == ' ') //dès qu'on a un vide, on le fait remonter en haut avec GravityCol  
                {
                    gravityCol(tab, i, j, length, width, sign);
                    break; //puis une fois que l'on a trouvé un vide, on passe à la colonne suivante
                }
            }
        }
        system("clear"); //à la fin on affiche un tableau où tous les symboles avec un vide en dessous sont descendus d'une ligne. En le faisant en boucle, on une impression de gravité
        showTab(tab, length, width, score);
        usleep(70000);
    }
}



void destroyTabforStart(char **tab, int length, int width, int sign) //renvoie un tableau qui ne possède pas trois symboles côte à côte en longueur, en largeur et en diagonale. C'est un tableau de départ qui n'applique pas la gravité et ne détecte pas tous les symboles côte à côte 3 à 3, mais renvoie un tableau sans 3 symboles côte à côte
{
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0, v5 = 0, i2, j2;
    while (v1 != 1) // vérifie le tableau tant qu'il n'y a pas un tour sans modification du tableau : le booléen v1 prend 1 comme valeur au début et 0 s'il y a une modification par la suite
    {
        v1 = 1;
        for (int i = 0; i < width; i++) //parcours le tableau
        {
            for (int j = 0; j < length; j++)
            {
                if ((j >= 1 && j < length - 1) && (tab[i][j] == tab[i][j - 1] && tab[i][j] == tab[i][j + 1])) // teste si trois symboles sont identiques horizontalement
                {
                    v2 = 1;
                }
                if (v2 == 1) //si on a trois symboles identiques en longueur on leur donne une nouvelle valeur aléatoire 
                {
                    j2 = j;
                    while ((j2 + 1 < length) && (tab[i][j2 + 1] == tab[i][j])) //teste toutes les cases à droite de la case du tableau où on se trouve actuellement avec le parcours du tableau (tab[i][j]) et leur donne une nouvelle valeur aléatoire si les symboles des cases sont identiques à celui de la case du tableau où on se trouve actuellement
                    {
                        tab[i][j2 + 1] = buildoneTab(tab, i, j2 + 1, sign);
                        j2++;
                    }
                    j2 = j;
                    while ((j2 - 1 >= 0) && (tab[i][j2 - 1] == tab[i][j])) //puis celles à gauche de la case du tableau où on se trouve actuellement
                    {
                        tab[i][j2 - 1] = buildoneTab(tab, i, j2 - 1, sign);
                        j2--;
                    }
                } //ATTENTION : les annotations suivantes sont identiques au précédentes à la différences qu'elle s'appliquent pour 3 symboles en largeur au lieu de 3 symboles en longueur
                if ((i >= 1 && i < width - 1) && (tab[i][j] == tab[i - 1][j] && tab[i][j] == tab[i + 1][j])) // teste si trois symboles sont identiques verticalement
                {
                    v3 = 1;
                }
                if (v3 == 1) //teste les symboles voisins en largeur si v3 vaut 1 (3 symboles identiques en largeur) et les remplace en un nouveau symbole aléatoire s'ils sont identiques
                {
                    i2 = i;
                    while ((i2 + 1 < width) && (tab[i][j] == tab[i2 + 1][j])) //teste toutes les cases au dessus de la case du tableau où on se trouve actuellement avec le parcours du tableau (tab[i][j]) et les remplace en un nouveau symbole aléatoire si les symboles des cases sont identiques à celui de la case du tableau où on se trouve actuellement
                    {
                        tab[i2 + 1][j] = buildoneTab(tab, i2 - 1, j, sign);
                        i2++;
                    }
                    i2 = i;
                    while ((i2 - 1 >= 0) && (tab[i][j] == tab[i2 - 1][j])) //puis celles en dessous de la case du tableau où on se trouve actuellement
                    {
                        tab[i2 - 1][j] = buildoneTab(tab, i2 - 1, j, sign);
                        i2--;
                    }
                }
                if (((i >= 1 && i < width - 1) && (j >= 1 && j < length - 1)) && (tab[i][j] == tab[i - 1][j + 1] && tab[i][j] == tab[i + 1][j - 1])) // teste si trois symboles sont identiques diagonalement de bas à gauche en haut à droite
                {
                    v4 = 1;
                }
                if (v4 == 1)
                {
                    i2 = i;
                    j2 = j;
                    while (((i2 - 1 > 0) && (j2 + 1 < length)) && ((tab[i][j] == tab[i2 - 1][j2 + 1]))) //teste toutes les cases en haut à droite de la case du tableau où on se trouve actuellement avec le parcours du tableau (tab[i][j]) et les remplace en un nouveau symbole aléatoire si les symboles des cases sont identiques à celui de la case du tableau où on se trouve actuellement
                    {
                        tab[i2 - 1][j2 + 1] = buildoneTab(tab, i2 - 1, j2 + 1, sign);
                        i2--;
                        j2++;
                    }
                    i2 = i;
                    j2 = j;
                    while (((i2 + 1 < width) && (j2 - 1 > 0)) && ((tab[i][j] == tab[i2 + 1][j2 - 1]))) //puis celles en bas à gauche de la case du tableau où on se trouve actuellement
                    {
                        tab[i2 + 1][j2 - 1] = buildoneTab(tab, i2 + 1, j2 - 1, sign);
                        i2++;
                        j2--;
                    }
                }
                if (((i >= 1 && i < width - 1) && (j >= 1 && j < length - 1)) && (tab[i][j] == tab[i - 1][j - 1] && tab[i][j] == tab[i + 1][j + 1])) //teste si trois symboles sont identiques diagonalement de bas à droite en haut à gauche
                {
                    v5 = 1;
                }
                if (v5 == 1)
                {
                    i2 = i;
                    j2 = j;
                    while (((i2 - 1 >= 0) && (j2 - 1 >= 0)) && ((tab[i][j] == tab[i2 - 1][j2 - 1]))) //teste toutes les cases en haut à gauche de la case du tableau où on se trouve actuellement avec le parcours du tableau (tab[i][j]) et les remplace en un nouveau symbole aléatoire si les symboles des cases sont identiques à celui de la case du tableau où on se trouve actuellement
                    {
                        tab[i2 - 1][j2 - 1] = buildoneTab(tab, i2 - 1, j2 - 1, sign);
                        i2--;
                        j2--;
                    }
                    i2 = i;
                    j2 = j;
                    while (((i2 + 1 < width) && (j2 + 1 < length)) && ((tab[i][j] == tab[i2 + 1][j2 + 1]))) //puis celles en bas à droite de la case du tableau où on se trouve actuellement
                    {
                        tab[i2 + 1][j2 + 1] = buildoneTab(tab, i2 + 1, j2 + 1, sign);
                        i2++;
                        j2++;
                    }
                }
                if (((v2 == 1) || (v3 == 1)) || ((v4 == 1) || (v5 == 1))) //on exécute ce script si on a eu une détection de 3 cases identiques en largeur, en longueur ou en diagonale
                {
                    tab[i][j] = buildoneTab(tab, i, j, sign); //on attribue un symbole aléatoire à la case du tableau[i][j] où on est actuellement
                    v1 = 0, v2 = 0, v3 = 0, v4 = 0, v5 = 0;   //et on remet tous les booléens à 0
                }
            }
        }
    }
}



int checkSpaceNumber(char **tab2, int width, int length) //compte le nombre d'espace dans la fonction tab2 pour calculer le score. Lié à destroyTab
{
    int score = 0;
    for (int i = 0; i < width; i++) //parcours en largeur
    {
        for (int j = 0; j < length; j++)
        {
            if (tab2[i][j] == ' ') //s'il y a un espace, le score augmente d'une unité
            {
                score++;
            }
        }
    }
    return score;
}



void destroyTab(char **tab, int length, int width, int sign, int score) //renvoie un tableau qui détruit toutes les apparitions de 3 symboles alignés en longueur, largeur et diagonale
{
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0, v5 = 0, i2, j2;
    char **tab2;
    tab2 = malloc((width + 1) * sizeof(char *)); //on fait un second tableau de pointeur
    for (int a = 0; a < width; a++)
    {
        tab2[a] = malloc(length * sizeof(char));
    }
    while (v1 != 1) //vérifie le tableau tant qu'il n'y a pas un tour sans modification du tableau : le booléen v1 prend 1 comme valeur au début et 0 s'il y a une modification par la suite
    {
        for (int i = 0; i < width; i++) //le second tableau prend les même valeur que le premier
        {
            for (int j = 0; j < length; j++)
            {
                tab2[i][j] = tab[i][j];
            }
        }
        v1 = 1;
        for (int i = 0; i < width; i++) //parcours le tableau
        {
            for (int j = 0; j < length; j++)
            {
                if ((j >= 1 && j < length - 1) && (tab[i][j] == tab[i][j - 1] && tab[i][j] == tab[i][j + 1])) //teste si trois symboles sont identiques horizontalement
                {
                    v2 = 1;
                }
                if (v2 == 1) //Si v2 == 1, alors remplace les 3 symboles identiques en longueur par un vide au même emplacement dans le deuxième tableau (car tab[i][j] == tab2[i][j])
                {
                    tab2[i][j] = ' ';
                    tab2[i][j - 1] = ' ';
                    tab2[i][j + 1] = ' ';
                    v1 = 0, v2 = 0; //remet le booléen de détection des trois symboles en longueur à 0
                }
                if ((i >= 1 && i < width - 1) && (tab[i][j] == tab[i - 1][j] && tab[i][j] == tab[i + 1][j])) // teste si trois symboles sont identiques verticalement
                {
                    v3 = 1;
                }
                if (v3 == 1) //Si v3 == 1, alors remplace les 3 symboles identiques en largeur par un vide au même emplacement dans le deuxième tableau (car tab[i][j] == tab2[i][j])
                {
                    tab2[i][j] = ' ';
                    tab2[i - 1][j] = ' ';
                    tab2[i + 1][j] = ' ';
                    v1 = 0, v3 = 0; //remet le booléen de détection des trois symboles en largeur à 0
                }
                if (((i >= 1 && i < width - 1) && (j >= 1 && j < length - 1)) && (tab[i][j] == tab[i - 1][j + 1] && tab[i][j] == tab[i + 1][j - 1])) // teste si trois symboles sont identiques diagonalement de bas à gauche en haut à droite
                {
                    v4 = 1;
                }
                if (v4 == 1) //Si v4 == 1, alors remplace les 3 symboles identiques en diagonale par un vide au même emplacement dans le deuxième tableau (car tab[i][j] == tab2[i][j])
                {
                    tab2[i][j] = ' ';
                    tab2[i - 1][j + 1] = ' ';
                    tab2[i + 1][j - 1] = ' ';
                    v1 = 0, v4 = 0; //remet le booléen de détection des trois symboles en diagonale de bas à gauche en haut à droite à 0
                }
                if (((i >= 1 && i < width - 1) && (j >= 1 && j < length - 1)) && (tab[i][j] == tab[i - 1][j - 1] && tab[i][j] == tab[i + 1][j + 1])) // teste si trois symboles sont identiques diagonalement de bas à droite en haut à gauche
                {
                    v5 = 1;
                }
                if (v5 == 1) //Si v5 == 1, alors remplace les 3 symboles identiques en diagonale par un vide au même emplacement dans le deuxième tableau (car tab[i][j] == tab2[i][j])
                {
                    tab2[i][j] = ' ';
                    tab2[i - 1][j - 1] = ' ';
                    tab2[i + 1][j + 1] = ' ';
                    v1 = 0, v5 = 0; //remet le booléen de détection des trois symboles en diagonale de bas à droite en haut à gauche à 0
                }
            }
        }
        score += checkSpaceNumber(tab2, width, length); //dans cette configuration, le nombre de symboles détruits correspond au nombre de vide dans le second tableau, et c'est cette valeur que prend le score 
        system("clear"); //on affiche alors le tableau où les cases détruites ont un fond rouge pour faire une transition avec la gravité d'où le nom
        showTabTransition(tab, tab2, length, width, score);
        sleep(1);
        gravity(tab2, length, width, sign, score); //puis on applique la gravité
        for (int i = 0; i < width; i++) //enfin le premier tableau prend les valeurs du second tableau
        {
            for (int j = 0; j < length; j++)
            {
                tab[i][j] = tab2[i][j];
            }
        }
    }
    tab[width][0] = score; //le tableau à une ligne bonus où on y stocke le score pour l'emporter hors de la fonction car un double tableau de pointeurs n'a pas besoin d'être retourner
}



int checkTab(char **tab, int length, int width) // sert à vérifier si un échange est possible dans le tableau
{
    int v = 0; //booléen qui prend 1 si un échange est possible et 0 sinon
    for (int i = 0; i < width; i++) //parcours le tableau
    {
        for (int j = 0; j < length; j++) //teste si trois symboles sont identiques en largeur ou en longueur et met le booléen à 1 si c'est le cas
        {
            if ((i >= 1 && i < width - 1) && (tab[i][j] == tab[i - 1][j] && tab[i][j] == tab[i + 1][j]))
            {
                v = 1;
            }
            if ((j >= 1 && j < length - 1) && (tab[i][j] == tab[i][j - 1] && tab[i][j] == tab[i][j + 1]))
            {
                v = 1;
            }
            if (((i >= 1 && i < width - 1) && (j >= 1 && j < length - 1)) && (tab[i][j] == tab[i - 1][j + 1] && tab[i][j] == tab[i + 1][j - 1]))
            {
                v = 1;
            }
            if (((i >= 1 && i < width - 1) && (j >= 1 && j < length - 1)) && (tab[i][j] == tab[i - 1][j - 1] && tab[i][j] == tab[i + 1][j + 1]))
            {
                v = 1;
            }
        }
    }
    return v; // renvoie le booléen qui sert pour des conditions. Si v vaut 1 (le tableau est échangable), alors la condition if est vraie sinon elle est fausse
}



int checkEnd(char **tab, int length, int width) //sert à vérifier si l'on peut encore aligner 3 symboles avec les 4 échanges symboles
{
    char temp1, temp2; //on créé deux variables char
    int v = 0; //et un booleén
    for (int i = 0; i < width; i++) //on fait un parcours du tableau
    {
        for (int j = 0; j < length; j++)
        {
            if (i > 0) //pour éviter d'échanger avec des données non initialisés, on fait i>0 pour un échange avec le haut, j>0 avec la gauche...
            {
                temp1 = tab[i][j]; //puis les deux variables char prennent les valeur de la case du tableau où on est avec le parcours (tab[i][j]) et de celle à gauche (tab[i-1][j])
                temp2 = tab[i - 1][j];
                tab[i][j] = temp2; //et on échange les valeurs des deux cases du tableau
                tab[i - 1][j] = temp1;
                v = checkTab(tab, length, width); //puis on vérifie si un échange est possible avec cet configuration avec checkTab
                tab[i][j] = temp1; //et on redonne au cases du tableau leur valeur de départ
                tab[i - 1][j] = temp2;
                if (v == 1) //et on renvoie 1 si un échange est possible. On le fait maintenant pour éviter que v se voit attribuer 0 avec un autre test
                {
                    return v;
                }
            }
            if (j > 0)
            {
                temp1 = tab[i][j];
                temp2 = tab[i][j - 1];
                tab[i][j] = temp2;
                tab[i][j - 1] = temp1;
                v = checkTab(tab, length, width);
                tab[i][j] = temp1;
                tab[i][j - 1] = temp2;
                if (v == 1)
                {
                    return v;
                }
            }
            if (i < width - 1)
            {
                temp1 = tab[i][j];
                temp2 = tab[i + 1][j];
                tab[i][j] = temp2;
                tab[i + 1][j] = temp1;
                v = checkTab(tab, length, width);
                tab[i][j] = temp1;
                tab[i + 1][j] = temp2;
                if (v == 1)
                {
                    return v;
                }
            }
            if (j < length - 1)
            {
                temp1 = tab[i][j];
                temp2 = tab[i][j + 1];
                tab[i][j] = temp2;
                tab[i][j + 1] = temp1;
                v = checkTab(tab, length, width);
                tab[i][j] = temp1;
                tab[i][j + 1] = temp2;
                if (v == 1)
                {
                    return v;
                }
            }
        }
    }
    return v;
}



int createLength_and_Width_withoutLimits(int *tab) //cette fonction lié à createLength_and_Width permet comme son nom l'indique de créer des tableaux sans limites
{
    printf("%sWARNING: you are in the limitless version of CY-crush.\nYou can create boards of any size you want.\nHowever, the game may run very slowly regularly.\nIf you put a length greater than 32 or a width greater than 99, the game cannot be played and your table will only be displayed.\nIf you put a length greater than 63 or a width greater than 99, the display will not be able to be done correctly but will still be left.\nYou can make arrays that do not allow any combination in this mode (for example an array of size 1x1 or 2x1).\nPress '-1' again to switch back to limit version.%s\n\nWARNING IMPORTANT INFORMATION: \n-this game is not recommended for people with epilepsy\n-it is not recommended to make large tables with few symbols because the program may never end\n-do not modify the text files associated with the program ( length,width,score and array).\nIf you do, put the old values back or delete the file (deleting the file will cause you to lose your save).\n\n", CB_RED, CB_WHITE);
    //le printf ci-dessus indique les divers problèmes, précautions à avoir et consignes lié à la saisie de la longueur et de la largeur et au jeu en général
    int length = 0, width = 0, trash = 0; 
    printf("Select a number of boxes with a length greater than 1: ");
    scanf("%d", &length); //on récupére la valeur si c'est un entier
    while (trash != '\n' && trash != EOF) //si ce n'est pas un entier, la variable trash va récupérer tous les caractères
    {
        trash = getchar();
    }
    trash = 0; //on vide ensuite la variable
    if (length == -1) //on passe de createLength_and_Width_withoutLimits à createLength_and_Width en entrant '-1' lors de la saisie de la longueur ou de la largeur
    {
        system("clear"); //lors de ce passage on rénitialise la console pour que ce soit plus compréhensible à lire
        return createLength_and_Width(tab);
    }
    while (length < 1) //si la valeur de la longueur n'est pas correcte, on redemande en boucle à l'utilisateur saisir la bonne valeur de la même façon que précedemment
    {
        printf("Please select a number of boxes with a length greater than 1: ");
        scanf("%d", &length);
        while (trash != '\n' && trash != EOF)
        {
            trash = getchar();
        }
        trash = 0;
        if (length == -1)
        {
            system("clear");
            return createLength_and_Width(tab);
        }
    }
    printf("Select a number of boxes with a width greater than 1: ");
    scanf("%d", &width); //puis on rentre la largeur de la même façon que précedemment
    while (trash != '\n' && trash != EOF)
    {
        trash = getchar();
    }
    trash = 0;
    if (width == -1)
    {
        system("clear");
        return createLength_and_Width(tab);
    }
    while (width < 1) //on redemande en boucle à l'utilisateur de saisir la bonne valeur de la même façon que précedemment
    {
        printf("Please select a number of boxes with a width greater than 1: ");
        scanf("%d", &width);
        while (trash != '\n' && trash != EOF)
        {
            trash = getchar();
        }
        trash = 0;
        if (width == -1)
        {
            system("clear");
            return createLength_and_Width(tab);
        }
    }
    tab[0] = length; //puis met les valeurs dans un tableau de taille 2. Comme on a un pointeur sur le tableau en paramètre, on ne doit rien retourner
    tab[1] = width;
    return 0; //on met un return 0 par précaution
}



int createLength_and_Width(int *tab) //cette fonction lié à createLength_and_Width_withoutLimits permet comme son nom l'indique de créer des tableaux dont la taille est limité
{
    printf("You are in the limited version of CY-crush.\nIn this version, the number of squares in length and width is limited to 26.\nPress '-1' when choosing squares in length or width to switch to the version limitless.\n\nWARNING IMPORTANT INFORMATION: \n-this game is not recommended for people with epilepsy\n-it is not recommended to make large tables with few symbols because the program may never end\n-do not modify the text files associated with the program ( length,width,score and array).\nIf you do, put the old values back or delete the file (deleting the file will cause you to lose your savegame).\n\n");
    //le printf ci-dessus indique les divers problèmes, précautions à avoir et consignes lié à la saisie de la longueur et de la largeur et au jeu en général
    int width = 0, length = 0, trash = 0;
    printf("Select a number of boxes of length between 1 and 26: ");
    scanf("%d", &length); //on récupére la valeur si c'est un entier
    while (trash != '\n' && trash != EOF) //si ce n'est pas un entier, la variable trash va récupérer tous les caractères
    {
        trash = getchar();
    }
    trash = 0; //on vide ensuite la variable
    if (length == -1)
    {
        system("clear");
        return createLength_and_Width_withoutLimits(tab); //on passe de createLength_and_Width à createLength_and_Width_withoutLimits en entrant '-1' lors de la saisie de la longueur ou de la largeur
    }
    while (length < 1 || length > 26) //si la valeur de la longueur n'est pas correcte, on demande en boucle à l'utilisateur de saisir la bonne valeur de la même façon que précedemment
    {
        printf("Please select a number of boxes of length between 1 and 26: ");
        scanf("%d", &length);
        while (trash != '\n' && trash != EOF)
        {
            trash = getchar();
        }
        trash = 0;
        if (length == -1)
        {
            system("clear");
            return createLength_and_Width_withoutLimits(tab);
        }
    }
    printf("Select a number of boxes of width between 1 and 26: ");
    scanf("%d", &width); //puis on rentre la largeur de la même façon que précedemment
    while (trash != '\n' && trash != EOF)
    {
        trash = getchar();
    }
    trash = 0;
    if (width == -1)
    {
        system("clear");
        return createLength_and_Width_withoutLimits(tab);
    }
    while (width < 1 || width > 26) //on demande en boucle à l'utilisateur de saisir la bonne valeur de la même façon que précedemment
    {
        printf("Please select a number of boxes of width between 1 and 26: ");
        scanf("%d", &width);
        while (trash != '\n' && trash != EOF)
        {
            trash = getchar();
        }
        trash = 0;
        if (width == -1)
        {
            system("clear");
            return createLength_and_Width_withoutLimits(tab);
        }
    }
    if(width < 3 && length < 3) //si jamais la longueur et la largeur sont plus petits que 3, alors on ne peut pas faire de combinaisons
    {
        printf("No combination possible, please try again in 3 seconds.\n");
        sleep(3);
        system("clear");
        return createLength_and_Width(tab);
    }
    tab[0] = length; //puis met les valeurs dans un tableau de taille 2. Comme on a un pointeur sur le tableau en paramètre, on ne doit rien retourner
    tab[1] = width;
    return 0; //on met un return 0 par précaution
}



int createSign(int* tab) //cette fonction permet de choisir le nombre de symboles entre 4 et 6
{
    int sign = 0, trash = 0;
    printf("Select a number of symbols between 4 and 6: ");
    scanf("%d", &sign); //on récupére la valeur si c'est un entier
    while (trash != '\n' && trash != EOF) //si ce n'est pas un entier, la variable trash va récupérer tous les caractères
    {
        trash = getchar();
    }
    trash = 0; //on vide ensuite la variable
    while (sign < 4 || sign > 6) //si le nombre de symboles n'est pas correct, on demande en boucle à l'utilisateur de saisir la bonne valeur de la même façon que précedemment
    {
        printf("Please select a number of symbols between 4 and 6: "); 
        scanf("%d", &sign);
        while (trash != '\n' && trash != EOF)
        {
            trash = getchar();
        }
        trash = 0;
    }
    return sign; //enfin on renvoie le nombre de symboles;
}



int wantStop() //cette fonction demande à l'utilisateur s'il veut arrêter de jouer
{
    int trash = 0;
    char wantStop;
    printf("Do you want to stop here (print 'y' or 'Y' for yes and something else for no) : "); 
    wantStop = getchar(); //on prend le premier caractère et trash récupère tous les autres
    while (trash != '\n' && trash != EOF)
    {
        trash = getchar();
    }
    if (wantStop == 'y' || wantStop == 'Y') //si le joueur dit oui, on renvoie 1
    {
        return 1;
    }
    else //sinon non
    {
        return 0;
    }
}



char **Placeswitch(char **tab, int length, int width, int score) //cette fonction permet d'échanger deux cases côte à côte horizontalement ou verticalement
{
    int x = 0, y = 0, x2 = 0, y2 = 0, trash = 0, S;
    char m1, m2, switchValidate;
    do
    {
        system("clear"); //on affiche le tableau
        showTab(tab,length,width,score);
        S = 0, switchValidate = 0;
        while (trash != '\n' && trash != EOF)
        {
            trash = getchar();
        }
        trash=0;
        printf("What's the letter of the first place : "); //on récupère les coordonées de la première case
        x = getchar(); //on prend le premier caractère correspondant à la coordonnée en longueur et trash récupère tous les autres
        while (trash != '\n' && trash != EOF)
        {
            trash = getchar();
        }
        trash = 0;
        if (x >= 97 && x <= 122) //si la lettre est en minuscule, on la met en majuscule
        {
            x = toupper(x);
        }
        x -= 'A'; //puis on retire la valeur de la première lettre ce qui nous donne la coordonnée en longueur de la première case à échanger
        while (x < 0 || x > length - 1) //on demande à la nouveau la bonne valeur tant que ce n'est pas une lettre comprise dans le tableau
        {
            printf("Please select again the letter of the first place : ");
            x = getchar();
            while (trash != '\n' && trash != EOF)
            {
                trash = getchar();
            }
            trash = 0;
            if (x >= 97 && x <= 122)
            {
                x = toupper(x);
            }
            x -= 'A';
        }
        printf("Next, what's the number of the first place : ");
        scanf("%d", &y); //on demande ensuite le numéro de la ligne correspondant à la coordonnée en largeur et trash récupère tous les caractères entrés
        while (trash != '\n' && trash != EOF)
        {
            trash = getchar();
        }
        trash = 0;
        while (y <= 0 || y > width) //si la coordonnée entrée n'est un entier compris dans le tableau, on demande à nouveau la valeur
        {
            printf("Please select again the number of the first place : ");
            scanf("%d", &y);
            while (trash != '\n' && trash != EOF)
            {
                trash = getchar();
            }
            trash = 0;
        }
        y--; //puis on diminue d'une unité car on doit augmenter la coordonnée de 1 lors de l'affichage et on obtient la coordonée en largeur de la première case
        printf("The box chosen is (%c,%d).\n\n", (x + 65), (y + 1));
        printf("What's the letter of the second place : "); //on fait la même chose pour la deuxième case
        x2 = getchar(); 
        while (trash != '\n' && trash != EOF)
        { 
            trash = getchar();
        }
        trash = 0; 
        if (x2 >= 97 && x2 <= 122)
        {
            x2 = toupper(x2);
        }
        x2 -= 'A';
        while (x2 < 0 || x2 > length - 1)
        {
            printf("Please, select again the letter of the second place : ");
            x2 = getchar(); 
            while (trash != '\n' && trash != EOF)
            { 
                trash = getchar();
            }
            trash = 0; 
            if (x2 >= 97 && x2 <= 122)
            {
                x2 = toupper(x2);
            }
            x2 -= 'A';
        }
        printf("Next, what's the number of the second place : ");
        scanf("%d", &y2);
        while (trash != '\n' && trash != EOF)
        {
            trash = getchar();
        }
        trash = 0;
        while (y2 <= 0 || y2 > width)
        {
            printf("Please select again the number of the second place : ");
            scanf("%d", &y2);
            while (trash != '\n' && trash != EOF)
            {
                trash = getchar();
            }
            trash = 0;
        }
        y2--;
        printf("The box chosen is (%c,%d).\n\n", (x2 + 65), (y2 + 1));
        printf("Is this the box you chose ? (print 'y' or 'Y' for yes and something else for no) : "); //enfin on demande à l'utilisateur de valider son choix
        switchValidate = getchar();
        while (trash != '\n' && trash != EOF)
        { // vider le buffer
            trash = getchar();
        }
        trash = 0;
        printf("\n");
        if(switchValidate != 'y' && switchValidate != 'Y') //si l'utilisateur dit oui, la variable S prend 1. Si S vaut 1, la boucle est rénitialisé
        {
            S = 1;
        }
        else if(x == x2 && y == y2) //on teste différentes erreurs possibles et S prend 1 si elles sont présentes 
        { 
            S = 1;
            printf("Same case ! Try again !\n");
        }
        else if(((x != x2-1 && x2 != x-1) || (y!=y2)) && ((y != y2-1 && y2 != y-1) || (x!=x2)))
        {
            S = 1;
            printf("The two boxes chosen are not neighbors vertically or horizontally !\n");
        }
        else
        {
            m1 = tab[y][x];
            m2 = tab[y2][x2];
            tab[y][x] = m2;
            tab[y2][x2] = m1;
            if (checkTab(tab, length, width))
            {
                return tab; //enfin si aucune erreur n'est détecté, on renvoie le tableau
            }
            else
            {
                tab[y2][x2] = m2;
                tab[y][x] = m1;
                S = 1;
                printf("Cannot destroy anything ! Try again !\n");
            }
        }
        if(S==1)
        {
            printf("Try to swap boxes again in 3 seconds.\n");
            sleep(3);
        }
    } while (S == 1);
}



int roundNumber() //Cette fonction permet à l'utilisateur de choisir un nombre de tours
{
    int roundNumber = 0;
    char roundValidate, trash = 0;
    printf("Do you want to define a number of rounds ? (print 'y' or 'Y' for yes and something else for no) : ");
    roundValidate = getchar(); //on prend le premier caractère et trash récupère tous les autres
    while (trash != '\n' && trash != EOF)
    {
        trash = getchar();
    }
    trash = 0;
    if(roundValidate == 'y' || roundValidate == 'Y') //si l'utilisateur dit oui, on lui demande ensuite son nombre de tours et trash prend les éventuels caractères
    {
        while(roundNumber <= 0)
        {
            printf("Choose a number of rounds greater than 0 : ");
            scanf("%d",&roundNumber);
            while (trash != '\n' && trash != EOF)
            {
                trash = getchar();
            }
            trash = 0;
        }
        return roundNumber;
    }
    else
    {
        return -1; //si l'utilisateur ne veut pas mettre de tours, on renvoie -1
    }
}




void saveScore(int score) //sauvegarde le score dans un fichier. Les fonctions saveWidth et saveLength fonctionnent de la même façon
{
    FILE* file = fopen("score.txt", "w"); //on créé le fichier score
    if (file != NULL) 
    {
        fprintf(file, "%d", score); //puis on y inscrit le score du joueur
        fclose(file);
        printf("Score saved successfully.\n"); //et on affiche que le score a bien été sauvegardé (seulement pour le score)
    } 
    else 
    {
        printf("Error opening score file.\n"); //on affiche qu'il y'a une erreur si on n'a pas pu créé le fichier score
    }
}




void saveLength(int length) 
{
    FILE* file = fopen("length.txt", "w");
    if (file != NULL) 
    {
        fprintf(file, "%d", length);
        fclose(file);
    } 
    else 
    {
        printf("Error opening file length.\n");
    }
}



void saveWidth(int width) 
{
    FILE* file = fopen("width.txt", "w");
    if (file != NULL) 
    {
        fprintf(file, "%d", width);
        fclose(file);
    } 
    else 
    {
        printf("Error opening file width.\n");
    }
}



void saveTab(char** tab, int length, int width) //fonction pour sauvegarder le tableau de bonbons dans un fichier
{
    FILE* file = fopen("tab.txt", "w"); 
    if (file != NULL) {
        for (int i = 0; i < width; i++) //on fait un parcourt du tableau avec width et length, puis on enregistre les symboles du tableau en revenant à la ligne à chaque fin de ligne du tableau
        {
            for (int j = 0; j < length; j++) 
            {
                fprintf(file, "%c", tab[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
        printf("Table saved successfully.\n");
    } 
    else 
    {
        printf("Error while opening table file.\n");
    }
}



void saveGame(char** tab, int length, int width, int score, int begin) //demande au joueur s'il veut sauvegarder le tableau et le fait si c'est le cas
{
    char saveValidate = 0, trash = 0, totalTime = 0;
    printf("Do you want to save your actual game ? (print 'y' or 'Y' for yes and something else for no) : ");
    saveValidate = getchar(); //on prend le premier caractère et trash récupère tous les autres
    while (trash != '\n' && trash != EOF)
    {
        trash = getchar();
    }
    trash = 0;
    if(saveValidate == 'y' || saveValidate == 'Y') //si l'utilisateur dit oui, on enregistre la longueur et la largeur de son tableau ainsi que le tableau et son score
    {
        saveLength(length);
        saveWidth(width);
        saveScore(score);
        saveTab(tab,length,width);
    }
    printf("\n"); 
}  



int loadScore() //fonction pour charger le score à partir d'un fichier. Les fonctions loadWidth et loadLength fonctionnent de la même façon
{
    int score = 0;
    FILE* file = fopen("score.txt", "r"); //on ouvre le fichier score.txt
    if (file != NULL) 
    {
        fscanf(file, "%d", &score); //et on y récupère la valeur qu'on y a enregistré précedemment
        fclose(file);
        printf("Score loaded successfully.\n");
    } 
    else 
    {
        printf("Error opening score file.\n");
    }
    return score;
}




int loadLength() {
    int length = 0;
    FILE* file = fopen("length.txt", "r");
    if (file != NULL) 
    {
        fscanf(file, "%d", &length);
        fclose(file);
    } 
    else 
    {
        printf("Error opening file length.\n");
    }
    return length;
}



int loadWidth() {
    int width = 0;
    FILE* file = fopen("width.txt", "r");
    if (file != NULL) 
    {
        fscanf(file, "%d", &width);
        fclose(file);
    } 
    else 
    {
        printf("Error opening file width.\n");
    }
    return width;
}




void loadTab(char** tab, int length, int width) //fonction pour charger le tableau de bonbons à partir d'un fichier 
{
    FILE* file = fopen("tab.txt", "r");
    if (file != NULL) {
        for (int i = 0; i < width; i++) //parcourt du tableau
        {
            for (int j = 0; j < length; j++) 
            {
                fscanf(file, "%c", &tab[i][j]); //on donne au tableau les valeurs que l'on a enregistré précedemment
            }
            fscanf(file, "\n");
        }
        fclose(file);
        printf("Table loaded successfully.\n");
    } 
    else 
    {
        printf("Error while opening table file.\n");
    }
}



int wantLoadGame() //on demande à l'utilisateur s'il veut charger une partie qu'il a précedemment sauvegardé
{
    char loadValidate = 0, trash = 0;
    printf("Do you want to load the game you save ? (print 'y' or 'Y' for yes and something else for no) : ");
    loadValidate = getchar(); //on prend le premier caractère et trash récupère tous les autres
    while (trash != '\n' && trash != EOF)
    {
        trash = getchar();
    }
    trash = 0;
    if(loadValidate == 'y' || loadValidate == 'Y') //si l'utilisateur dit oui, on renvoie 1
    {
        return 1;
    }
    else //sinon on renvoie 0
    {
        return 0;    
    }

}



void loadGame(char** tab, int length, int width)
{
    int score = loadScore();
    loadTab(tab,length,width); //un nouveau tableau récupère les symboles du tableau sauvegardé 
    tab[width][0] = score; //la ligne bonus du tableau récupère le score
}



void game(char** tab,int length, int width, int sign, int score, int roundNmb, int begin) //le fichier principal qui permet de jouer au jeu
{
    while (checkEnd(tab, length, width)) //tant que des échanges sont possibles
    {
        tab = Placeswitch(tab, length, width, score); //on échange des cases voisines
        showTab(tab, length, width, score);  //puis on affiche le tableau
        destroyTab(tab, length, width, sign, score);  //on détruit le tableau avec les cases échangés
        score = tab[width][0]; //le score est actualisé
        roundNmb--; //si on a définit un nombre de tour, il diminue d'un
        if(roundNmb < 0)
        {
            //ne rien faire. C'est le cas où l'on a refusé de choisir un nombre de tour
        }
        else if(roundNmb == 0) //le jeu s'arrête
        {
            printf("It's over !\n\n");
            break;
        }
        else //on annonce au joueur combien de tours il lui reste
        {
            printf("You have %d rounds left.\n\n",roundNmb);
        }
        saveGame(tab,length,width,score,begin); //on propose au joueur de sauvegarder sa partie
        if (wantStop()) //enfin on demande au joueur s'il veut arrêter de jouer. On termine aussi le jeu si c'est le cas
        {
            printf("\n");
            break;
        }
    }
}


int checkGame() //cette fonction permet de savoir si l'on a une partie correctement sauvegardé en mémoire
{
    int gameExist;
    FILE* file = fopen("score.txt", "r"); //on regarde si on a un score enregistré
    if(file != NULL)
    {
        fclose(file);
        FILE* file = fopen("time.txt", "r"); //puis une longueur
        if(file != NULL)
        {
            fclose(file);
            FILE* file = fopen("length.txt", "r"); //puis une longueur
            if(file != NULL)
            {
                fclose(file);
                FILE* file = fopen("width.txt", "r"); //puis une largeur
                if(file != NULL)
                {
                    fclose(file);
                    FILE* file = fopen("tab.txt", "r"); //puis un tableau
                    if(file != NULL)
                    {
                        fclose(file);
                        return 1; //et on revoie 1 si l'on a tout
                    }
                }
            }
        }
    }
    return 0; //sinon 0
}



void changeHour(int totalTime) //affiche totalTime, qui est en secondes, en heures/minutes/secondes
{
    int hours, minutes, seconds;
    if(totalTime < 60) //en fonction du nombre de secondes on affiche différemment le temps de jeu
    {
        printf("Game time: %d second(s).\n\n",totalTime);    
    }
    else if(totalTime < 3600)
    {
        minutes = totalTime / 60; //ici on calcule nombre de minutes
        seconds = (totalTime % 3600) % 60;
        printf("Game time: %d minute(s) and %d second(s).\n\n",minutes,seconds);
    }
    else
    {
        hours = seconds / 3600; //et ici le nombre d'heures
        minutes = (seconds % 3600) / 60;
        seconds = (totalTime % 3600) % 60;
        printf("Game time: %d hour(s), %d minute(s) and %d second(s).\n\n",hours,minutes,seconds);
    }
}




typedef struct //structure contenant toutes les informations à enregistrer dans le highScore
{
    char name[256];
    int score;
    int time;
} Highscores;



void saveHighscores(int score, int totalTime)
{
    FILE* file = fopen("highscore.txt", "a+"); //ouvre le fichier en mode ajout et lecture et le créé s'il n'existe pas
    if (file == NULL)
    {
        printf("Unable to create/open file.\n");
        return;
    }

    Highscores game;
    game.score = score;
    game.time = totalTime;
    printf("Enter your name : "); //on récupére le nom (avec un fgets qui peut ainsi prendre les espaces), le score et le temps de jeu du joueur
    fgets(game.name, sizeof(game.name), stdin);
    game.name[strcspn(game.name, "\n")] = '\0';

    Highscores gameArray[11]; //on définit un tableau de 11 qui peut ainsi récupérer tous les scores dans le Highscore
    int numScores = 0;

    // Lire les scores existants
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL && numScores < 11)
    {
        sscanf(line, "%[^,],%d,%d", gameArray[numScores].name, &(gameArray[numScores].score), &(gameArray[numScores].time)); //on sauvegarde le score du joueur dans highscore.txt
        if (game.score == gameArray[numScores].score && game.time == gameArray[numScores].time && strcmp(game.name, gameArray[numScores].name) == 0)  //si le nom, le score et le temps sont identiques, on ne l'ajoute pas dans le highscore. On évite ainsi les doublons et avoir exactement le même score et temps est assez improbable involontairement
        {
            fclose(file);
            printf("Your score already exists in the leaderboard.\n\n");
            return;
        }
        numScores++; //on regarde tous les scores enregistrés pour checher les doublons
    }
    if (numScores < 10 || game.score > gameArray[numScores - 1].score) //on vérifie si le score est assez élevé pour être integré dans Highscore
    {
        gameArray[numScores] = game; //et si c'est le cas, on l'ajoute
        numScores++;
        for (int i = 0; i < numScores - 1; i++) //puis on tri le highscore en fonctions des scores
        {
            for (int j = i + 1; j < numScores; j++)
            {
                if (gameArray[j].score > gameArray[i].score)
                {
                    Highscores temp = gameArray[i];
                    gameArray[i] = gameArray[j];
                    gameArray[j] = temp;
                }
            }
        }
        fclose(file);
        file = fopen("highscore.txt", "w"); //ensuite on ouvre highscore en mode écriture
        if (file != NULL)
        {
            for (int i = 0; i < numScores && i < 10; i++) //et on écrit les scores que l'on vient d'enregistrer dans l'ordre croissant dans le fichier
            {
                fprintf(file, "%s,%d,%d\n", gameArray[i].name, gameArray[i].score, gameArray[i].time);
            }
            fclose(file);
            printf("Your score has been saved in the highscores. Congratulation !\n\n"); //on indique au joueur que son score a été enregistré dans le highscore
        }
        else
        {
            printf("Error: Unable to open highscore.txt file.\n");
        }
    }
    else
    {
        fclose(file);
        printf("Your score is not high enough to be recorded in the highscore. Try again !\n\n"); //si le score n'est pas assez élevé le highscore reste tel quel et on indique au joueur que son score n'est pas assez élevé pour être integré au tableau
    }
}




void loadHighscore() //on affiche les scores
{
    int rank = 1;
    FILE* file = fopen("highscore.txt", "r");
    if (file == NULL) 
    {
        printf("Unable to read the file.\n\n\n");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL && rank <= 10)  
    {
        char name[256]; //on crée trois variables pour chacune des données enregistrés dans highscore.txt puis on les affiches
        int score;
        int time;
        sscanf(line, "%[^,],%d,%d", name, &score, &time);
        printf("%d : name = %s, score = %d, Playtime = %ds\n\n\n", rank, name, score, time);
        rank++; //le rang augmente d'un à chaque nouveau score
    }
    fclose(file);
}
