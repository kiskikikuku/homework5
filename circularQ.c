#include<stdio.h>
#include<stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
}QueueType;

QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element *item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void){

    QueueType *cQ = createQueue();
    element data;
    char command;

    do{

        printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

        printf("Command : ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'i' : case 'I':
            data = getElement();
            enQueue(cQ, data);
            break;

        case 'd' : case 'D':
            deQueue(cQ, &data);
            break;
        
        case 'p' : case 'P':
            printQ(cQ);
            break;
        
        case 'b' : case 'B':
            debugQ(cQ);
            break;

        case 'q' : case 'Q':
            freeQueue(cQ);
            break;

        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command !='q' && command != 'Q');

    return 1;
}

QueueType *createQueue(){

    QueueType *cQ;
    cQ = (QueueType*)malloc(sizeof(QueueType)); //큐에 공간 할당
    cQ->front = 0;
    cQ->rear = 0;

    return cQ;
}

int freeQueue(QueueType *cQ){

    if(cQ == NULL){return 1;}

    free(cQ);
    return 1;    
} // 큐에 할당한 공간 해제

int isEmpty(QueueType *cQ){
    if(cQ->front == cQ->rear) return 1; // 비어있는경우 1을 반환
    else return 0; // 비어있지 않은경우 0 반환
}

int isFull(QueueType *cQ){

    if(cQ->front == (cQ->rear+1)%MAX_QUEUE_SIZE){
        printf("Queue is FUll!!!\n");
        return 1;
    }
    else return 0;

}

void enQueue(QueueType *cQ, element item){
    
    
    if(isFull(cQ)==1) {return;}
    else {
        cQ->rear = (cQ->rear+1)%MAX_QUEUE_SIZE;
        cQ->queue[cQ->rear] = item;
    }

    return;
}

void deQueue(QueueType *cQ, element *item){
    if(isEmpty(cQ)){
        printf("Queue is Empty!!!\n");
    }

    else{
        cQ->front = (cQ->front+1)%MAX_QUEUE_SIZE;
        *item = cQ->queue[cQ->front];    
    }

    return;
}

void printQ(QueueType *cQ){
    int i, first, last;

    first = (cQ->front+1)%MAX_QUEUE_SIZE;
    last = (cQ->rear+1)%MAX_QUEUE_SIZE;

    printf("Circular Queue : [");
    i=first;
    while(i != last){
        printf("%3c", cQ->queue[i]);
        i = (i+1)%MAX_QUEUE_SIZE;
    }
    printf(" ]\n");

}

void debugQ(QueueType *cQ){
    printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


element getElement(){
    element item;
    printf("Input element = ");
    scanf(" %c", &item);
    return item;
} //element(문자) 1개를 받아서 반환

