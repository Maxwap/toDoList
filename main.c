#include "list.h"


int main() {
    int choice;
    List *todolist = createList();
    //printList(todolist);
    updateTasks(todolist);
    deleteTasks(todolist);
    updateTasksEnCours(todolist);

    //menu(todolist);
    do{
        printMenu();
        scanf("%d", &choice);
        getchar(); // consume newline character

        switch (choice) {
            case 1: {
                Task *newTask = askTask();
                addTask(todolist, newTask);
                updateTasksEnCours(todolist);
                break;
            }
            case 2: {
                printList(todolist);
                break;
            }
            case 3: {
                printf("Fin programme\n");
                break;
            }
            default:
                printf("Choix invalide!\n");
                break;

        }
    } while (choice != 3);

    return 0;
}
