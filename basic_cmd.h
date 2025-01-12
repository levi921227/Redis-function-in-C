#ifndef BASIC_CMD_H
#define BASIC_CMD_H

typedef struct data {
    int key;
    int value;
    struct data* next;
    struct data* prev;
} Data;

void createdata(Data **head, int key, int value);
int readdata(Data* head, int key);
void updatedata(Data** head, int key, int value);
void deletedata(Data **head, int key);
void printdata(Data** head);

#endif
