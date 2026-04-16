#include <string>
#include <vector>

using namespace std;
typedef struct stack
{
    int* data;
    int top;
    int capacity;
}Stack;

void init(Stack* s, int capacity)
{
    s->capacity=capacity;
    s->data=(int*)malloc(sizeof(int)*s->capacity);
    s->top=-1;
}

int empty(Stack* s)
{
    return s->top==-1;
}
    
int full(Stack* s)
{
    return s->top==s->capacity-1;
}

void push(Stack* s, int val)
{
    if(full(s))
    {
        fprintf(stderr,"스택 포화 에러 \n");
        return;
    }
    else
        s->data[++(s->top)]=val;
}

int pop(Stack* s)
{
    if(empty(s))
    {
        fprintf(stderr,"스택 공백 에러 \n");
        return -1;
    }
    else
        return s->data[(s->top)--];
}

int peek(Stack* s)
{
    if(full(s))
    {
        fprintf(stderr,"스택 공백 에러 \n");
        return -1;
    }
    else
        return s->data[(s->top)];
}

void free_s(Stack* s)
{
    free(s->data);
}

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    Stack s;
    int n=board.size();
    init(&s,n*n);
    
    for(int i=0;i<moves.size();i++){
        int col=moves[i]-1;
        for(int row=0;row<n;row++){
            if(board[row][col]!=0){
                int doll=board[row][col];
                board[row][col]=0;
                
                if(!empty(&s)&&peek(&s)==doll){
                    pop(&s);
                    answer+=2;
                }
                else{
                    push(&s,doll);   
                }
                break;
            }
        }
    }
    free_s(&s);
    return answer;
}