#include <iostream>
#include <cstdlib>
#include<string>

using namespace std;

typedef struct{
    char * data;
    int top;
    int capacity;
}Stack;

void init(Stack* s,int capacity);
void free_stack(Stack* s);
int empty(Stack* s);
int is_full(Stack* s);
void push(Stack* s,char val);
char pop(Stack* s);
char peek(Stack* s);

void init(Stack* s,int capacity){
    s->data=(char *)malloc(sizeof(char)*capacity);
    s->top=-1;
    s->capacity=capacity;
}

void free_stack(Stack* s){
    free(s->data);
    s->data=NULL;
    s->top=-1;
    s->capacity=0;
}

int empty(Stack* s){
    return s->top==-1;
}

int is_full(Stack* s){
    return s->top==s->capacity-1;
}

void push(Stack* s,char val){
    if(!is_full(s))
        s->data[++(s->top)]=val;
}

char pop(Stack* s){
    if(!empty(s))
        return s->data[(s->top)--];
    return '\0';
}

char peek(Stack* s){
    if(!empty(s))
        return s->data[s->top];
    return '\0';
}

int solution(string s)
{
    int len=s.length();
    int answer = -1;
    
    if(len%2!=0)
        return 0;
    
    Stack stack;
    init(&stack,len);
    
    for(int i=0;i<len;i++){
        char current = s[i];
        
        if(!empty(&stack)&&peek(&stack)==current){
            pop(&stack);
        }
        else{
            push(&stack,current);
        }
    }
    
    answer=empty(&stack)?1:0;
    free_stack(&stack);

    return answer;
}