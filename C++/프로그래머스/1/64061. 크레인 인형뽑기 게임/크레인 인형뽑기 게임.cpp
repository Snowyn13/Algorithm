#include <string>
#include <vector>
using namespace std;

typedef struct{
    int* data;
    int top;
    int capacity;
}Stack;

void init(Stack* s,int capacity){
    s->data=(int*)malloc(sizeof(int)*capacity);
    s->top=-1;
    s->capacity=capacity;
}

int empty(Stack* s){
    return s->top==-1;
}

int is_full(Stack* s){
    return s->top==s->capacity-1;
}

void push(Stack* s,int val){
    if(!is_full(s))
        s->data[++(s->top)]=val;
}

int pop(Stack* s){
    if(!empty(s))
        return s->data[(s->top)--];
    return -1;
}

int peek(Stack* s){
    if(!empty(s))
        return s->data[s->top];
    return -1;
}

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    int n = board.size();

    Stack s;
    init(&s, n*n);

    for(int i=0;i<moves.size();i++){
        int col = moves[i]-1;

        for(int row=0;row<n;row++){
            if(board[row][col]!=0){
                int doll = board[row][col];
                board[row][col]=0;

                if(!empty(&s) && peek(&s)==doll){
                    pop(&s);
                    answer+=2;
                }else{
                    push(&s,doll);
                }
                break;
            }
        }
    }

    free(s.data);
    return answer;
}