#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{

    char selection;

    do
    {
        printf("1. Ajouter un membre\n");
        printf("2. Retirer un membre\n");
        printf("q. Quitter\n\n");

        printf("Entrez votre sélection\n");
        scanf("%c%*c", &selection);

        switch (selection)
        {
        case '1':
            printf("Ajout d'un membre\n\n");
            break;

        case '2':
            printf("Retirer un membre \n\n");
            break;

        case 'q':
            break;

        default:
            printf("L'action n'existe pas \n\n");
            break;
        }

    } while (selection != 'q');

    return 0;
}
