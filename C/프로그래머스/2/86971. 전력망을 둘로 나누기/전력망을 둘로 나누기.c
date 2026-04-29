#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct EdgeNode {
    int to;
    struct EdgeNode* next;
} EdgeNode;

typedef struct TreeNode {
    int id;
    int visited;
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

int dfs_count(TreeNode* nodes, int n, int start, int cut_a, int cut_b) {
    for (int i = 1; i <= n; i++) {
        nodes[i].visited = 0;
    }

    StackType s;
    stack_init(&s, n + 1);

    int count = 0;

    stack_push(&s, start);
    nodes[start].visited = 1;

    while (!stack_empty(&s)) {
        int cur = stack_pop(&s);
        count++;

        EdgeNode* edge = nodes[cur].neighbors;

        while (edge != NULL) {
            int next = edge->to;

            if ((cur == cut_a && next == cut_b) ||
                (cur == cut_b && next == cut_a)) {
                edge = edge->next;
                continue;
            }

            if (!nodes[next].visited) {
                nodes[next].visited = 1;
                stack_push(&s, next);
            }

            edge = edge->next;
        }
    }

    free(s.data);

    return count;
}

int solution(int n, int** wires, size_t wires_rows, size_t wires_cols) {
    TreeNode* nodes = (TreeNode*)malloc(sizeof(TreeNode) * (n + 1));

    for (int i = 1; i <= n; i++) {
        nodes[i].id = i;
        nodes[i].visited = 0;
        nodes[i].neighbors = NULL;
    }

    for (int i = 0; i < wires_rows; i++) {
        int a = wires[i][0];
        int b = wires[i][1];

        add_edge(nodes, a, b);
        add_edge(nodes, b, a);
    }

    int answer = n;

    for (int i = 0; i < wires_rows; i++) {
        int cut_a = wires[i][0];
        int cut_b = wires[i][1];

        int count1 = dfs_count(nodes, n, cut_a, cut_a, cut_b);
        int count2 = n - count1;

        int diff = count1 - count2;
        if (diff < 0) {
            diff = -diff;
        }

        if (diff < answer) {
            answer = diff;
        }
    }

    return answer;
}