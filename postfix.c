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
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];

int postfixStackTop = -1;
int evalStackTop = -1;

int evalresult = 0;

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

    char command;

    do
    {
        printf("----------------------------------------------------------------\n");
      printf("               Infix to Postfix, then Evaluation               \n");
      printf("----------------------------------------------------------------\n");
      printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
      printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

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
    postfixStack[++postfixStackTop] = x;
}

char postfixPop(){
    char x;
    if(postfixStackTop==-1)
        return '\0';
    else{
        x = postfixStack[postfixStackTop--];
    }

    return x;
}

void evalPush(int x){
    evalStack[++evalStackTop] = x;
}

int evalPop(){
    int x;
    if (evalStackTop == -1)
        return -1;
    else{
        x = evalStack[evalStackTop--];
    }
    
    return x;
}

void getInfix(){

    printf("Type the expression >>> ");
    scanf("%s", infixExp);
}

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
}

precedence getPriority(char x){
    return getToken(x);
}

void charCat(char* c){
    if(postfixExp == '\0')
        strcpy(postfixExp, c, 1);
    else
        strcat(postfixExp, c, 1);
}

void toPostfix(){} // 구현 대상 중위표기스택 -> 후위표기스택으로 변환

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

void evaluation(){} // 구현 대상 -> 계산