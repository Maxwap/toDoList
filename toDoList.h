#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#ifndef TP_TODOLIST_H
#define TP_TODOLIST_H

typedef struct task {
    char name[50];
    long date;
    char status[10];
    int days;
    struct task *next;
}Task;

typedef struct list {
    Task *head;
}List;

struct tm;

//- Créer une liste de tâches vide
List *createList();

long dateEpoch();

long roundDownToDay(long (*dateEpoch)());

void updateTaskStatus(Task *task, const char *newStatus);

Task *askTask();

void addTask(List *, Task *);

void printDate(long timestamp);

int compareDays(Task *task);

void updateAndRemoveTasks(List *todolist);

int countTasksEnCours(List *todolist);

void displayList(List * );

void menu(List *todolist);

#endif //TP_TODOLIST_H