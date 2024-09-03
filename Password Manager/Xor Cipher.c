#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Data structure definition
typedef struct Data {
    char* key;
    char* value;
    struct Data* next;
    struct Data* prev;
} Data;

// XOR encryption/decryption function
void xor_encrypt_decrypt(char* str, char key) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] ^= key;
    }
}

// Create new data
void createdata(Data **head, const char* key, const char* value) {
    Data* cur = *head;
    while (cur != NULL && cur->next != NULL) {
        cur = cur->next;
    }

    Data* newdata = malloc(sizeof(Data));
    newdata->key = malloc(strlen(key) + 1);
    strcpy(newdata->key, key);
    newdata->value = malloc(strlen(value) + 1);
    strcpy(newdata->value, value);
    xor_encrypt_decrypt(newdata->value, key[0]);  // Encrypt the value

    newdata->next = NULL;
    newdata->prev = cur;

    if (*head == NULL) {
        *head = newdata;
    } else {
        cur->next = newdata;
    }
}

// Create new data without encryption (for loading from file)
void create_File_data(Data **head, const char* key, const char* value) {
    Data* cur = *head;
    while (cur != NULL && cur->next != NULL) {
        cur = cur->next;
    }

    Data* newdata = malloc(sizeof(Data));
    newdata->key = malloc(strlen(key) + 1);
    strcpy(newdata->key, key);
    newdata->value = malloc(strlen(value) + 1);
    strcpy(newdata->value, value);
    newdata->next = NULL;
    newdata->prev = cur;

    if (*head == NULL) {
        *head = newdata;
    } else {
        cur->next = newdata;
    }
}

// Read data
char* readdata(Data* head, const char* key) {
    Data* cur = head;
    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0) {
            xor_encrypt_decrypt(cur->value, key[0]);  // Decrypt the value
            return cur->value;
        }
        cur = cur->next;
    }
    return NULL;
}

// Update data
void updatedata(Data** head, const char* key, const char* value) {
    Data* cur = *head;
    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0) {
            free(cur->value);
            cur->value = malloc(strlen(value) + 1);
            strcpy(cur->value, value);
            xor_encrypt_decrypt(cur->value, key[0]);  // Encrypt the value
            return;
        }
        cur = cur->next;
    }
    printf("Key not found: %s\n", key);
}

// Delete data
void deletedata(Data **head, const char* key) {
    Data* cur = *head;
    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0)
            break;
        cur = cur->next;
    }
    if (cur == NULL) {
        printf("Key not found: %s\n", key);
        return;
    } else {
        if (cur == *head) {
            *head = cur->next;
        } else {
            cur->prev->next = cur->next;
            if (cur->next != NULL) {
                cur->next->prev = cur->prev;
            }
        }
        free(cur->key);
        free(cur->value);
        free(cur);
    }
}

// Print all data
void printdata(Data* head) {
    Data* cur = head;
    while (cur != NULL) {
        printf("key: %s, value (encrypted): %s\n", cur->key, cur->value);
        cur = cur->next;
    }
}

// Save data to file
void save_to_file(Data* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    Data* cur = head;
    while (cur != NULL) {
        int key_len = strlen(cur->key) + 1;
        fwrite(&key_len, sizeof(int), 1, file);
        fwrite(cur->key, sizeof(char), key_len, file);

        int value_len = strlen(cur->value) + 1;
        fwrite(&value_len, sizeof(int), 1, file);
        fwrite(cur->value, sizeof(char), value_len, file);

        cur = cur->next;
    }

    fclose(file);
}

// Load data from file
void load_from_file(Data** head, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return;
    }

    int key_len, value_len;
    char key[500], value[500];

    while (fread(&key_len, sizeof(int), 1, file)) {
        fread(key, sizeof(char), key_len, file);
        fread(&value_len, sizeof(int), 1, file);
        fread(value, sizeof(char), value_len, file);
        create_File_data(head, key, value);  // Use function without encryption
    }
    
    fclose(file);
}

// Basic UI
int main() {
    const char* filename = "data.bin";

    Data* head = NULL;
    load_from_file(&head, filename);

    int fn;
    char key[500], value[500];

    while (1) {
        printf("\n1. Create data\n");
        printf("2. Read data\n");
        printf("3. Update data\n");
        printf("4. Delete data\n");
        printf("5. Print all data\n");
        printf("Please choose an option (enter the number code):\n");
        
        if (scanf("%d", &fn) != 1) { // Check for input errors
            printf("Invalid input, exiting.\n");
            break;
        }

        switch (fn) {
            case 1:
                printf("please enter the key (account):\n");
                scanf("%s", key);
                printf("please enter the value (password):\n");
                scanf("%s", value);
                createdata(&head, key, value);
                break;

            case 2:
                printf("please enter the key (account):\n");
                scanf("%s", key);
                char* output = readdata(head, key);
                if (output) {
                    printf("Decrypted value (password): %s\n", output);
                    xor_encrypt_decrypt(output, key[0]);  // Re-encrypt the value
                } else {
                    printf("Key not found: %s\n", key);
                }
                break;

            case 3:
                printf("please enter the key (account):\n");
                scanf("%s", key);
                printf("please enter the value (password):\n");
                scanf("%s", value);
                updatedata(&head, key, value);
                break;

            case 4:
                printf("please enter the key (account):\n");
                scanf("%s", key);
                deletedata(&head, key);
                break;

            case 5:
                printdata(head);
                break;

            default:
                printf("Exiting program...\n");
                save_to_file(head, filename);
                exit(0);
        }
        printf("Please continue with your operation (press another number key to exit)\n");
    }

    save_to_file(head, filename);
    return 0;
}

