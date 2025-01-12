#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

typedef struct data {
 char* key;
 char* value;
 int valueInt;
 struct data* next;
 struct data* prev;
}Data;

typedef struct linklist{
 Data* head;
}List;

Data* mergesort(Data* head);
Data* merge(Data* left,Data* right);
void spilt(Data* head,Data** front,Data** back);

void printdata(Data**head){
 Data* cur = *head;
 while(cur != NULL){
 printf("key:%s\n",cur -> key);
 printf("value:%s\n",cur -> value);
 cur = cur -> next;
 printf("\n");
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
 cur -> next -> prev = cur -> prev;
 free(cur);
 cur = 0;
 }
}



void createdata(Data **head, char* key, char* value) {
 Data* cur = *head;
 while (cur != NULL) {
 if (cur == NULL || cur->next == NULL)
 break;
 else
 cur = cur->next;
 }
 if (*head == NULL) {
 *head = malloc(sizeof(Data)); 
 (*head)->key = malloc(sizeof(char)*(strlen(key)));
 (*head)->value = malloc(sizeof(char)*(strlen(value)));
 (*head)->next = NULL;
 (*head)->prev = NULL;
 strcpy((*head) -> key,key);
 strcpy((*head) -> value,value);
 
 }
 else {
 Data* newdata;
 newdata = malloc(sizeof(Data)); 
 newdata->key = malloc(sizeof(char)*strlen(key));
 newdata->value = malloc(sizeof(char)*strlen(value));
 newdata->next = NULL;
 cur->next = newdata;
 newdata->prev = cur;
 strcpy(newdata->key,key);
 strcpy(newdata->value,value);
 
 }


}

Data* mergesort(Data* head){

 if(head == NULL || head -> next == NULL){
 return head;
 }

 Data* front;
 Data* back;
 spilt(head,&front,&back);

 front = mergesort(front);
 back = mergesort(back);

 return merge(front,back);
 
}

void spilt(Data* head,Data** front,Data** back){
 Data* slow = head;
 Data* fast = head -> next;

 while(fast != NULL){
 fast = fast -> next;
 if(fast != NULL){
 slow = slow -> next;
 fast = fast -> next;
 }
 }

 *front = head;
 *back = slow -> next;

 if(back != NULL){
 (*back) -> prev = NULL;
 }
 slow -> next = NULL;
}

Data* merge(Data* left,Data* right){
 Data* result;
 if(left == NULL){
 return right;
 }
 if(right == NULL){
 return left;
 }

 if(atoi(left -> value) <= atoi(right -> value)){
 result = left;
 result -> next = merge(left -> next,right);
 if(result -> next != NULL){
 result -> next -> prev = result;
 }
 }
 else{
 result = right;
 result -> next = merge(left,right -> next);
 if(result -> next != NULL){
 result -> next -> prev = result;
 }
 }
 return result;
}

void ZADD(Data** head,char* key,char* value){
 createdata(head,key,value);
 (*head) = mergesort(*head);
}

void ZCARD(Data* head){
 int sum = 0;
 Data* cur = head;
 if(cur != NULL && strcmp(cur -> value,cur -> next -> value) <= 0){
 while(cur){
 cur = cur -> next;
 sum++;
 }
 printf("Length:%d\n",sum);
 }
 else{
 printf("The data hasn't been sorted!\n");
 }

}

void ZCOUNT(Data* head,char* min,char* max){
 Data* start = head;
 Data* end = head;
 int sum = 0;
 while(start != NULL && strcmp(start -> value,min) < 0){
 start = start -> next;
 }
 while(end != NULL && strcmp(end -> value,max) < 0){
 end = end -> next;
 }
 while(start != 0 && strcmp(start -> value,end -> value) != 0){
 start = start -> next;
 sum++;
 }
 printf("There are %d numbers in the range\n",sum);
}

