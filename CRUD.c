#include <stdio.h>
#include <stdlib.h>

//Create
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

//Read
int readdata(Data* head, int key) {
    Data* cur = head;
    while (cur != NULL) {
        if (cur->key == key)
            return cur->value;
        cur = cur->next;
    }
}

//Update
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

//Delete
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

//Print
void printdata(Data** head) {
    Data* cur = *head;
    while (cur != NULL) {
        printf("key: %d, value: %d\n", cur->key, cur->value);
        cur = cur->next;
    }
}

//Basic UI
int main() {
            printf("1.create data\n");
            printf("2.read data\n");
            printf("3.update data\n");
            printf("4.delete data\n");
            printf("5.print all data\n");
            printf("Please choose the action you want to do in number:");
            Data* head = NULL;
            int fn;
            char key[50];
            char value[500];
            while (scanf("%d", &fn) != EOF) {
                
                switch (fn) 
                {
                    case 1:
                        printf("please enter the key\n");
                        scanf("%s", key);
                        printf("please enter the value\n");
                        scanf("%s", value);
                        createdata(&head, key, value);
                        break;

                    case 2:
                        char *output;
                        printf("please enter the key\n");
                        scanf("%s", key);
                        output = readdata(head, key);
                        printf("%s\n", output);
                        break;

                    case 3:
                        printf("please enter the key\n");
                        scanf("%s", key);
                        printf("please enter the value\n");
                        scanf("%s", value);
                        updatedata(&head, key, value);
                        break;

                    case 4:
                        printf("please enter the key\n");
                        scanf("%s", key);
                        deletedata(&head, key);
                        break;

                    case 5:
                        printdata(&head);
                        break;

                    default:
                        exit(0);

                }

                printf("Keep choosing other actions or input other number to leave\n");
            }

    }
