#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#ifndef TP_TODOLIST_H
#define TP_TODOLIST_H

typedef struct task {
    char name[50];
    time_t date; // Utilisation de time_t pour stocker la date
    char status[10]; // En_attente, En_cours, Terminee
    int days;
    struct task *next;
} Task;

typedef struct list {
    Task *head;

} List;

struct tm;



List *createList();
Task *askTask();
void addTask(List *todolist, Task *newTask);
long dateTodayMidnight();
void updateStatus(Task *task, const char *newStatus);
void printTask(Task *task);
void printList(List *todolist);
void menu(List *todolist);
void updateTasks(List *todolist);
void deleteTasks(List *todolist);
void updateTasksEnCours(List *todolist);

void writeTasksToFile(List *todolist, const char *filename);
void writeTaskToFile(FILE *file, Task *task);
void readTasksFromFile(List *todolist, const char *filename);
#endif //TP_TODOLIST_H