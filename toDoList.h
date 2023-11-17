#include<stdio.h>
#include<stdlib.h>

#ifndef TP_TODOLIST_H
#define TP_TODOLIST_H

//Une liste de tâches contient des tâches où chaque tâche est définie par :
//- Son nom
//- Sa date de création
//- Son statut : En attente, En cours ou Terminée
//- Un nombre de jours nécessaires pour la terminer
typedef struct date {
    int year;
    int month;
    int day;
}Date;

typedef struct task {
    char name[50];
    Date date;
    char status[50];
    int days;
    struct task *next;
}Task;

typedef struct list {
    Task *head;
}List;



//Une tâche est créée avec le statut « En attente » et un nombre de jours >1 pour être terminée.

//Afin de mettre en place cette liste de tâches, vous devez implémenter les algorithmes suivants :
//- Créer une liste de tâches vide
//- Ajouter une tâche donnée à une liste de tâches donnée
//- Afficher les tâches d’une liste de tâches donnée (toutes les informations doivent
//être affichées) dans l’ordre croissant des dates
//- Chercher les tâches Terminées d’une liste de tâches donnée et les retirer
//- Décrémenter les jours des tâches « En cours » et les changer en « Terminée » s’il
//reste 0 jours.
//- Changer les tâches de « En_attente » à « En_cours » s’il y a moins de 5 tâches
//«En_cours » dans la liste de tâches.
//Vous devez définir les structures de données nécessaires pour l’implémentation d’une liste.

//- Créer une liste de tâches vide
List *createList();

// demander une date a l'utilisateur
Date *askDate();

//fonction qui demande à l'utilisateur de saisir les champs d'une nouvelle tâche
Task *askTask();

Task *addTask(List*);

void sortList(List *,Task *);

void displayList(List * );

#endif //TP_TODOLIST_H