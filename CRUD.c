#include <stdio.h>
#include <stdlib.h>
#include"hw1.h"


void createdata(Data **head, int key, int value) {
    Data* cur = *head;
    while (cur != NULL && cur->next != NULL) {
        cur = cur->next;
    }

    Data* newdata = malloc(sizeof(Data));

    newdata->key = key;
    newdata->value = value;
    newdata->next = NULL;
    newdata->prev = cur;

    if (*head == NULL) {
        *head = newdata;
    } else {
        cur->next = newdata;
    }
}

int readdata(Data* head, int key) {
    Data* cur = head;
    while (cur != NULL) {
        if (cur->key == key)
            return cur->value;
        cur = cur->next;
    }
}

void updatedata(Data** head, int key, int value) {
    Data* cur = *head;
    while (cur != NULL) {
        if (cur->key == key) {
            cur->value = value;
            return;
        }
        cur = cur->next;
    }

    printf("Key not found: %d\n", key);
}

void deletedata(Data **head, int key) {
    Data* cur = *head;
    while (cur != NULL) {
        if (cur->key == key)
            break;
        cur = cur->next;
    }
    if (cur == NULL) {
        printf("Key not found: %d\n", key);
        return;
    }
    else {
        if (cur == *head) {
            *head = cur->next;
            free(cur);
        }
        else {
            cur->prev->next = cur->next;
            free(cur);
        }
    }
}

void printdata(Data** head) {
    Data* cur = *head;
    while (cur != NULL) {
        printf("key: %d, value: %d\n", cur->key, cur->value);
        cur = cur->next;
    }
}
