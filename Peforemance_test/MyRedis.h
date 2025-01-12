#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"basic_cmd.h"
#define len 100000

int main() {
    Data* head = NULL;

    clock_t start, finish;
    clock_t a,b;

    double times;
    double readtimes;
    srand(time(NULL));

    int* tempkey = malloc(len * sizeof(int));
    int* tempvalue = malloc(len * sizeof(int));

    //create new data
    start = clock();
    for (int i = 0; i < len; i++) {
        tempkey[i] = i;
        tempvalue[i] = rand();
        createdata(&head, tempkey[i], tempvalue[i]);
    }
    finish = clock();

    //read data
    a = clock();
    for(int i = 0; i < len; i++){
        readdata(head,tempkey[i]);
    }
    b = clock();

    //calculate time
    times = (double)((finish - start) / (double)CLOCKS_PER_SEC);
    double avg = times/len;
    printf("create 100000 pairs total time: %lf seconds\n",times);
    printf("create average: %lf seconds\n", avg);
    readtimes = (double)((b-a)/(double)CLOCKS_PER_SEC);
    double avgRead = readtimes/len;
    printf("read 100000 keys total time: %lf seconds\n",readtimes);
    printf("read average: %lf seconds\n",avgRead);
  

    // Free and calculate memory
    int space = 0; 
    Data* cur = head;
    while (cur != NULL) {
        space++;
        Data* temp = cur;
        cur = cur->next;
        free(temp);
    }
    int usespace = space*(sizeof(Data));
    printf("memory used:%d bytes\n",usespace);
    
    free(tempkey);
    free(tempvalue);

    return 0;
}
