//Including LPUSH, RPUSH, LPOP, RPOP, LLEN, LRENGE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>  
      
typedef struct data {
    char* key;
    char* value;
    struct data* next;
    struct data* prev;
}Data;

char* readdata(Data* head, char* key) {
    Data* cur = head;
    while (cur) {
        if (strcmp(cur->key, key) == 0)
            return cur->value;
        else
            cur = cur->next;
    }
    if (cur == NULL) {
        printf("error\n");
        return NULL;
    }
}

void deletedata(Data **head, char* key) {
    Data* cur = *head;
    while (cur) {
        if (strcmp(cur->key, key) == 0)
            break;
        else
            cur = cur->next;
    }
    if (cur == NULL) {
        printf("error\n");
        return ;
    }
    else {
        if (cur == *head) {
            *head = cur->next;
            free(cur);
            cur = 0;
        }
        else
            cur->prev->next = cur->next;
            free(cur);
            cur = 0;
    }
}

void updatedata(Data** head, char* key, char* value) {
    Data* cur = *head;
    while (cur) {
        if (strcmp(cur->key, key) == 0)
            break;
        else
            cur = cur->next;
    }
    if (cur == NULL) {
        printf("error\n");
        return ;
    }
    else
        strcpy(cur->value, value);
}

void printdata(Data**head){
    Data* cur = *head;
    while(cur != NULL){
        printf("key:%s\n",cur -> key);
        printf("value:%s\n",cur -> value);
        cur = cur -> next;
        printf("\n");
    }
}

void createdata(Data **head, char* key, char* value) {
    Data* cur = *head;
    while (cur != NULL && cur->next != NULL) {
        cur = cur->next;
    }

    Data* newdata = malloc(sizeof(Data));
    if (newdata == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    newdata->key = malloc(strlen(key) + 1);
    if (newdata->key == NULL) {
        printf("Memory allocation failed\n");
        free(newdata);
        return;
    }

    newdata->value = malloc(strlen(value) + 1);
    if (newdata->value == NULL) {
        printf("Memory allocation failed\n");
        free(newdata->key);
        free(newdata);
        return;
    }

    newdata->next = NULL;
    newdata->prev = cur;

    strcpy(newdata->key, key);
    strcpy(newdata->value, value);

    if (*head == NULL) {
        *head = newdata;
    } else {
        cur->next = newdata;
    }
}

void LPUSH(Data** head,char* key,char* value){
    Data* cur = *head;

    Data* newdata = malloc(sizeof(Data));
    newdata -> next = cur;
    newdata -> prev = NULL;
    *head = newdata;

    strcpy(newdata->key, key);
    strcpy(newdata->value, value);
}

void RPUSH(Data** head,char* key,char* value){
    Data *cur = *head;
    while(cur != NULL && cur -> next != NULL){
        cur = cur -> next;
    }

    Data* newdata = malloc(sizeof(Data));
    newdata->next = NULL;
    newdata->prev = cur;
    cur -> next = newdata;

    strcpy(newdata->key, key);
    strcpy(newdata->value, value);
}

void LPOP(Data** head){
    Data* cur = *head;
    *head = cur -> next;
    free(cur);
    cur = 0;
}

void RPOP(Data** head){
    Data* cur = *head;
    while(cur != NULL && cur -> next != NULL){
        cur = cur -> next;
    }
    cur -> prev -> next = NULL;
    free(cur);
    cur = 0;
}

void LLEN(Data** head){
    Data* cur = *head;
    int len = 0;
    while(cur != NULL){
        cur = cur -> next;
        len++;
    }
    printf("The length is %d ",len);
    printf("\n");   
}

void LRENGE(Data** head,char* key,char* key1){
    Data* start = *head;
    Data* end = *head;
    while(start){
        if(strcmp(start -> key,key) == 0)
            break;
        else
            start = start -> next;
    }
    while(end){
        if(strcmp(end -> key,key1) == 0)
            break;
        else
            end = end -> next;
    }
    while(strcmp(start -> key,end -> key) != 0){
        printf("key: %s  value: %s\n",start -> key,start -> value);
        start = start -> next;
    }
    printf("key: %s  value: %s\n",end -> key,end -> value);
}

int main() {
            printf("1.create data\n");
            printf("2.read data\n");
            printf("3.update data\n");
            printf("4.delete data\n");
            printf("5.print all data\n");
            printf("6.LPUSH\n");
            printf("7.RPUSH\n");
            printf("8.LPOP\n");
            printf("9.RPOP\n");
            printf("10.LLEN\n");
            printf("11.LRENGE\n");
            printf("請選擇操作方式(輸入數字代號):");
            Data* head = NULL;
            int fn;
            char key[50];
            char key1[50];
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

                    case 6:
                        printf("please enter the key\n");
                        scanf("%s", key);
                        printf("please enter the value\n");
                        scanf("%s", value);
                        LPUSH(&head, key, value);
                        break;
                    
                    case 7:
                        printf("please enter the key\n");
                        scanf("%s", key);
                        printf("please enter the value\n");
                        scanf("%s", value);
                        RPUSH(&head, key, value);
                        break;

                    case 8:
                        LPOP(&head);
                        break;
                    
                    case 9:
                        RPOP(&head);
                        break;
                    
                    case 10:
                        LLEN(&head);
                        break;
                    
                    case 11:
                        printf("start key is: ");
                        scanf("%s",key);
                        printf("end key is: ");
                        scanf("%s",key1);
                        LRENGE(&head,key,key1);
                        break;
                    
                    default:
                        exit(0);

                }

                printf("請繼續輸入操作(按其他數字鍵離開)\n");
            }

    }
