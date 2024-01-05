#include "toDoList.h"

int main() {
    FILE *fichier;
    int nombre, continuer;

    // Ouvre le fichier en mode écriture
    fichier = fopen("nombres.txt", "w");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        return 1;
    }

    do {
        printf("Saisissez un nombre : ");
        scanf("%d", &nombre);

        // Écrit le nombre dans le fichier
        fprintf(fichier, "%d\n", nombre);

        printf("Voulez-vous saisir un autre nombre ? (1 pour Oui / 0 pour Non) : ");
        scanf("%d", &continuer);
    } while (continuer != 0);

    // Ferme le fichier
    fclose(fichier);

    printf("Les nombres ont été écrits dans le fichier nombres.txt avec succès.\n");
    List *todolist = createList();
    menu(todolist);
    return 0;
}