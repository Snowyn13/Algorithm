#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
typedef struct stack
{
    char* data;
    int top;
    int capacity;
}Stack;

void init(Stack* s, int capacity)
{
    s->capacity=capacity;
    s->data=(char*)malloc(sizeof(char)*s->capacity);
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

void  push(Stack* s,char val)
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

int match(char o, char c)
{
    return (o=='(' && c==')') ||
           (o=='{' && c=='}') ||
           (o=='[' && c==']');
}

int rotation(const char* a,int len, int start)
{
    Stack s;
    init(&s,len);
    
    for(int off=0;off<len;off++)
    {
        char c=a[(start+off)%len];
        if(c=='('||c=='{'||c=='[')
            push(&s,c);
        else
        {
            if(empty(&s) || !match(peek(&s),c))
            {
                free_s(&s);
                return 0;
            }
            pop(&s);
        }
    }
    int result=empty(&s);
    free_s(&s);
    return result;
        
}


int solution(const char* s) {
    int answer = 0;
    int len=strlen(s);
    
    for(int i=0;i<len;i++)
        answer+=rotation(s,len,i);
    return answer;
}