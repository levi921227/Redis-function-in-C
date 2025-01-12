#include <hiredis/hiredis.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define len 100000

int main(){

    //connect redis
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
    if (c) {
        printf("Error: %s\n", c->errstr);
        // handle error
    } else {
        printf("Can't allocate redis context\n");
        }
    }

    redisReply *reply;

    clock_t start, finish;
    clock_t a,b;
    double times;
    double readtimes;
    srand(time(NULL));

    int* tempkey = malloc(len * sizeof(int));
    int* tempvalue = malloc(len * sizeof(int));

    // use redis to create pairs
    start = clock();
    for (int i = 0; i < len; i++) {
        tempkey[i] = i;
        tempvalue[i] = rand();
        reply = redisCommand(c,"SET %d %d",tempkey[i],tempvalue[i]);
        if (reply == NULL) {
            printf("Error setting key-value pair: %s\n", c->errstr);
            redisFree(c);
            return 1;
        }
        freeReplyObject(reply);
           
    }
    finish = clock();

    //use redis to read value
    a = clock();
    for(int i = 0; i < len; i++){
        reply = redisCommand(c,"GET %d",tempkey[i]);
        if (reply == NULL) {
            printf("Error setting key-value pair: %s\n", c->errstr);
            redisFree(c);
            return 1;
        }
        freeReplyObject(reply);
    }
    b = clock();

    //calculate times
    times = ((finish - start) / (double)CLOCKS_PER_SEC);
    double avg = times/len;
    readtimes = ((b-a)/(double)CLOCKS_PER_SEC);
    double avgRead = readtimes/len;
    printf("create 100000 pairs total time: %lf seconds\n",times);
    printf("create average: %lf seconds\n",avg);
    printf("read 100000 keys total time: %lf seconds\n",readtimes);
    printf("read average: %lf seconds\n",avgRead);

    //calculate
    reply = redisCommand(c, "INFO MEMORY");
    if (reply == NULL) {
        printf("error\n");
        redisFree(c);
        return 1;
    }
    if (reply->str != NULL) {
        printf("Memory Usage Info: \n%s\n", reply->str);
    } else {
        printf("No memory info.\n");
    }


    redisFree(c);
    return 0;
}
