#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// cards1_len은 배열 cards1의 길이입니다.
// cards2_len은 배열 cards2의 길이입니다.
// goal_len은 배열 goal의 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.

typedef const char* element;
typedef struct queue{
    element* data;
    int front;
    int rear;
    int capacity;
}Queue;

void free_q(Queue* q)
{
    free(q->data);
}

void init(Queue* q, int capacity)
{
    q->capacity=capacity+1;
    q->data=(element*)malloc(sizeof(element)*q->capacity);
    q->front=0;
    q->rear=0;
}

int empty(Queue* q)
{
    return q->front==q->rear;
}

int full(Queue* q)
{
    return (q->rear+1)%q->capacity==q->front;
}

void enqueue(Queue* q, const element val)
{
    if(full(q))
    {
        fprintf(stderr,"큐 포화 에러\n");
        return;
    }
    else
    {
        q->rear=(q->rear+1)%q->capacity;
        q->data[q->rear]=val;
    }
}

element dequeue(Queue* q)
{
    if(empty(q))
    {
        fprintf(stderr,"큐 공백 에러\n");
        return NULL;
    }
    else
    {
        q->front=(q->front+1)%q->capacity;
        return q->data[q->front];
    }
}

element peek(Queue* q)
{
    if(empty(q))
    {
        fprintf(stderr,"큐 공백 에러\n");
        return NULL;
    }
    else
        return q->data[(q->front+1)%q->capacity];
}

char* solution(const char* cards1[], size_t cards1_len, const char* cards2[], size_t cards2_len, const char* goal[], size_t goal_len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    Queue q1;
    Queue q2;
    init(&q1,cards1_len);
    init(&q2,cards2_len);
    
    for(int i=0;i<cards1_len;i++)
        enqueue(&q1,cards1[i]);
    
    for(int i=0;i<cards2_len;i++)
        enqueue(&q2,cards2[i]);
    
    for(int i=0;i<goal_len;i++)
    {
        if(!empty(&q1)&&strcmp(peek(&q1),goal[i])==0)
            dequeue(&q1);
        else if(!empty(&q2)&&strcmp(peek(&q2),goal[i])==0)
            dequeue(&q2);
        else
        {
            free_q(&q1);
            free_q(&q2);
            char* answer = (char*)malloc(3);
            
            strcpy(answer,"No");
            return answer;
        }
    }
    free_q(&q1);
    free_q(&q2);
    
    char* answer = (char*)malloc(4);
    strcpy(answer,"Yes");
    return answer;
}