#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    int* data;
    int top;
    int capacity;
}Stack;

void init(Stack* s,int capacity){
    s->top=-1;
    s->data=(int*)malloc(sizeof(int)*capacity);
    s->capacity=capacity;
}

int empty(Stack* s){
    return s->top==-1;
}

int is_full(Stack* s){
    return s->top==s->capacity-1;
}

int push(Stack* s,int val){
    if(!is_full(s))
        return s->data[++(s->top)]=val;
}

int pop(Stack*s){
    if(!empty(s))
        return s->data[(s->top)--];
}

int peek(Stack* s){
    if(!empty(s))
        return s->data[s->top];
}

int* solution(int prices[], size_t prices_len) {
    int* answer = (int*)malloc(sizeof(int)*prices_len);
    Stack s;
    init(&s,prices_len);
    
    for(int i=0;i<prices_len;i++){
        while(!empty(&s)&&prices[i]<prices[peek(&s)]){
            int topn=pop(&s);
            answer[topn]=i-topn;
        }
        push(&s,i);
    }
    while(!empty(&s)){
        int topn = pop(&s);
        answer[topn] = prices_len - 1 - topn;
    }
    free(s.data);
    return answer;
}