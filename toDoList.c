#include "toDoList.h"

//- Créer une liste de tâches vide
List *createList() {
    List *todolist = malloc(sizeof(Task));
    todolist->head = NULL;
    return todolist;
}

//fonction qui récupère uniquement la date actuelle, sans conversion (en secondes depuis 1970)
long dateEpoch() {
    time_t timestamp = time(NULL); // Récupère le timestamp actuel
    return timestamp;
}

//fonction qui arrondit la date actuelle au jour inférieur
long roundDownToDay(long (*dateEpoch)()) {
    long timestamp = dateEpoch(); // Récupère le timestamp actuel
    return timestamp - (timestamp % 86400); // Arrondit au multiple de 86400 inférieur
}

//fonction qui met à jour le statut d'une tâche
void updateTaskStatus(Task *task, const char *newStatus) {
    // Utilisation de strcpy pour copier la nouvelle chaîne de caractères dans task->status
    strcpy(task->status, newStatus);
}

//fonction qui demande à l'utilisateur de saisir les champs d'une nouvelle tâche
Task* askTask() {
    Task* task = (Task *) malloc(sizeof(Task));
    //date automatique et arrondie au jour inférieur et statut automatique "En attente"
    task->date = roundDownToDay(dateEpoch);
    updateTaskStatus(task, "En attente");;

    printf("Enter the name of the task: ");
    scanf("%s", task->name);

    printf("Enter the days of the task: ");
    scanf("%d", &task->days);

    task->next = NULL;
    return task;
}

//fonction qui parcourt la liste et compare les dates, et ajoute la nouvelles tache dans l'ordre croissant des dates
void addTask(List *todolist, Task *task) {
    Task *current = todolist->head;
    if (current == NULL) {
        todolist->head = task;
    } else {
        while (current->next != NULL && current->next->date < task->date) {
            current = current->next;
        }
        task->next = current->next;
        current->next = task;
    }
}

//fonction qui affiche une date en format jj/mm/aaaa à partir d'un timestamp
void printDate(long timestamp) {
    time_t time = (time_t)timestamp;
    struct tm *date = localtime(&time);
    if (date != NULL) {
        printf("Date: %d/%d/%d\n", date->tm_mday, date->tm_mon + 1, date->tm_year + 1900);
    } else {
        printf("Invalid date.\n");
    }
}

//focntion qui parcourt la chaine et affiche les listes
void displayList(List *todolist) {
    Task *current = todolist->head;
    while (current != NULL) { // Modification de la condition de boucle
        printf("Name: %s\n", current->name);
        printDate(current->date);
        printf("Status: %s\n", current->status);
        printf("Days: %d\n", current->days);
        current = current->next;
    }
}

// Fonction pour comparer les jours entre la date de la tâche et la date actuelle
int compareDays(Task *task) {
    long dateDay = roundDownToDay(dateEpoch); // Date actuelle arrondie au jour
    long dateTask = task->date; // Date de la tâche

    // Convertir les timestamps en jours
    int currentDays = (int)(dateDay / 86400);
    int taskDays = (int)(dateTask / 86400);

    // Calcul de la différence de jours
    int daysDifference = taskDays - currentDays;
    return daysDifference;
}

// Fonction qui parcourt la liste, décrémente les jours des tâches "En cours" et retire les tâches terminées
void updateAndRemoveTasks(List *todolist) {
    Task *current = todolist->head;
    Task *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->status, "Terminée") == 0) {
            if (previous == NULL) {
                todolist->head = current->next;
            } else {
                previous->next = current->next;
            }
            Task *temp = current;
            current = current->next;
            free(temp);
        } else if (strcmp(current->status, "En cours") == 0) {
            int daysDifference = compareDays(current);
            if (daysDifference <= 0) {
                updateTaskStatus(current, "Terminée");
                Task *temp = current;
                current = current->next;
                free(temp);
            } else {
                current->days = daysDifference;
                previous = current;
                current = current->next;
            }
        } else {
            previous = current;
            current = current->next;
        }
    }
}

//fonction qui compte les taches en cours
int countTasksEnCours(List *todolist) {
    Task *current = todolist->head;
    int count = 0;
    while (current != NULL) {
        if (strcmp(current->status, "En cours") == 0) {
            count++;
        }
        current = current->next;
    }
    return count;
}

//fonction qui prend en parametre countTaskEnCours et qui change le status des taches en attente a encours tant que count est inférieur a 5
void updateTasksEnAttente(List *todolist, int count) {
    Task *current = todolist->head;
    while (current != NULL && count < 5) {
        if (strcmp(current->status, "En attente") == 0) {
            updateTaskStatus(current, "En cours");
            count++;
        }
        current = current->next;
    }
}

//fonction menu qui permet : d'ajouter des taches, de les afficher, de les mettre a jour et de quitter
void menu(List *todolist) {
    int choice = 0;
    int count = 0;
    int n=0;
    while (choice != 4) {
        printf("******** MENU *******\n");
        printf("1. Add a task\n");
        printf("2. Display the list\n");
        printf("3. Quit\n");
        printf("**********************\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("How many tasks do you want to add? ");
                scanf("%d", &n);

                while (n>0){
                    addTask(todolist,askTask());
                    n--;
                }

                updateAndRemoveTasks(todolist);
                count = countTasksEnCours(todolist);
                updateTasksEnAttente(todolist, count);

                break;
            case 2:
                displayList(todolist);
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}