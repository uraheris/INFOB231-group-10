#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

struct member
{
    char firstName[20];
    char lastName[20];
    char phone[10];
    char email[30];
    int isActive;
};

void addMember(struct member member, char filePath[])
{
    // open file
    int dataBaseFile = open(filePath, O_RDWR | O_CREAT);

    // check if file could be opened
    if (dataBaseFile == -1)
    {
        printf("Could not open file\n");
        return;
    }

    struct member tempMember;
    int emptyMemberFound = 0;
    int memberCounter = 0;

    // if there is an empty member, move file pointer to that member
    while (read(dataBaseFile, &tempMember, sizeof(struct member)) > 0 && emptyMemberFound == 0)
    {
        if (strcmp(tempMember.firstName, "") == 0)
        {
            lseek(dataBaseFile, memberCounter * sizeof(struct member), SEEK_SET);
            emptyMemberFound = 1;

            // write member to file
            write(dataBaseFile, &member, sizeof(struct member));

            // close file
            close(dataBaseFile);
            printf("Membre ajouté avec succès\n\n");
            return;
        }
        memberCounter++;
    }

    // if there is no empty member, move file pointer to end of file
    if (emptyMemberFound == 0)
    {
        lseek(dataBaseFile, 0, SEEK_END);

        // write member to file
        write(dataBaseFile, &member, sizeof(struct member));

        // close file
        close(dataBaseFile);
        printf("Membre ajouté avec succès\n\n");
        return;
    }
}

void deleteMember(char email[], char filePath[])
{
    // open file
    int dataBaseFile = open(filePath, O_RDWR);
    // check if file could be opened
    if (dataBaseFile == -1)
    {
        printf("Could not open file\n");
        return;
    }
    // read file
    int memberFound = 0;
    int memberCounter = 0;
    struct member readMember;
    while (read(dataBaseFile, &readMember, sizeof(struct member)) > 0)
    {
        // check if member is the one to be deleted
        if (strcmp(readMember.email, email) == 0)
        {
            memberFound = 1;
            lseek(dataBaseFile, memberCounter * sizeof(struct member), SEEK_SET);
            struct member voidMember = {"", "", "", "", 0};
            write(dataBaseFile, &voidMember, sizeof(struct member));
        }
        memberCounter++;
    }

    // member found
    if (memberFound == 0)
    {
        printf("Membre non trouvé\n\n");
    }
    // member not found
    else
    {
        printf("Membre supprimé avec succès\n\n");
    }

    // close file
    close(dataBaseFile);
}

void listMembers(char filePath[], int isActive)
{
    // open file
    int dataBaseFile = open(filePath, O_RDONLY);

    // check if file could be opened
    if (dataBaseFile == -1)
    {
        printf("Could not open file\n");
        return;
    }

    // print header
    (isActive == 1) ? printf("\n_Liste des membres actifs_ \n") : printf("_Liste des membres inactifs_ \n");
    
    // read file and print members
    int memberFound = 0;
    struct member readMember;
    while (read(dataBaseFile, &readMember, sizeof(struct member)) > 0)
    {
        if (strcmp(readMember.firstName, "") != 0 && readMember.isActive == isActive)
        {
            memberFound = 1;
            printf("Prénom: %s\n", readMember.firstName);
            printf("Nom: %s\n", readMember.lastName);
            printf("Téléphone: %s\n", readMember.phone);
            printf("Email: %s\n", readMember.email);
            printf("Actif: %d\n\n", readMember.isActive);
        }
    }

    // no member found
    if (memberFound == 0)
    {
        printf("Aucun membre trouvé\n\n");
    }

    // close file
    close(dataBaseFile);
}

void showMemberInfo(char filePath[], char name[])
{
    // open file
    int dataBaseFile = open(filePath, O_RDONLY);

    // check if file could be opened
    if (dataBaseFile == -1)
    {
        printf("Could not open file\n");
        return;
    }

    // print header
    printf("\n_Informations du membre_ \n");

    // read file and print info
    int memberFound = 0;
    struct member readMember;
    while (read(dataBaseFile, &readMember, sizeof(struct member)) > 0)
    {
        if (strcmp(readMember.lastName, name) == 0)
        {
            memberFound = 1;
            printf("Prénom: %s\n", readMember.firstName);
            printf("Nom: %s\n", readMember.lastName);
            printf("Téléphone: %s\n", readMember.phone);
            printf("Email: %s\n", readMember.email);
            printf("Actif: %d\n\n", readMember.isActive);
        }
    }

    // member not found
    if (memberFound == 0)
    {
        printf("Membre non trouvé\n\n");
    }

    // close file
    close(dataBaseFile);
}

int main(int argc, char const *argv[])
{
    char selection;
    do
    {
        printf("\n\n__Menu__\n");
        printf("1. Ajouter un membre\n");
        printf("2. Retirer un membre\n");
        printf("3. Lister les membres\n");
        printf("4. Afficher les informations d'un membre\n");
        printf("q. Quitter\n\n");

        printf("Entrez votre sélection: ");
        scanf("%c", &selection);

        switch (selection)
        {
        case '1':
            printf("\n\n__Ajout d'un membre__\n");
            // variables initialization
            char firstName[20];
            char lastName[20];
            char phone[10];
            char email[30];
            int isActive;

            // get user input
            printf("Entrez le prénom du membre: ");
            scanf("%s", firstName);
            printf("Entrez le nom du membre: ");
            scanf("%s", lastName);
            printf("Entrez le numéro de téléphone du membre: ");
            scanf("%s", phone);
            printf("Entrez l'adresse email du membre: ");
            scanf("%s", email);
            printf("Le membres est-il actif? (1 = oui, 0 = non): ");
            scanf("%d", &isActive);

            // create member
            struct member newMember;
            strcpy(newMember.firstName, firstName);
            strcpy(newMember.lastName, lastName);
            strcpy(newMember.phone, phone);
            strcpy(newMember.email, email);
            newMember.isActive = isActive;
            addMember(newMember, "asblMembersDatabase.txt");

            break;

        case '2':
            printf("\n\n__Retirer un membre__\n");
            // variables initialization
            char emailToDelete[30];

            // get user input
            printf("Entrez l'adresse email du membre à retirer: \n");
            scanf("%s", emailToDelete);

            // delete member
            deleteMember(emailToDelete, "asblMembersDatabase.txt");

            break;

        case '3':
            printf("\n\n__Liste des membres__\n");
            // ask user if he wants to list active or inactive members
            printf("Vous pouvez choisir de lister les membres actifs ou inactifs\n");
            printf("1. Actifs\n");
            printf("0. Inactifs\n\n");

            // get user input
            int isActiveSelection;
            printf("Entrez votre sélection: ");
            scanf("%d", &isActiveSelection);
            listMembers("asblMembersDatabase.txt", isActiveSelection);
            break;

        case '4':
            printf("\n\n__Afficher les informations d'un membre__\n");
            // variable initialization
            char name[20];

            // get user input
            printf("Entrez le nom du membre: ");
            scanf("%s", name);

            // show member info
            showMemberInfo("asblMembersDatabase.txt", name);

            break;

        case 'q':
            printf("Au revoir\n");
            break;

        default:
            printf("L'action n'existe pas\n\n");
            break;
        }

    } while (selection != 'q');

    return 0;
}
