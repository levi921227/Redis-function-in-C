#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 
#include <pthread.h>

typedef struct data{
    char* key;
    char* value;
    time_t expire;
    struct data* next;
    struct data* prev;
}Data;

typedef struct{
    int size;
    Data** buckets;
    time_t expireTime;
}hashtable;

int isCheck = 0;
pthread_t checkTimethreadId;

int hash(const char* str,int size){
    int hash = 1227;
    int x;
    while((x = *str++) != '\0'){
        hash = ((hash << 3) + hash) + x;
    }
    return hash%100;
}

void initHash(hashtable* map,int size){
    map -> size = size;
    map -> buckets = (Data**)calloc(size,sizeof(Data*));
}

void HSET(hashtable* map,const char* key,const char* value){
    int index = hash(key,map -> size);
    Data* cur = map -> buckets[index];
    while(cur){
        if(strcmp(key,cur -> key) ==0){
            free(cur -> value);
            cur -> value = strdup(value);
            return;
        }
        cur = cur -> next;
    }

    Data* newdata = (Data*)malloc(sizeof(Data));
    newdata -> key = strdup(key);
    newdata -> value = strdup(value);
    newdata -> next = map -> buckets[index];
    map -> buckets[index] = newdata;

}

const char* HGET(const hashtable* map,const char* key){
    int index = hash(key,map -> size);
    Data* cur = map -> buckets[index];
    while(cur){
        if(strcmp(key,cur -> key) == 0){
            return cur -> value;
        }
        cur = cur -> next;
    }
    return NULL;
}

void HDEL(const hashtable* map,const char* key){
    int index = hash(key,map -> size);
    Data* cur = map -> buckets[index];
    Data* prev = NULL;

    while(cur){
        if(strcmp(cur -> key,key) == 0){
            if(prev == NULL){
                map -> buckets[index] = cur -> next;
            }
            else{
                prev -> next = cur -> next;
            }
            printf("The key has been deleted\n");
            free(cur -> key);
            free(cur -> value);
            free(cur);
            cur = NULL;
            return;
        }
        prev = cur;
        cur = cur -> next;
    }
}

void* checkTimethread(void*arg){
    hashtable* map = (hashtable*)arg;

    while(isCheck){
        for(int i = 0;i < map -> size;i++){
            Data* cur = map -> buckets[i];
            Data* prev = NULL;

            while(cur){
                if(cur -> expire > 0 && cur -> expire <= time(NULL)){
                    printf("Key has expired\n");
                    HDEL(map,cur -> key);
                }
            }
        }
        usleep(1000000);
    }
    pthread_exit(NULL);
}    

void expire(hashtable* map,const char* key,time_t second){
    int index = hash(key,map -> size);
    Data* cur = map -> buckets[index];
    while(cur){
        if(strcmp(cur -> key,key) == 0){
            cur -> expire = second;
            printf("expire time:%ld\n",(cur -> expire) - time(NULL));
            map -> expireTime = time(NULL) + second;
            if(!isCheck){
                isCheck = 1;
                pthread_create(&checkTimethreadId,NULL,checkTimethread,(void*)map);
            }
            return;
        }
        cur = cur -> next;
    }

}




int main(){
    hashtable map;
    initHash(&map,100);
    
    printf("1.HSET\n");
    printf("2.HGET\n");
    printf("3.HDEL\n");
    printf("4.expire\n");
    printf("Please enter the number to choose the function:\n");
    int fn;
    char key[50];
    char value[50];
    time_t second = 0;
    while(scanf("%d",&fn) != EOF){
        switch(fn)
        {
            case 1:
                printf("Please enter the key:\n");
                scanf("%s",key);
                printf("Please enter the value:\n");
                scanf("%s",value);
                HSET(&map,key,value);
                break;
            case 2:
                printf("Please enter the key:\n");
                scanf("%s",key);
                const char* val = HGET(&map,key);
                printf("%s\n",val);
                break;
            case 3:
                printf("Please enter the key:\n");
                scanf("%s",key);
                HDEL(&map,key);
                break;
            case 4:
                printf("Please enter the key\n");
                scanf("%s",key);
                printf("Please enter the time(S)\n");
                scanf("%ld",&second);
                expire(&map,key,time(NULL) + second);
                break;
            default:
                isCheck = 0;
                pthread_join(checkTimethreadId,NULL);
                exit(0); 
        }
        printf("Please choose the function\n");
    }

}
