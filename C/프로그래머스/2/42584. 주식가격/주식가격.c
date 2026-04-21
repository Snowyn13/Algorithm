#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct stack
{
    int* data;
    int top;
    int capacity;
}Stack;

void init(Stack* s, int capacity)
{
    s->capacity=capacity;
    s->data=(int*)malloc(sizeof(int)*s->capacity);
    s->top=-1;
}

void free_s(Stack* s)
{
    free(s->data);
}

int empty(Stack* s)
{
    return s->top==-1;
}

int full(Stack* s)
{
    return s->top==s->capacity-1;
}

void push(Stack* s,int val)
{
    if(full(s))
    {
        fprintf(stderr,"스택 포화 에러\n");
        return;
    }
    else
        s->data[++(s->top)]=val;
}

int pop(Stack* s)
{
    if(empty(s))
    {
        fprintf(stderr,"스택 공백 에러\n");
        return -1;
    }
    else
        return s->data[(s->top)--];
}

int peek(Stack* s)
{
    if(empty(s))
    {
        fprintf(stderr,"스택 공백 에러\n");
        return -1;
    }
    else
        return s->data[(s->top)];
}

// prices_len은 배열 prices의 길이입니다.
int* solution(int prices[], size_t prices_len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(sizeof(int)*prices_len);
    Stack s;
    init(&s,prices_len);
    
    for(int i=0;i<prices_len;i++)
    {
        while(!empty(&s)&&prices[i]<prices[peek(&s)])
        {
            int topn=pop(&s);
            answer[topn]=i-topn;
        }
        push(&s,i);
    }
    
    while(!empty(&s))
    {
        int topn=pop(&s);
        answer[topn]=prices_len-1-topn;
    }
    free_s(&s);
    return answer;
}