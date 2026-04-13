#include <string>
#include <vector>

using namespace std;

typedef struct queue {
    int* data;
    int front;
    int rear;
    int capacity;
}Queue;

void init(Queue* q, int capacity)
{
    q->capacity = capacity + 1;
    q->data = (int*)malloc(sizeof(int) * q->capacity);
    q->front = 0;
    q->rear = 0;
}

int empty_q(Queue* q)
{
    return q->front == q->rear;
}

int full_q(Queue* q)
{
    return (q->rear + 1) % q->capacity == q->front;
}

void enqueue(Queue* q, int val)
{
    if (!full_q(q)) {
        q->rear = (q->rear + 1) % q->capacity;
        q->data[q->rear] = val;
    }
    else return;
}

int dequeue(Queue* q)
{
    if (!empty_q(q)) {
        q->front = (q->front + 1) % q->capacity;
        return q->data[q->front];
    }
    else
        return -1;
}

int peek(Queue* q)
{
    if (!empty_q(q)) {
        return q->data[(q->front + 1) % q->capacity];
    }
    else
        return -1;
}

void free_q(Queue* q)
{
    free(q->data);
}

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    Queue q;
    init(&q, progresses.size());

    for (int i = 0; i < progresses.size(); i++) {
        int remain = 100 - progresses[i];
        int day = remain / speeds[i];
        if (remain % speeds[i] != 0)
            day++;

        enqueue(&q, day);
    }

    while (!empty_q(&q)) {
        int count = 1;
        int de = dequeue(&q);

        while (!empty_q(&q) && peek(&q) <= de) {
            count++;
            dequeue(&q);
        }
        answer.push_back(count);
    }
    free_q(&q);
    return answer;
}