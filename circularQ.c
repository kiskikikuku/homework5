#include<stdio.h>
#include<stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element; // element 타입 정의 (큐에 들어갈 문자 1개)
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
}QueueType; // 큐 타입 정의(element 배열과 front, rear 인덱스)

QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element *item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement(); 
//함수 선언

int main(void){
    printf("[----- [Park Taehyun] [2018068040] -----]\n");
    QueueType *cQ = createQueue(); // 큐 생성
    element data; 
    char command; // 입력문자 저장할 변수

    do{

        printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

        printf("Command : ");
        scanf(" %c", &command); //명령 입력받기

        switch (command)
        {
        case 'i' : case 'I': //원소 삽입
            data = getElement();
            enQueue(cQ, data);
            break; 

        case 'd' : case 'D': //원소 제거
            deQueue(cQ, &data);
            break;
        
        case 'p' : case 'P': //큐 출력
            printQ(cQ);
            break;
        
        case 'b' : case 'B': //디버그
            debugQ(cQ);
            break;

        case 'q' : case 'Q': //종료
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
}//큐 생성함수, 큐를 생성하여 공간할당 및 인덱스 초기화를 진행하여 생성한 큐의 주소를 반환한다.

int freeQueue(QueueType *cQ){

    if(cQ == NULL){return 1;}

    free(cQ);
    return 1;    
} // 큐에 할당한 공간 해제

int isEmpty(QueueType *cQ){
    if(cQ->front == cQ->rear) return 1; // 비어있는경우 1을 반환
    else return 0; // 비어있지 않은경우 0 반환
}//큐가 비어있는지 체크

int isFull(QueueType *cQ){

    if(cQ->front == (cQ->rear+1)%MAX_QUEUE_SIZE){
        printf("Queue is FUll!!!\n");
        return 1; 
    } //큐가 꽉 찬 경우 1을 반환
    else return 0; // 꽉 차지 않으면 0을 반환

} //큐가 꽉 차있는지 체크

void enQueue(QueueType *cQ, element item){
    
    
    if(isFull(cQ)==1) {return;} //큐가 꽉 찼는지 확인
    else {
        cQ->rear = (cQ->rear+1)%MAX_QUEUE_SIZE; // rear 한칸 이동
        cQ->queue[cQ->rear] = item; // 이동한 위치에 원소 삽입
    }

    return;
} //원소 삽입

void deQueue(QueueType *cQ, element *item){
    if(isEmpty(cQ)){
        printf("Queue is Empty!!!\n");
        return;
    }   // 큐가 비어있는지 확인, 비어있으면 함수 종료

    else{
        cQ->front = (cQ->front+1)%MAX_QUEUE_SIZE;
        *item = cQ->queue[cQ->front];
        return;    
    } // front를 한칸 이동(가장 먼저 삽입한 원소가 있는 위치로), 해당 위치 원소를 item이 가리키는 곳에 담아줌

} //원소 제거

void printQ(QueueType *cQ){
    int i, first, last;

    first = (cQ->front+1)%MAX_QUEUE_SIZE; // 첫원소 위치 first: 프론트 한칸 앞
    last = (cQ->rear+1)%MAX_QUEUE_SIZE; // last : 마지막 원소의 다음 위치

    printf("Circular Queue : [");
    i=first;
    while(i != last){
        printf("%3c", cQ->queue[i]); // 원소 출력
        i = (i+1)%MAX_QUEUE_SIZE; // 한칸이동
    }
    printf(" ]\n");

} // 큐 출력

void debugQ(QueueType *cQ){
    printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		} //front인 경우, front로 출력
		printf("  [%d] = %c\n", i, cQ->queue[i]); // 아닌 경우, 원소 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // 현재 front rear의 위치 출력
} // 큐 검사


element getElement(){
    element item;
    printf("Input element = ");
    scanf(" %c", &item);
    return item;
} //element(문자) 1개를 받아서 반환

