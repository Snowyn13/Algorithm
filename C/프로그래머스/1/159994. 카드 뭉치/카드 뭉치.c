#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// ===== 원형큐 코드 시작 =====
#define MAX_QUEUE_SIZE 30
typedef const char* element;

typedef struct { // 큐 타입
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

// 오류 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 초기화 함수
void init_queue(QueueType *q)
{
    q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
    return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType *q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 원형큐 출력 함수 (제출에는 없어도 되지만 교안 스타일 유지용)
void queue_print(QueueType *q)
{
    int i;
    printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);

    if (!is_empty(q)) {
        i = q->front;
        do {
            i = (i + 1) % MAX_QUEUE_SIZE;
            printf("%s | ", q->data[i]);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n");
}

// 삽입 함수
void enqueue(QueueType *q, element item)
{
    if (is_full(q))
        error("큐가 포화상태입니다");

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType *q)
{
    if (is_empty(q))
        error("큐가 공백상태입니다");

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 맨 앞 원소 확인 함수 (문제 풀이용 추가)
element peek(QueueType *q)
{
    if (is_empty(q))
        return NULL;

    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

// cards1_len은 배열 cards1의 길이입니다.
// cards2_len은 배열 cards2의 길이입니다.
// goal_len은 배열 goal의 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
char* solution(const char* cards1[], size_t cards1_len,
               const char* cards2[], size_t cards2_len,
               const char* goal[], size_t goal_len) {
    
    QueueType q1, q2;
    init_queue(&q1);
    init_queue(&q2);

    // cards1을 큐에 삽입
    for (size_t i = 0; i < cards1_len; i++) {
        enqueue(&q1, cards1[i]);
    }

    // cards2를 큐에 삽입
    for (size_t i = 0; i < cards2_len; i++) {
        enqueue(&q2, cards2[i]);
    }

    // goal 순서대로 확인
    for (size_t i = 0; i < goal_len; i++) {
        if (!is_empty(&q1) && strcmp(peek(&q1), goal[i]) == 0) {
            dequeue(&q1);
        }
        else if (!is_empty(&q2) && strcmp(peek(&q2), goal[i]) == 0) {
            dequeue(&q2);
        }
        else {
            char* answer = (char*)malloc(3);
            strcpy(answer, "No");
            return answer;
        }
    }

    char* answer = (char*)malloc(4);
    strcpy(answer, "Yes");
    return answer;
}