#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#define SIZE 100
#define STACK_SIZE 100
#define QUEUE_SIZE 100

// Node veri yapýsý
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// Stack veri yapýsý
typedef struct {
    Node* top;
    int cnt;
} stack;

// Queue veri yapýsý
typedef struct {
    Node* front;
    Node* rear;
    int cnt;
} queue;

void initialize_stack(stack* stk) {
    stk->top = NULL;
    stk->cnt=0;
}
void initialize_queue(queue* q) {
	q->cnt=0;
    q->front = q->rear = NULL;
}
typedef enum{true,false}boolean;
boolean isEmpty_stack(stack* stk) {
    return (stk->cnt==0);
}

boolean isFull_stack(stack* stk) {
    return (stk->cnt == STACK_SIZE);
}

void push(stack* stk, int c) {
	if(!isFull_stack(stk)){
		struct Node* temp= (Node*)malloc(sizeof(Node));
		temp->data=c;
		temp->next= stk->top;
		stk->top=temp;
		stk->cnt++;
	}
	else
		printf("Stack dolu\n");
    
}	

int pop(stack* stk) {
    if (!isEmpty_stack(stk)) {
        struct Node *temp = stk->top;
        stk->top = stk->top->next;
        int x = (int)temp->data; // Karakter verisini int'e dönüþtürüyoruz.
        free(temp);
        stk->cnt--;
        return x;
    }
    return -1; // Stack boþsa -1 gibi bir hata kodu döndürebilirsiniz.
}


int isEmpty_queue(queue* q) {
    return (q->cnt == 0);
}

int isFull_queue(queue *q){
	return (q->cnt == QUEUE_SIZE);
}

void enqueue(queue* q, int x) {
	
	if(!isFull_queue(q)){
		struct Node* temp= (Node*)malloc(sizeof(Node));
		temp->next=NULL;
		temp->data=x;
		
		if(isEmpty_queue(q))
			q->front=q->rear=temp;
		else
			q->rear=q->rear->next=temp;	
		q->cnt++;	
	}
    
}

int dequeue(queue* q) {
    if(!isEmpty_queue(q)){
		struct Node* temp= q->front;
		int x= temp->data;
		q->front=temp->next;
		free(temp);
		q->cnt--;
		return x;	
	}
}
int main() {
	
	char ifade[SIZE];
	queue q;
	stack s;
	int i=0, mismatches=0;
	initialize_stack(&s);
	initialize_queue(&q);
	
	printf("bir ifade giriniz: ");
	gets(ifade);
	
	for(i=0; i!=strlen(ifade); i++){
		if(isalpha(ifade[i])){
			enqueue(&q,tolower(ifade[i]));
			push(&s,tolower(ifade[i]));
		}
	}
	while(!isEmpty_queue(&q)){
		if(pop(&s)!=dequeue(&q)){
			mismatches=1;
			break;
		}
	}
	if(mismatches==1)
		printf("ifade palindrom degil..");
	else
		printf("ifade palindrom..");	
	
	getch();
	
	return 0;
}

