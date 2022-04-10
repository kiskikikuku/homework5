#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20
typedef enum{
    lparen = 0,
    rparen = 9,
    times = 7,
    divide = 6,
    plus = 5,
    minus = 4,
    operand = 1
} precedence; // stack 내의 우선순위, 0이 가장 낮은 우선순위

char infixExp[MAX_EXPRESSION_SIZE]; // infix 표현이 저장되는 배열
char postfixExp[MAX_EXPRESSION_SIZE]; // postfix로 변경하여 저장할 배열
char postfixStack[MAX_STACK_SIZE]; // postfix로 변환을 위한 스택
int evalStack[MAX_STACK_SIZE]; // 계산용 스택

int postfixStackTop = -1; // postfix 스택의 top
int evalStackTop = -1; // 계산용 스택의 top
int evalresult = 0; //계산 결과 저장

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main(){

    char command; //명령입력 문자

    do
    {
        printf("----------------------------------------------------------------\n");
      printf("               Infix to Postfix, then Evaluation               \n");
      printf("----------------------------------------------------------------\n");
      printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
      printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); // 명령 입력받기

        switch (command)
        {
        case 'i': case 'I':
            getInfix();
            break;
        case 'p': case'P':
            toPostfix();
            break;
        case 'e': case'E':
            evaluation();
            break;
        case 'd': case'D':
            debug();
            break;
        case 'r': case'R':
            reset();
            break;
        case 'q': case 'Q':
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
         break;
        }
    } while (command != 'q' && command != 'Q');
    
    return 1;
}

void postfixPush(char x){
    postfixStack[++postfixStackTop] = x; // top을 하나 증가시키고 x삽입
} //postfix 스택에 원소 1개 push

char postfixPop(){
    char x;
    if(postfixStackTop==-1) //비어있는 스택의 경우, 호출을 종료한다
        return '\0';
    else{
        x = postfixStack[postfixStackTop--];
    } // x에 반환할 문자를 담고 top을 하나 감소시킨다

    return x; //pop하는 문자 반환
} //postfix 스택에서 원소 1개 pop

void evalPush(int x){
    evalStack[++evalStackTop] = x; // top을 하나 증가시키고 x삽입
} // 계산용 스택에 정수 push

int evalPop(){
    int x;
    if (evalStackTop == -1)
        return -1; //비어있는 스택의 경우, 호출을 종료한다
    else{
        x = evalStack[evalStackTop--];
    } // x에 반환할 정수를 담고 top을 하나 감소시킨다
    
    return x; //pop하는 숫자 반환
} //계산용 스택에서 원소 1개 pop

void getInfix(){

    printf("Type the expression >>> ");
    scanf("%s", infixExp);
} //infix표기 식을 문자열로 입력받는다

precedence getToken(char symbol){
    switch (symbol)
    {
    case '(' : return lparen;
    case ')' : return rparen;
    case '+' : return plus;
    case '-' : return minus;
    case '*' : return times;
    case '/' : return divide;
    default: return operand;
    }
} // 입력받은 문자를 precedence로 변환하여줌

precedence getPriority(char x){
    return getToken(x);
} 

void charCat(char* c){
    if(postfixExp == '\0')
        strcpy(postfixExp, c);
    else
        strcat(postfixExp, c);
}

void toPostfix(){
    
    char *exp = infixExp;
    char x;

    while (*exp != '\0')
    {
        if (getPriority(*exp) == operand) // 피연산자(숫자)의 경우
        {
            x = *exp;   //하나 저장해서
            charCat(&x); //후위표기 Exp에 삽입한다.
        }
        else if (getPriority(*exp) == lparen) // 왼쪽괄호의 경우
        {
            
            postfixPush(*exp); // 스택에 삽입한다.
        }
        else if (getPriority(*exp) == rparen){ // 오른쪽 괄호의 경우
            while((x = postfixPop()) != '('){ // 왼쪽 괄호가 나올때까지 팝해서
                charCat(&x); //후위표기 Exp에 삽입한다.
            }
        }
        else //나머지 (+,-,*,/)
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)){ //스택에 쌓인 연산자가 우선순위가 높은 경우
                x = postfixPop(); //스택에서 1개 팝하여
                charCat(&x); // 후위표기 Exp에 삽입
            }
            postfixPush(*exp); // 읽은 연산자를 후위표기 Exp에 삽입
        }
        
        exp++; // 다음 문자 읽기
    }

    while (postfixStackTop != -1) //스택에 남은 연산자들을 Exp에 삽입
    {
        x = postfixPop;
        charCat(&x);

    }
    

         
} // 구현 대상 중위표기스택 -> 후위표기스택으로 변환

void debug(){
    printf("\n---DEBUG\n");
    printf("infixExp = %s\n", infixExp);
    printf("postExp = %s\n", postfixExp);
    printf("eval result = %d\n", evalresult);

    printf("postfixStack : ");
    for (int i = 0; i < MAX_STACK_SIZE; i++)
    {   
        printf("%c ", postfixStack[i]);
    }
    printf("\n");
}

void reset(){

    infixExp[0] = '\0';
    postfixExp[0] = '\0';

    for (int i = 0; i < MAX_STACK_SIZE; i++)
    {
        postfixExp[i] = '\0';
    }

    postfixStackTop = -1;
    evalStackTop = -1;
    evalresult = 0;
}

void evaluation(){
    int op1, op2;

    char symbol;
    evalStackTop = -1;
    
    for (int i = 0; i < strlen(postfixExp); i++)
    {
        symbol = postfixExp[i];
        if (getToken(symbol)==operand) //숫자가 들어오면
        {
            evalPush(symbol -'0'); // 숫자를 계산 스택에 push
        }
        else{ // 연산자가 들어오면
            op2 = evalPop(); 
            op1 = evalPop(); //차례로 pop하여 변수에 넣어준다
            switch (getToken(symbol))
            {
            case plus: 
                evalPush(op1+op2);
                break;
            case minus:
                evalPush(op1-op2);
                break;
            case times:
                evalPush(op1*op2);
                break;
            case divide:
                evalPush(op1/op2);
                break; //연산 기호에 맞게 연산을 한 후 결과를 계산 스택에 push
            default:
                break;
            }
        }
    }

    evalresult = evalPop();
    return;
} // 구현 대상 -> 계산