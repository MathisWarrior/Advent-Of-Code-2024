#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Cellule* creerCellule(int val) {
    Cellule* newCell = (Cellule*)malloc(sizeof(Cellule));
    if (!newCell) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newCell->val = val;
    newCell->next = NULL;
    return newCell;
}

void insererFin(Liste* head, int val) {
    Cellule* newCell = creerCellule(val);
    if (*head == NULL) {
        *head = newCell;
        return;
    }
    Cellule* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newCell;
}

void supprimerCellule(Liste* head, int val) {
    Liste temp = *head;
    Liste prev = NULL;

    if (temp != NULL && temp->val == val) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->val != val) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Node with value %d not found\n", val);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void afficherListe(Liste head) {
    Liste temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->val);
        temp = temp->next;
    }
    printf("NULL\n");
}

void libererListe(Liste head) {
    Liste temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Liste copierListe(Liste head) {
    Liste newHead = NULL;
    Liste tail = NULL;

    while (head != NULL) {
        Liste newNode = (Liste)malloc(sizeof(Cellule));
        newNode->val = head->val;
        newNode->next = NULL;

        if (newHead == NULL) {
            newHead = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        head = head->next;
    }

    return newHead;
}

size_t nbElements(Liste head) {
    size_t count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

Liste supprimerCelluleAIndex(Liste head, int index) {
    if (index < 0) {
        printf("Index must be positive\n");
        return head;
    }

    if (index == 0) {
        Liste temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Liste temp = head;
    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Index out of bounds\n");
        return head;
    }

    Liste next = temp->next->next;
    free(temp->next);
    temp->next = next;

    return head;
}