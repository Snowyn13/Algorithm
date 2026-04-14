#include <string>
#include <vector>
#include <cstdlib>  // malloc, free 때문에 필요

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
}

int dequeue(Queue* q)
{
    if (!empty_q(q)) {
        q->front = (q->front + 1) % q->capacity;
        return q->data[q->front];
    }
    return -1;
}

int peek(Queue* q)
{
    if (!empty_q(q)) {
        return q->data[(q->front + 1) % q->capacity];
    }
    return -1;
}

void free_q(Queue* q)
{
    free(q->data);
}

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    int n = progresses.size();

    // ✅ vector → C 배열로 변환 (추가된 부분)
    int* prog = (int*)malloc(sizeof(int) * n);
    int* spd = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        prog[i] = progresses[i];
        spd[i] = speeds[i];
    }

    Queue q;
    init(&q, n);

    // ✅ 기존 코드 유지, 단지 prog/spd 사용
    for (int i = 0; i < n; i++) {
        int remain = 100 - prog[i];
        int day = remain / spd[i];
        if (remain % spd[i] != 0)
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

    free(prog);
    free(spd);
    free_q(&q);

    return answer;
}