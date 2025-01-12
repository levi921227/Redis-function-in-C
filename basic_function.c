#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct data {
    char* key;
    char* value;
    struct data* next;
    struct data* prev;
} Data;

typedef enum {
    ADD = 1,
    READ,
    UPDATE,
    DELETE,
    DISPLAY,
    EXIT
} MenuOption;

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

void deletedata(Data** head, char* key) {
    Data* cur = *head;
    while (cur) {
        if (strcmp(cur->key, key) == 0)
            break;
        else
            cur = cur->next;
    }
    if (cur == NULL) {
        printf("error\n");
        return;
    } else {
        if (cur == *head) {
            *head = cur->next;
            if (*head) (*head)->prev = NULL;
            free(cur);
            cur = NULL;
        } else {
            cur->prev->next = cur->next;
            if (cur->next) cur->next->prev = cur->prev;
            free(cur);
            cur = NULL;
        }
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
        return;
    } else {
        free(cur->value);
        cur->value = malloc(strlen(value) + 1);
        strcpy(cur->value, value);
    }
}

void printdata(Data** head) {
    Data* cur = *head;
    while (cur != NULL) {
        printf("key: %s\n", cur->key);
        printf("value: %s\n", cur->value);
        cur = cur->next;
        printf("\n");
    }
}

void createdata(Data** head, char* key, char* value) {
    Data* cur = *head;
    while (cur != NULL && cur->next != NULL) {
        cur = cur->next;
    }
    if (*head == NULL) {
        *head = malloc(sizeof(Data));
        (*head)->key = malloc(strlen(key) + 1);
        (*head)->value = malloc(strlen(value) + 1);
        (*head)->next = NULL;
        (*head)->prev = NULL;
        strcpy((*head)->key, key);
        strcpy((*head)->value, value);
    } else {
        Data* newdata = malloc(sizeof(Data));
        newdata->key = malloc(strlen(key) + 1);
        newdata->value = malloc(strlen(value) + 1);
        newdata->next = NULL;
        newdata->prev = cur;
        cur->next = newdata;
        strcpy(newdata->key, key);
        strcpy(newdata->value, value);
    }
}

int main() {
    printf("1. 新增資料\n");
    printf("2. 讀取資料\n");
    printf("3. 修改資料\n");
    printf("4. 刪除資料\n");
    printf("5. 顯示所有資料\n");
    printf("6. 離開程式\n");

    Data* head = NULL;
    int fn;
    char key[50];
    char value[500];

    while (1) {
        printf("請選擇操作方式 (輸入數字代號): ");
        if (scanf("%d", &fn) == EOF) break;

        switch (fn) {
            case ADD:
                printf("請輸入鍵值 (key): ");
                scanf("%s", key);
                printf("請輸入內容 (value): ");
                scanf("%s", value);
                createdata(&head, key, value);
                break;

            case READ: {
                char* output;
                printf("請輸入鍵值 (key): ");
                scanf("%s", key);
                output = readdata(head, key);
                if (output != NULL) {
                    printf("內容: %s\n", output);
                }
                break;
            }

            case UPDATE:
                printf("請輸入鍵值 (key): ");
                scanf("%s", key);
                printf("請輸入新內容 (value): ");
                scanf("%s", value);
                updatedata(&head, key, value);
                break;

            case DELETE:
                printf("請輸入鍵值 (key): ");
                scanf("%s", key);
                deletedata(&head, key);
                break;

            case DISPLAY:
                printdata(&head);
                break;

            case EXIT:
                printf("離開程式\n");
                exit(0);

            default:
                printf("無效的選項，請重新輸入！\n");
        }

        printf("請繼續輸入操作 (按其他數字鍵離開):\n");
    }

    return 0;
}
