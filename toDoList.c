#include "toDoList.h"

//- Créer une liste de tâches vide
List *createList() {
    List *todolist = malloc(sizeof(Task));
    todolist->head = NULL;
    return todolist;
}

//fonction pour rentrer une date
Date* askDate() {
    Date* date = (Date *) malloc(sizeof(Date));
    printf("Enter the year: ");
    scanf("%d", &date->year);
    printf("Enter the month: ");
    scanf("%d", &date->month);
    printf("Enter the day: ");
    scanf("%d", &date->day);
    return date;
}
//fonction qui demande à l'utilisateur de saisir les champs d'une nouvelle tâche
Task* askTask() {
    Task* task = (Task *) malloc(sizeof(Task));
    printf("Enter the name of the task: ");
    scanf("%s", task->name);
    task->date=*askDate();
    printf("Enter the status of the task: ");
    scanf("%s", task->status);
    printf("Enter the days of the task: ");
    scanf("%d", &task->days);
    task->next = NULL;
    return task;
}

Task *addTask(List *todolist){
    Task *task = askTask();
    if (todolist->head == NULL) {
        todolist->head = task;
    } else {
        Task *current = todolist->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = task;
    }
    return task;
}


//fonction qui parcourt la liste et qui ajoute la tâche à la bonne place en fonction de la date
void sortList(List *todolist, Task *task) {

}

//fonction qui regarde si c'est le premiere element de la liste en terme de date et qui ajouter dans todolist head si c'est le cas
void addFirst(List *todolist, Task *task) {
    if (todolist->head == NULL) {
        todolist->head = task;
    } else {
        sortList(todolist, task);
    }
}

//focntion qui parcour et affiche la liste
void displayList(List *todolist) {
    Task *current = todolist->head;
    while (current != NULL) { // Modification de la condition de boucle
        printf("Name: %s\n", current->name);
        printf("Date: %d/%d/%d\n", current->date.day, current->date.month, current->date.year);
        printf("Status: %s\n", current->status);
        printf("Days: %d\n", current->days);
        current = current->next;
    }
}