void ZRANK(Data* head,char* key){
 Data* cur = head;
 Data* tmp = head;
 int total = 0;
 int temp = 0;
 int rank;
 while(tmp != NULL){
 tmp = tmp -> next;
 total++;
 }
 
 while(strcmp(cur -> key,key) != 0){
 cur = cur -> next;
 temp++;
 }
 rank = total - temp;
 printf("The rank of %s = %d\n",key,rank);
}

void ZRANGE(Data* head,int start,int end){
 Data* from = head;
 Data* to = head;
 for(int i = 0;i < start;i++){
 from = from -> next;
 };
 for(int i = 0;i < end;i++){
 to = to -> next;
 }
 printf("%s ",from -> key);
 while(strcmp(from -> key,to -> key) != 0){
 from = from -> next;
 printf("%s ",from -> key);
 }
 printf("\n");
}

void ZREMRANGEBYSCORE(Data* head,char* min,char* max){
 Data* cur = head;
 int count = 0;
 while(cur){
 if(strcmp(cur -> value,min) > 0 && strcmp(cur -> value,max) < 0){
 deletedata(&head,cur -> key);
 count++;
 }
 cur = cur -> next;
 }
 printf("%d datas has been deleted\n",count);
}

void ZREM(Data** head,char* input){

 char* token = strtok(input," ");

 while(token != NULL){
 deletedata(head,token);
 printf("removed:%s\n",token);
 token = strtok(NULL," ");
 }

}
 

void ZRANGEBYSCORE(Data* head,char* min,char* max){
 Data* start = head;
 Data* end = head;
 while(start != NULL && strcmp(start -> value,min) < 0){
 start = start -> next;
 }
 while(end != NULL && strcmp(end -> value,max) < 0){
 end = end -> next;
 }

 while(strcmp(start -> key,end -> key) != 0){
 printf("key:%s\n",start -> key);
 printf("value:%s\n",start -> value);
 printf("\n");
 start = start -> next;
 }
}


List* ZINTERSTORE(int num){
 List* lists = (List*)malloc(num*sizeof(List));
 for(int i = 0;i < num;i++){
 lists[i].head = NULL;
 int elements;
 char key[50];
 char value[50];
 printf("Enter the number of elements\n");
 scanf("%d",&elements);
 for(int j = 0;j < elements;j++){
 printf("Please input the SETs:\n");
 printf("key: ");
 scanf("%s",key);
 printf("value: ");
 scanf("%s",value);
 createdata(&lists[i].head,key,value);
 //printdata(&lists[i].head);
 }

 }

 Data* result = NULL;
 for (int i = 0; i < num; i++) {
 if (i == 0) {
 result = lists[i].head;
 } else {
 Data* currentSet = lists[i].head;
 Data* intersection = NULL;
 int sum;
 char plus[50];
 while (currentSet != NULL) {
 Data* temp = result;
 while (temp != NULL) {
 if (strcmp(currentSet->key, temp->key) == 0) {
 sum = atoi(currentSet -> value) + atoi(temp -> value);
 sprintf(plus,"%d",sum);
 createdata(&intersection, currentSet->key, plus);
 break;
 }
 temp = temp->next;
 }
 currentSet = currentSet->next;
 }

 result = intersection;
 }
 }

 printf("Intersection Result:\n");
 printdata(&result);

 return lists; 

}

List UNION(List* sets, int num, double* weights) {
 List result;
 result.head = NULL;

 for (int i = 0; i < num; i++) {
 Data* cur = sets[i].head;
 while (cur != NULL) {

 int intVal = atoi(cur -> value)*weights[i];
 Data* existmember = result.head;

 while(existmember != NULL){
 if(strcmp(existmember -> key,cur -> key) == 0){
 existmember -> valueInt += intVal;
 break;
 }
 existmember = existmember -> next;
 }

 if (existmember == NULL) {
 createdata(&result.head, cur->key, cur->value);
 Data* newMember = result.head;
 while (newMember->next != NULL) {
 newMember = newMember->next;
 }
 newMember->valueInt = intVal;
 }

 cur = cur->next;
 }

 }
 return result;
}

