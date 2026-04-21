#include <iostream>
#include<string>
using namespace std;
typedef struct stack
{
    char* data;
    int top;
    int capacity;
}Stack;

void free_s(Stack* s)
{
    free(s->data);
}

void init(Stack* s, int capacity)
{
    s->capacity=capacity;
    s->data=(char*)malloc(sizeof(char)*s->capacity);
    s->top=-1;
}

int empty(Stack* s)
{   
    return s->top==-1;
}

int full(Stack* s)
{
    return s->top==s->capacity-1;
}

void push(Stack* s, char val)
{
    if(full(s))
    {
        fprintf(stderr,"스택 포화 에러\n");
        return;
    }
    else
        s->data[++(s->top)]=val;
}

char pop(Stack* s)
{
    if(empty(s))
    {
        fprintf(stderr,"스택 공백 에러\n");
        return '\0';
    }
    else
        return s->data[(s->top)--];
}

char peek(Stack* s)
{
    if(empty(s))
    {
        fprintf(stderr,"스택 공백 에러\n");
        return '\0';
    }
    else
        return s->data[s->top];
}

int solution(string s)
{
    int answer = -1;
    int len=s.length();
    Stack st;
    init(&st,len);
    
    for(int i=0;i<len;i++)
    {
        char c=s[i];
        if(!empty(&st)&&peek(&st)==c)
        {
            pop(&st);
        }
        else
            push(&st,c);
    }
    answer=empty(&st)?1:0;
    free_s(&st);
    return answer;
}