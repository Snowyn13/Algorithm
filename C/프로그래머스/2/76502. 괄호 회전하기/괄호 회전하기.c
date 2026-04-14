#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.

typedef struct {
    char* data;
    int top;
    int capacity;
} CharStack;

void init_stack(CharStack* s, int capacity) {
    s->data = (char*)malloc(sizeof(char) * capacity);
    s->top = -1;
    s->capacity = capacity;
}

void free_stack(CharStack* s) {
    free(s->data);
}

int is_empty(CharStack* s) {
    return s->top == -1;
}

int is_full(CharStack* s) {
    return s->top == s->capacity - 1;
}

void push(CharStack* s, char c) {
    if (!is_full(s))
        s->data[++s->top] = c;
}

char pop(CharStack* s) {
    if (!is_empty(s))
        return s->data[s->top--];
    return '\0';
}

char peek(CharStack* s) {
    if (!is_empty(s))
        return s->data[s->top];
    return '\0';
}

int match(char o, char c) {
    return (o == '(' && c == ')') ||
           (o == '[' && c == ']') ||
           (o == '{' && c == '}');
}

int valid_rotation(const char* s, int n, int start) {
    CharStack st;
    init_stack(&st, n);

    for (int off = 0; off < n; off++) {
        char c = s[(start + off) % n];

        if (c == '(' || c == '[' || c == '{') {
            push(&st, c);
        } else {
            if (is_empty(&st) || !match(peek(&st), c)) {
                free_stack(&st);
                return 0;
            }
            pop(&st);
        }
    }

    int result = is_empty(&st);
    free_stack(&st);
    return result;
}

int solution(const char* s) {
    int n = strlen(s);
    int answer = 0;

    for (int i = 0; i < n; i++) {
        answer += valid_rotation(s, n, i);
    }

    return answer;
}