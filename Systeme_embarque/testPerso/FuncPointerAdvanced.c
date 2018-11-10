#include <stdio.h>
//---------Les prototypes-----------
double addition(double n1,double n2);
double soustraction(double n1,double n2);
double multiplication(double n1,double n2);
double division(double n1,double n2);
double (* affichMenu(void))(double,double);

//------Les fonctions de calcul-------
double addition(double n1,double n2)
{
    return n1 + n2;
}
double soustraction(double n1,double n2)
{
    return n1 - n2;
}
double multiplication(double n1,double n2)
{
    return n1 * n2;
}
double division(double n1,double n2)
{
    return n1 / n2;
}

//------Le tableau de pointeur sur fonctions (global)------
double (*listeFonctions[4])(double,double) = {addition,soustraction,multiplication,division};

//--------Fonction du menu--------
double (* affichMenu(void))(double,double)       /*Le retour correspondant à un pointeur sur fonction*/
{
    int choix;                                   /*La variable pour le choix*/
    do{
         printf("-------------------------------MENU--------------------------------------\n");
         printf("Veuillez choisir une operation (en choisissant un nombre entre 1 et 4) :\n");
         printf("1 pour addition\n");
         printf("2 pour soustraction\n");
         printf("3 pour multiplication\n");
         printf("4 pour division\n");
         printf("Votre choix : ");
         scanf("%d",&choix);

    }while(choix < 1 || choix > 4 );        /*En cas d'erreur de saisie*/

    return listeFonctions[choix - 1];       /*On renvoi le pointeur sur la fonction de calcul choisie*/
}

//--------Le main----------
int main(void)
{
     double (*fonctionDeCalcul)(double,double);       /*déclaration du pointeur*/
     double n1,n2;                                    /*Les opérandes*/

     fonctionDeCalcul = affichMenu();                 /*On lit la fonction choisie*/

     printf("Saisissez les operandes : ");            /*On demande la saisie des opérandes*/
     scanf("%lf",&n1);
     scanf("%lf",&n2);

     printf("le resultat du calcul est : %f\n",(*fonctionDeCalcul)(n1,n2));   /*On affiche le résultat*/

     return 0;
}