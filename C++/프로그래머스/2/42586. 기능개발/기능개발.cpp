#include <string>
#include <vector>

using namespace std;

struct Queue {
    int* data;
    int front;
    int rear;
    int capacity;
};

void init_queue(Queue* q, int max_items) {
    q->capacity = max_items + 1;
    q->data = (int*)malloc(sizeof(int) * q->capacity);
    q->front = 0;
    q->rear = 0;
}

int queue_empty(Queue* q) {
    return q->front == q->rear;
}

int queue_full(Queue* q) {
    return (q->rear + 1) % q->capacity == q->front;
}

void enqueue(Queue* q, int item) {
    if (queue_full(q)) return;
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = item;
}

int dequeue(Queue* q) {
    if (queue_empty(q)) return -1;
    q->front = (q->front + 1) % q->capacity;
    return q->data[q->front];
}

int peek(Queue* q) {
    if (queue_empty(q)) return -1;
    return q->data[(q->front + 1) % q->capacity];
}

void free_queue(Queue* q) {
    free(q->data);
    q->data = NULL;
}

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    Queue q;

    init_queue(&q, progresses.size());

    // 1. 작업 완료까지 걸리는 날짜 계산 → 큐 저장
    for (int i = 0; i < progresses.size(); i++) {
        int remain = 100 - progresses[i];
        int day = remain / speeds[i];
        if (remain % speeds[i] != 0) day++;

        enqueue(&q, day);
    }

    // 2. 배포 묶음 계산
    while (!queue_empty(&q)) {
        int deployDay = dequeue(&q);
        int count = 1;

        while (!queue_empty(&q) && peek(&q) <= deployDay) {
            dequeue(&q);
            count++;
        }

        answer.push_back(count);
    }

    free_queue(&q);
    return answer;
}