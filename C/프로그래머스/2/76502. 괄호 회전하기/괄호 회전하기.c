#include <string.h>

typedef struct {
    char data[1000];
    int top;
} CharStack;

void init_stack(CharStack *s) {
    s->top = -1;
}

int is_empty(CharStack *s) {
    return s->top == -1;
}

void push(CharStack *s, char c) {
    s->data[++s->top] = c;
}

char pop(CharStack *s) {
    return s->data[s->top--];
}

char peek(CharStack *s) {
    return s->data[s->top];
}

int match(char o, char c) {
    return (o == '(' && c == ')') ||
           (o == '[' && c == ']') ||
           (o == '{' && c == '}');
}

int valid_rotation(const char *s, int n, int start) {
    CharStack st;
    init_stack(&st);

    for (int off = 0; off < n; ++off) {
        char c = s[(start + off) % n];

        if (c == '(' || c == '[' || c == '{')
            push(&st, c);
        else if (is_empty(&st) || !match(peek(&st), c))
            return 0;
        else
            pop(&st);
    }

    return is_empty(&st);
}

int solution(const char *s) {
    int n = strlen(s);
    int answer = 0;

    for (int i = 0; i < n; ++i)
        answer += valid_rotation(s, n, i);

    return answer;
}