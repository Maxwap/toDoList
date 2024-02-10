#include "list.h"

List *createList() {
    List *todolist = malloc(sizeof(List));
    if (todolist == NULL) {
        printf("Erreur d'allocation de memoire\n");
        exit(1);
    }
    todolist->head = NULL;
    return todolist;
}

Task *askTask() {
    Task *task = (Task *)malloc(sizeof(Task));
    if (task == NULL) {
        printf("Erreur d'allocation de memoire\n");
        exit(1);
    }
    printf("Entrer le nom de la tache: ");
    scanf("%s", task->name);
    task->date = dateTodayMidnight();

    updateStatus(task, "En_attente");

    printf("Entrer le nombre de jours pour la realiser: ");
    scanf("%d", &task->days);
    //fonction e vérification de saisie
    while (task->days < 1) {
        printf("Le nombre de jours doit etre superieur a 1. Recommencez: ");
        scanf("%d", &task->days);
    }

    return task;
}

void addTask(List *todolist, Task *newTask) {
    Task *currentTask = todolist->head;
    if (currentTask == NULL) {
        todolist->head = newTask;
    } else {
        while (currentTask->next != NULL) {
            currentTask = currentTask->next;
        }
        currentTask->next = newTask;
    }
    newTask->next = NULL;
}

void updateStatus(Task *task, const char *newStatus) {
    strcpy(task->status, newStatus);
}

long dateTodayMidnight() {
    time_t timestamp = time(NULL);
    struct tm *timeinfo = localtime(&timestamp);

    timeinfo->tm_hour = 0;
    timeinfo->tm_min = 0;
    timeinfo->tm_sec = 0;

    timestamp = mktime(timeinfo);
    return timestamp;
}

void printTask(Task *task) {
    printf("*****************************************\n");
    printf("Nom de la tache: %s\n", task->name);

    struct tm *timeinfo = localtime(&(task->date));
    printf("Date de creation: %d/%d/%d\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
    printf("Statut: %s\n", task->status);
    printf("Nombre de jours pour la realiser: %d\n", task->days);
    printf("*****************************************\n");

}

//fonction qui affiche toutes les taches de la liste
void printList(List *todolist) {
    Task *currentTask = todolist->head;
    while (currentTask != NULL) {
        printTask(currentTask);
        currentTask = currentTask->next;
    }
}

// Fonction pour mettre à jour les tâches en fonction de la date actuelle pOUR LES EN COURS
void updateTasks(List *todolist) {
    Task *currentTask = todolist->head;

    while (currentTask != NULL) {
        if (strcmp(currentTask->status, "En_cours") == 0) {
            // Calcul de la différence de jours entre la date actuelle et la date de création de la tâche
            int diffDays = difftime(dateTodayMidnight(), currentTask->date) / (60 * 60 * 24);
            currentTask->days = currentTask->days - diffDays;

            // Mise à jour du nombre de jours restants
            if (currentTask->days < 0) {
                updateStatus(currentTask, "Terminee");
            }
        }
        currentTask = currentTask->next;
    }
}

//fonction qui supprime les taches terminees
void deleteTasks(List *todolist) {
    Task *currentTask = todolist->head;
    Task *previousTask = NULL;

    while (currentTask != NULL) {
        if (strcmp(currentTask->status, "Terminee") == 0) {
            if (previousTask == NULL) {
                todolist->head = currentTask->next;
            } else {
                previousTask->next = currentTask->next;
            }
            free(currentTask);
            currentTask = NULL;
        } else {
            previousTask = currentTask;
            currentTask = currentTask->next;
        }
    }
}

//fonction qui change le statuts des taches de "en attente" à "en cours" si tant qu'il y a moins de 5 taches en cours
void updateTasksEnCours(List *todolist) {
    Task *currentTask = todolist->head;
    int count = 0;
    while (currentTask != NULL) {
        if (strcmp(currentTask->status, "En_cours") == 0) {
            count++;
        }
        currentTask = currentTask->next;
    }
    currentTask = todolist->head;
    while (currentTask != NULL) {
        if (strcmp(currentTask->status, "En_attente") == 0 && count < 5) {
            updateStatus(currentTask, "En_cours");
            count++;
        }
        currentTask = currentTask->next;
    }
}

void menu(List *todolist) {
    updateTasksEnCours(todolist);
    int choice = 0;
    while (choice != 3) {
        printf("**********MENU**********\n");
        printf("1. Ajouter une tache\n");
        printf("2. Afficher la liste\n");
        printf("3. Quitter\n");
        printf("Votre choix: ");

        // Vérification du choix du menu
        while (1) {
            if (scanf("%d", &choice) != 1 || (choice < 1 || choice > 3)) {
                printf("Saisie incorrecte, veuillez saisir 1, 2 ou 3.\n");
                printf("Votre choix: ");
                while (getchar() != '\n'); // Nettoyage du buffer d'entrée
            } else {
                break;
            }
        }

        if (choice == 1) {
            Task *newTask = askTask();
            addTask(todolist, newTask);
            updateTasks(todolist);
            //deleteTasks(todolist);

        } else if (choice == 2) {
            printList(todolist);
        } else if (choice != 3) {
            //sortir du programme
            exit(0);

        }
    }
}

void writeTaskToFile(FILE *file, Task *task) {
    // Écris chaque champ de la tâche dans le fichier
    fprintf(file, "%s %ld %s %d\n", task->name, task->date, task->status, task->days);
}
void writeTasksToFile(List *todolist, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
        return;
    }

    Task *currentTask = todolist->head;
    while (currentTask != NULL) {
        writeTaskToFile(file, currentTask);
        currentTask = currentTask->next;
    }

    fclose(file);
}
void readTasksFromFile(List *todolist, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
        return;
    }

    Task tempTask;
    int count = 0;

    char line[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        // Initialiser tempTask.days avec une valeur par défaut
        tempTask.days = 0;

        // Utilise sscanf pour analyser les champs de la ligne
        if (sscanf(line, "%49s %ld %9s %*[^0-9]%d", tempTask.name, &(tempTask.date), tempTask.status, &(tempTask.days)) >= 3 &&
            strlen(tempTask.name) > 0 && tempTask.date > 0) {



            Task *newTask = (Task *)malloc(sizeof(Task));
            if (newTask == NULL) {
                printf("Erreur d'allocation de mémoire\n");
                exit(1);
            }

            strcpy(newTask->name, tempTask.name);
            newTask->date = tempTask.date;
            strcpy(newTask->status, tempTask.status);
            newTask->days = tempTask.days;

            addTask(todolist, newTask);

            // Ajout de messages de débogage
            printf("Lecture de la tache %d : Nom=%s, Date=%ld, Statut=%s, Jours=%d\n", count, newTask->name, newTask->date, newTask->status, newTask->days);
            count++;
        } else {
            printf("Erreur de lecture de la ligne : %s\n", line);
        }
    }


    // Ajout de messages de débogage
    printf("Nombre total de tâches lues depuis le fichier : %d\n", count);

    if (feof(file)) {
        printf("Fin du fichier atteinte.\n");
    } else if (ferror(file)) {
        printf("Erreur de lecture depuis le fichier.\n");
    }

    fclose(file);

}