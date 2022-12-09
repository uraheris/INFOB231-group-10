# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>

struct member {
    char firstName[20];
    char lastName[20];
    char phone[10];    
    char email[30];
    int isActive;
};

void addMember(struct member member, char filePath[]) {
    // open file
    int dataBaseFile = open(filePath, O_RDWR | O_CREAT);

    // check if file could be opened
    if (dataBaseFile == -1) {
        printf("Could not open file\n");
        exit(1);
    }

    struct member tempMember;
    int emptyMemberFound = 0;
    int memberCounter = 0;

    // if there is an empty member, move file pointer to that member
    while (read(dataBaseFile, &tempMember, sizeof(struct member)) > 0 && emptyMemberFound == 0) {
        if (strcmp(tempMember.firstName, "") == 0) {
            lseek(dataBaseFile, memberCounter * sizeof(struct member), SEEK_SET);
            printf("Empty member found\n");
            emptyMemberFound = 1;

            // write member to file
            write(dataBaseFile, &member, sizeof(struct member));

            // close file
            close(dataBaseFile);
            return;
        }
        memberCounter++;
    }

    // if there is no empty member, move file pointer to end of file
    if (emptyMemberFound == 0) {
        printf("No empty member found\n");
        lseek(dataBaseFile, 0, SEEK_END);

        // write member to file
        write(dataBaseFile, &member, sizeof(struct member));

        // close file
        close(dataBaseFile);
        return;
    }
}

void deleteMember(char email[], char filePath[]) {
    // open file
    int dataBaseFile = open(filePath, O_RDWR);
    // check if file could be opened
    if (dataBaseFile == -1) {
        printf("Could not open file\n");
        exit(1);
    }
    // read file
    struct member readMember;
    int memberCounter = 0;
    while (read(dataBaseFile, &readMember, sizeof(struct member)) > 0) {
        // check if member is the one to be deleted
        if (strcmp(readMember.email, email) == 0) {
            lseek(dataBaseFile, memberCounter * sizeof(struct member), SEEK_SET);
            struct member voidMember = {"", "", "", "", 0};
            write(dataBaseFile, &voidMember, sizeof(struct member));
        }
        memberCounter++;
    }
    // close file
    close(dataBaseFile);
}

void listMembers(char filePath[], int isActive) {
    // open file
    int dataBaseFile = open(filePath, O_RDONLY);

    // check if file could be opened
    if (dataBaseFile == -1) {
        printf("Could not open file\n");
        exit(1);
    }

    // read file
    struct member readMember;
    while (read(dataBaseFile, &readMember, sizeof(struct member)) > 0) {
        if (strcmp(readMember.firstName, "") != 0 && readMember.isActive == isActive) {
            printf("Prénom: %s\n", readMember.firstName);
            printf("Nom: %s\n", readMember.lastName);
            printf("Téléphone: %s\n", readMember.phone);
            printf("Email: %s\n", readMember.email);
            printf("Actif: %d\n\n", readMember.isActive);
        }
    }
    // close file
    close(dataBaseFile);
}

void showMemberInfo(char filePath[], char name[]) {
    // open file
    int dataBaseFile = open(filePath, O_RDONLY);

    // check if file could be opened
    if (dataBaseFile == -1) {
        printf("Could not open file\n");
        exit(1);
    }

    // read file
    struct member readMember;
    while (read(dataBaseFile, &readMember, sizeof(struct member)) > 0) {
        if (strcmp(readMember.lastName, name) == 0) {
            printf("Prénom: %s\n", readMember.firstName);
            printf("Nom: %s\n", readMember.lastName);
            printf("Téléphone: %s\n", readMember.phone);
            printf("Email: %s\n", readMember.email);
            printf("Actif: %d\n\n", readMember.isActive);
        }
    }
    // close file
    close(dataBaseFile);
}

int main(int argc, char const *argv[])
{
    char selection;
    do
    {
        printf("1. Ajouter un membre\n");
        printf("2. Retirer un membre\n");
        printf("3. Lister les membres\n");
        printf("4. Afficher les informations d'un membre\n");
        printf("q. Quitter\n\n");

        printf("Entrez votre sélection: \n");
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
            printf("Entrez le prénom du membre: \n");
            scanf("%s", firstName);
            printf("Entrez le nom du membre: \n");
            scanf("%s", lastName);
            printf("Entrez le numéro de téléphone du membre: \n");
            scanf("%s", phone);
            printf("Entrez l'adresse email du membre: \n");
            scanf("%s", email);
            printf("Le membres est-il actif? (1 = oui, 0 = non) \n");
            scanf("%d", &isActive);

            // create member
            struct member newMember;
            strcpy(newMember.firstName, firstName);
            strcpy(newMember.lastName, lastName);
            strcpy(newMember.phone, phone);
            strcpy(newMember.email, email);
            newMember.isActive = isActive;
            addMember(newMember, "asblMembersDatabase.txt");

            printf("Membre ajouté avec succès\n\n");
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

            printf("Membre retiré avec succès\n\n");
            break;

        case '3':
            printf("\n\n__Liste des membres__\n");
            // ask user if he wants to list active or inactive members
            printf("Vous pouvez choisir de lister les membres actifs ou inactifs\n");
            printf("1. Actifs\n");
            printf("2. Inactifs\n");

            // get user input
            printf("Entrez votre sélection: \n");
            scanf("%c", &selection);
            switch (selection)
            {
            case '1':
                listMembers("asblMembersDatabase.txt", 1);
                break;

            case '2':
                listMembers("asblMembersDatabase.txt", 0);
                break;

            default:
                printf("L'action n'existe pas \n\n");
                break;
            }
            break;

        case '4':
            printf("\n\n__Afficher les informations d'un membre__\n");
            // variable initialization
            char name[20];

            // get user input
            printf("Entrez le nom du membre: \n");
            scanf("%s", name);

            // show member info
            showMemberInfo("asblMembersDatabase.txt", name);

            break;

        case 'q':
            printf("Au revoir\n");
            break;

        default:
            printf("L'action n'existe pas \n\n");
            break;
        }

    } while (selection != 'q');

    return 0;
}
