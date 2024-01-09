#include "list.h"

List *createList() {
    List *todolist = malloc(sizeof(List));
    //test si l'allocation a reussi
    if (todolist == NULL) {
        printf("Erreur d'allocation de memoire\n");
        exit(1);
    }
    todolist->head = NULL;
    return todolist;
}

Task *askTask() {
    Task *task = (Task *)malloc(sizeof(Task));
    //test si l'allocation a reussi
    if (task == NULL) {
        printf("Erreur d'allocation de memoire\n");
        exit(1);
    }
    printf("Entrer le nom de la tache: ");
    scanf("%s", task->name);

    task->date = dateCreation();
    printf("Date de creation: %s", ctime(&(task->date))); // Affichez la date pour vérification
    updateStatus(task, "En attente");

    printf("Entrer le nombre de jours pour la realiser: ");
    scanf("%d", &task->days);
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

long dateCreation() {
    time_t timestamp = time(NULL);
    struct tm *timeinfo = localtime(&timestamp);

    timeinfo->tm_hour = 0;
    timeinfo->tm_min = 0;
    timeinfo->tm_sec = 0;

    timestamp = mktime(timeinfo);
    return timestamp;
}

void printTask(Task *task) {
    printf("**************\n");
    printf("Nom de la tache: %s\n", task->name);
    printf("Date de creation: %s", ctime((const time_t *)&(task->date)));
    printf("Statut: %s\n", task->status);
    printf("Nombre de jours pour la realiser: %d\n", task->days);
    printf("**************\n");

}

//fonction qui affiche toutes les taches de la liste
void printList(List *todolist) {
    Task *currentTask = todolist->head;
    while (currentTask != NULL) {
        printTask(currentTask);
        currentTask = currentTask->next;
    }
}
/*
// Fonction pour mettre à jour les tâches en fonction de la date actuelle
void updateTasks(List *todolist) {
    time_t currentTime = time(NULL);
    Task *currentTask = todolist->head;

    while (currentTask != NULL) {
        // Calcul de la différence de jours entre la date actuelle et la date de création de la tâche
        int diffDays = difftime(currentTime, currentTask->date) / (60 * 60 * 24);

        // Mise à jour du nombre de jours restants
        if (diffDays > 0) {
            currentTask->days -= diffDays;

            // Si le nombre de jours restants est égal à 1, mettre le statut à "Terminé"
            if (currentTask->days == 1) {
                updateStatus(currentTask, "Termine");
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
        if (strcmp(currentTask->status, "Termine") == 0) {
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
*/
//fonction qui change le statuts des taches de "en attente" à "en cours" si tant qu'il y a moins de 5 taches en cours
void updateTasksEnCours(List *todolist) {
    Task *currentTask = todolist->head;
    int count = 0;
    while (currentTask != NULL) {
        if (strcmp(currentTask->status, "En cours") == 0) {
            count++;
        }
        currentTask = currentTask->next;
    }
    currentTask = todolist->head;
    while (currentTask != NULL) {
        if (strcmp(currentTask->status, "En attente") == 0 && count < 5) {
            updateStatus(currentTask, "En cours");
            count++;
        }
        currentTask = currentTask->next;
    }
}

void manageTasks(List *todolist) {
    time_t currentTime = time(NULL);
    Task *currentTask = todolist->head;
    Task *previousTask = NULL;

    while (currentTask != NULL) {
        int diffDays = difftime(currentTime, currentTask->date) / (60 * 60 * 24);

        if (diffDays > 0) {
            currentTask->days -= diffDays;

            if (currentTask->days == 1) {
                updateStatus(currentTask, "Termine");
            }
        }

        if (strcmp(currentTask->status, "Termine") == 0) {
            if (previousTask == NULL) {
                todolist->head = currentTask->next;
                free(currentTask);
                currentTask = todolist->head;
                continue;
            } else {
                Task *temp = currentTask;
                currentTask = currentTask->next;
                free(temp);
                previousTask->next = currentTask;
                continue;
            }
        }

        previousTask = currentTask;
        currentTask = currentTask->next;
    }
}

void menu(List *todolist) {
    int choice = 0;
    while (choice != 3) {
        printf("**********MENU**********\n");
        printf("1. Ajouter une tache\n");
        printf("2. Afficher la liste\n");
        printf("3. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Task *newTask = askTask();
            addTask(todolist, newTask);
            //updateTasks(todolist);
            //deleteTasks(todolist);
            manageTasks(todolist);
            updateTasksEnCours(todolist);

        } else if (choice == 2) {
            printList(todolist);
        } else if (choice != 3) {
            printf("Choix invalide\n");
        }
    }
}