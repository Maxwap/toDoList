#include "list.h"


int main() {

    List *todolist = createList();
    //readTasksFromFile(todolist, "taches.txt");
    printList(todolist);
    updateTasks(todolist);
    deleteTasks(todolist);
    updateTasksEnCours(todolist);

    menu(todolist);
    //writeTasksToFile(todolist, "taches.txt");
    return 0;
}
