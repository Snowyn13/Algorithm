#include <string>
#include <vector>

using namespace std;

typedef struct{
    int* data;
    int front;
    int rear;
    int capacity;
}Queue;

void init(Queue* q, int capacity)
{
    q->capacity = capacity + 1;
    q->front = 0;
    q->rear = 0;
    q->data = (int*)malloc(sizeof(int) * q->capacity);
}

int empty_c(Queue* q)
{
    return q->front == q->rear;
}

int full_c(Queue* q)
{
    return (q->rear + 1) % q->capacity == q->front;
}

void enqueue(Queue* q, int val)
{
    if (!full_c(q)) {
        q->rear = (q->rear + 1) % q->capacity;
        q->data[q->rear] = val;
    }
    else
        return;
}

int dequeue(Queue* q)
{
    if (!empty_c(q)) {
        q->front = (q->front + 1) % q->capacity;
        return q->data[q->front];
    }
    else
        return -1;
}

int peek(Queue* q)
{
    if (!empty_c(q)) {
        return q->data[(q->front + 1)%q->capacity];
    }
    else
        return -1;
}

void free_Q(Queue* q)
{
    free(q->data);
}

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    Queue q;

    init(&q,progresses.size());

    for (int i = 0; i < progresses.size(); i++) {
        int remain = 100 - progresses[i];
        int day = remain / speeds[i];
        if (remain % speeds[i] != 0)
            day++;
        enqueue(&q, day);
    }

    while (!empty_c(&q)) {
        int c = 1;
        int d = dequeue(&q);

        while (!empty_c(&q) && peek(&q) <= d) {
            c++;
            dequeue(&q);
        }
        answer.push_back(c);
    }
    free_Q(&q);
    return answer;
}