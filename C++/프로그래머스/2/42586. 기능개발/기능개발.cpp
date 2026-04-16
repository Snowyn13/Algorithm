#include <string>
#include <vector>

using namespace std;
typedef struct queue{
    int* data;
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
    q->data=(int*)malloc(sizeof(int)*q->capacity);
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

void enqueue(Queue* q,int val)
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

int dequeue(Queue* q)
{
    if(empty(q))
    {
        fprintf(stderr,"큐 공백 에러 \n");
        return -1;
    }
    else
    {
        q->front=(q->front+1)%q->capacity;
        return q->data[q->front];
    }
}

int peek(Queue* q)
{
    if(empty(q))
    {
        fprintf(stderr,"큐 공백 에러 \n");
        return -1;
    }
    else
        return q->data[(q->front+1)%q->capacity];
}

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    Queue q;
    init(&q,progresses.size());
    
    for(int i=0;i<progresses.size();i++)
    {
        int remain=100-progresses[i];
        int day=remain/speeds[i];
        if(remain%speeds[i]!=0)
            day++;
        enqueue(&q,day);
    }
    while(!empty(&q))
    {
        int d=dequeue(&q);
        int c=1;
        
        while(!empty(&q)&&d>=peek(&q))
        {
            c++;
            dequeue(&q);
        }
        answer.push_back(c);
    }
    free_q(&q);
    return answer;
}