void printval(Data**head){
 Data* cur = *head;
 while(cur != NULL){
 printf("key:%s\n",cur -> key);
 printf("value:%d\n",cur -> valueInt);
 cur = cur -> next;
 printf("\n");
 }
}

List ZUNIONSTORE(int num) {
 List* lists = (List*)malloc(num * sizeof(List));
 for (int i = 0; i < num; i++) {
 lists[i].head = NULL;
 int elements;
 char key[50];
 char value[50];
 printf("Enter the number of elements for set:\n");
 scanf("%d", &elements);
 for (int j = 0; j < elements; j++) {
 printf("Please input the SETs:\n");
 printf("key: ");
 scanf("%s", key);
 printf("value: ");
 scanf("%s", value);
 createdata(&lists[i].head, key, value);
 //printdata(&lists[i].head);
 }
 }

 double weights[num];
 for (int i = 0; i < num; i++) {
 printf("Enter weight for set %d:\n", i + 1);
 scanf("%lf", &weights[i]);
 }

 List result = UNION(lists, num, weights);
 printval(&result.head);

 for (int i = 0; i < num; i++) {
 Data* current = lists[i].head;
 while (current != NULL) {
 Data* next = current->next;
 free(current->key);
 free(current->value);
 free(current);
 current = next;
 }
 }
 free(lists);

 return result;
}


int main() {
 printf("1.新增資料\n");
 printf("2.顯示所有資料\n");
 printf("3.sort\n");
 printf("4.ZADD\n");
 printf("5.ZCARD\n");
 printf("6.ZCOUNT\n");
 printf("7.ZRANK\n");
 printf("8.ZRANGE\n");
 printf("9.ZREMRANGEBYSCORE\n");
 printf("10.ZREM\n");
 printf("11.ZRANGEBYSCORE\n");
 printf("12.ZINTERSTORE\n");
 printf("13.ZUNIONSTORE\n");
 printf("請選擇操作方式(輸入數字代號):");
 Data* head = NULL;
 int fn;
 char key[50];
 char value[500];
 char min[50];
 char max[50];
 char input[100];
 int start,end;
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
 printdata(&head);
 break;

 case 3:
 head = mergesort(head);
 printdata(&head);
 break;
 case 4:
 printf("please enter the key\n");
 scanf("%s", key);
 printf("please enter the value\n");
 scanf("%s", value);
 ZADD(&head, key, value);
 printdata(&head);
 break;
 case 5:
 ZCARD(head);
 break;
 case 6:
 printf("please enter the min\n");
 scanf("%s", min);
 printf("please enter the max\n");
 scanf("%s", max);
 ZCOUNT(head,min,max);
 break;
 case 7:
 printf("please enter the key\n");
 scanf("%s",key);
 ZRANK(head,key);
 break;
 case 8:
 printf("start: ");
 scanf("%d",&start);
 printf("end: ");
 scanf("%d",&end);
 ZRANGE(head,start,end);
 break;
 case 9:
 printf("please enter the max\n");
 scanf("%s",max);
 printf("please enter the min\n");
 scanf("%s",min);
 ZREMRANGEBYSCORE(head,max,min);
 break;
 case 10:
 printf("enter key(s) to remove\n");
 scanf(" %[^\n]",input);
 ZREM(&head,input);
 break;
 case 11:
 printf("please enter the min\n");
 scanf("%s",max);
 printf("please enter the max\n");
 scanf("%s",min);
 ZRANGEBYSCORE(head,max,min);
 break;
 case 12:
 printf("Number of sets\n");
 scanf("%d",&start);
 ZINTERSTORE(start);
 break;
 case 13:
 printf("Number of sets\n");
 scanf("%d",&start);
 ZUNIONSTORE(start);
 break;
 default:
 exit(0);
 }

 printf("請繼續輸入操作(按其他數字鍵離開)\n");
 }

 }
