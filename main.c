#include <stdio.h>

int main() {
    FILE *P_FICHIER;

    // Ouvrir le fichier en mode ajout (append)
    P_FICHIER = fopen("todolist.txt", "a");
    if (P_FICHIER == NULL) {
        printf("Erreur lors de l'ouverture du fichier en mode ajout.\n");
        return 1;
    }

    fprintf(P_FICHIER, "nico\n"); // Ajouter le contenu au fichier
    fclose(P_FICHIER);

    // Ouvrir le fichier en mode lecture
    P_FICHIER = fopen("todolist.txt", "r");
    if (P_FICHIER == NULL) {
        printf("Erreur lors de l'ouverture du fichier en mode lecture.\n");
        return 1;
    }

    char buffer[100]; // Pour stocker les données lues
    fscanf(P_FICHIER, "%s", buffer); // Lire le contenu du fichier dans 'buffer'
    printf("Contenu lu depuis le fichier : %s\n", buffer);

    fclose(P_FICHIER);

    //List *todolist = createList();
    //menu(todolist);
    return 0;
}
