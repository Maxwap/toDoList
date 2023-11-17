#include "toDoList.h"

int main() {
    List *todolist = createList();
    sortList(todolist,addTask(todolist));
    //sortList(todolist,addTask(todolist));
    sortList(todolist,addTask(todolist));
    displayList(todolist);
    return 0;
}