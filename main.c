#include "toDoList.h"

int main() {
    List *todolist = createList();
    menu(todolist);
    return 0;
}