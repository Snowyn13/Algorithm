#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef const char* element;

typedef struct {
    element* data;
    int front, rear;
    int capacity;
} QueueType;

// 초기화 (동적 할당)
void init_queue(QueueType *q, int max_items)
{
    q->capacity = max_items + 1;  // 한 칸 비움
    q->data = (element*)malloc(sizeof(element) * q->capacity);
    q->front = q->rear = 0;
}

// 메모리 해제
void free_queue(QueueType *q)
{
    free(q->data);
}

// 공백
int is_empty(QueueType *q)
{
    return q->front == q->rear;
}

// 포화
int is_full(QueueType *q)
{
    return (q->rear + 1) % q->capacity == q->front;
}

// 삽입
void enqueue(QueueType *q, element item)
{
    if (is_full(q))
        error("큐 포화");

    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = item;
}

// 삭제
element dequeue(QueueType *q)
{
    if (is_empty(q))
        error("큐 공백");

    q->front = (q->front + 1) % q->capacity;
    return q->data[q->front];
}

// 확인
element peek(QueueType *q)
{
    if (is_empty(q)) return NULL;
    return q->data[(q->front + 1) % q->capacity];
}

char* solution(const char* cards1[], size_t cards1_len,
               const char* cards2[], size_t cards2_len,
               const char* goal[], size_t goal_len) {
    
    QueueType q1, q2;

    init_queue(&q1, cards1_len);
    init_queue(&q2, cards2_len);

    for (size_t i = 0; i < cards1_len; i++)
        enqueue(&q1, cards1[i]);

    for (size_t i = 0; i < cards2_len; i++)
        enqueue(&q2, cards2[i]);

    for (size_t i = 0; i < goal_len; i++) {
        if (!is_empty(&q1) && strcmp(peek(&q1), goal[i]) == 0) {
            dequeue(&q1);
        }
        else if (!is_empty(&q2) && strcmp(peek(&q2), goal[i]) == 0) {
            dequeue(&q2);
        }
        else {
            //free_queue(&q1);
            //free_queue(&q2);

            char* answer = (char*)malloc(3);
            strcpy(answer, "No");
            return answer;
        }
    }

    free_queue(&q1);
    free_queue(&q2);

    char* answer = (char*)malloc(4);
    strcpy(answer, "Yes");
    return answer;
}