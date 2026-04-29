#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct EdgeNode {
    int to;
    struct EdgeNode* next;
} EdgeNode;

typedef struct TreeNode {
    int id;
    long long value;
    int visited;

    // 부모 노드를 가리키는 포인터
    struct TreeNode* parent;

    // 연결된 노드들을 저장할 수 있는 필드
    EdgeNode* neighbors;
} TreeNode;

typedef struct StackType {
    int* data;
    int top;
    int capacity;
} StackType;

void stack_init(StackType* s, int capacity) {
    s->data = (int*)malloc(sizeof(int) * capacity);
    s->top = -1;
    s->capacity = capacity;
}

bool stack_empty(StackType* s) {
    return s->top == -1;
}

bool stack_full(StackType* s) {
    return s->top == s->capacity - 1;
}

void stack_push(StackType* s, int value) {
    if (stack_full(s)) {
        return;
    }

    s->data[++(s->top)] = value;
}

int stack_pop(StackType* s) {
    if (stack_empty(s)) {
        return -1;
    }

    return s->data[(s->top)--];
}

void add_edge(TreeNode* nodes, int a, int b) {
    EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    newNode->to = b;
    newNode->next = nodes[a].neighbors;
    nodes[a].neighbors = newNode;
}

long long abs_value(long long value) {
    if (value < 0) {
        return -value;
    }

    return value;
}

// a_len은 배열 a의 길이입니다.
// edges_rows는 2차원 배열 edges의 행 길이, edges_cols는 2차원 배열 edges의 열 길이입니다.
long long solution(int a[], size_t a_len, int** edges, size_t edges_rows, size_t edges_cols) {
    long long sum = 0;

    for (int i = 0; i < a_len; i++) {
        sum += a[i];
    }

    if (sum != 0) {
        return -1;
    }

    TreeNode* nodes = (TreeNode*)malloc(sizeof(TreeNode) * a_len);

    for (int i = 0; i < a_len; i++) {
        nodes[i].id = i;
        nodes[i].value = a[i];
        nodes[i].visited = 0;
        nodes[i].parent = NULL;
        nodes[i].neighbors = NULL;
    }

    for (int i = 0; i < edges_rows; i++) {
        int a_node = edges[i][0];
        int b_node = edges[i][1];

        add_edge(nodes, a_node, b_node);
        add_edge(nodes, b_node, a_node);
    }

    StackType s;
    stack_init(&s, a_len);

    int* order = (int*)malloc(sizeof(int) * a_len);
    int order_count = 0;

    stack_push(&s, 0);
    nodes[0].visited = 1;
    nodes[0].parent = NULL;

    while (!stack_empty(&s)) {
        int cur = stack_pop(&s);
        order[order_count++] = cur;

        EdgeNode* edge = nodes[cur].neighbors;

        while (edge != NULL) {
            int next = edge->to;

            if (!nodes[next].visited) {
                nodes[next].visited = 1;
                nodes[next].parent = &nodes[cur];
                stack_push(&s, next);
            }

            edge = edge->next;
        }
    }

    long long answer = 0;

    for (int i = order_count - 1; i > 0; i--) {
        int cur = order[i];

        answer += abs_value(nodes[cur].value);

        nodes[cur].parent->value += nodes[cur].value;
        nodes[cur].value = 0;
    }

    return answer;
}