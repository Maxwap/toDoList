#include "toDoList.h"

int main() {

    List *todolist = createList();

    int n=0;
    printf("How many tasks do you want to add? ");
    scanf("%d", &n);

    while (n>0){
        addTask(todolist,askTask());
        n--;
    }
    addTask(todolist,askTask());

    displayList(todolist);
    return 0;
}