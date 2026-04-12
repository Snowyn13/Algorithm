#include <string>
#include <vector>

using namespace std;

typedef struct{
    int * data;
    int top;
    int capacity;
}Struct;

void init(Struct* s,int capacity){
    s->top=-1;
    s->data=(int*)malloc(sizeof(int)*capacity);
    s->capacity=capacity;
}

int empty(Struct* s){
    return s->top==-1;
}

int is_full(Struct* s){
    return s->top==s->capacity-1;
}

int push(Struct* s,int val){
    if(!is_full(s))
        return s->data[++(s->top)]=val;
}

int pop(Struct* s){
    if(!empty(s))
        return s->data[(s->top)--];
}

int peek(Struct* s){
    if(!empty(s))
        return s->data[s->top];
}

void free_stack(Struct* s){
    free(s->data);
}

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    Struct s;
    init(&s,board.size()*board.size());
    
    for(int i = 0; i < moves.size(); i++){
        int col = moves[i] - 1;
        
        for(int row = 0; row < board.size(); row++){
            if(board[row][col] != 0){
                int doll = board[row][col];
                board[row][col] = 0;
                
                if(!empty(&s) && peek(&s) == doll){
                    pop(&s);
                    answer += 2;
                }
                else{
                    push(&s, doll);
                }
                
                break;
            }
        }
    }
    
    free_stack(&s);
    return answer;
}