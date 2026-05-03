#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct TreeNode {
    int id;
    struct TreeNode** neighbors;
    int neighbor_count;
} TreeNode;

typedef struct StackType {
    TreeNode** data;
    int top;
    int capacity;
} StackType;

void stack_init(StackType* s, int capacity) {
    s->data = (TreeNode**)malloc(sizeof(TreeNode*) * capacity);
    s->top = -1;
    s->capacity = capacity;
}

bool stack_empty(StackType* s) {
    return s->top == -1;
}

bool stack_full(StackType* s) {
    return s->top == s->capacity - 1;
}

void stack_push(StackType* s, TreeNode* node) {
    if (stack_full(s)) {
        return;
    }

    s->data[++(s->top)] = node;
}

TreeNode* stack_pop(StackType* s) {
    if (stack_empty(s)) {
        return NULL;
    }

    return s->data[(s->top)--];
}

int dfs_count(TreeNode* nodes, int n, int start, int cut_a, int cut_b) {
    bool* visited = (bool*)calloc(n + 1, sizeof(bool));

    StackType s;
    stack_init(&s, n + 1);

    int count = 0;

    stack_push(&s, &nodes[start]);
    visited[start] = true;

    while (!stack_empty(&s)) {
        TreeNode* cur = stack_pop(&s);
        count++;

        for (int i = 0; i < cur->neighbor_count; i++) {
            TreeNode* next = cur->neighbors[i];

            if ((cur->id == cut_a && next->id == cut_b) ||
                (cur->id == cut_b && next->id == cut_a)) {
                continue;
            }

            if (!visited[next->id]) {
                visited[next->id] = true;
                stack_push(&s, next);
            }
        }
    }

    free(s.data);
    free(visited);

    return count;
}

int solution(int n, int** wires, size_t wires_rows, size_t wires_cols) {
    TreeNode* nodes = (TreeNode*)malloc(sizeof(TreeNode) * (n + 1));
    int* degree = (int*)calloc(n + 1, sizeof(int));

    for (int i = 0; i < wires_rows; i++) {
        int a = wires[i][0];
        int b = wires[i][1];

        degree[a]++;
        degree[b]++;
    }

    for (int i = 1; i <= n; i++) {
        nodes[i].id = i;
        nodes[i].neighbors = (TreeNode**)malloc(sizeof(TreeNode*) * degree[i]);
        nodes[i].neighbor_count = 0;
    }

    for (int i = 0; i < wires_rows; i++) {
        int a = wires[i][0];
        int b = wires[i][1];

        nodes[a].neighbors[nodes[a].neighbor_count++] = &nodes[b];
        nodes[b].neighbors[nodes[b].neighbor_count++] = &nodes[a];
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

    for (int i = 1; i <= n; i++) {
        free(nodes[i].neighbors);
    }

    free(degree);
    free(nodes);

    return answer;
}