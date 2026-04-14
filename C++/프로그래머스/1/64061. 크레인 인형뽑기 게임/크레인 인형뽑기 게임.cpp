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
    return -1;
}

int pop(Struct* s){
    if(!empty(s))
        return s->data[(s->top)--];
    return -1;
}

int peek(Struct* s){
    if(!empty(s))
        return s->data[s->top];
    return -1;
}

void free_stack(Struct* s){
    free(s->data);
}

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    int n = board.size();
    int m = moves.size();

    // board를 C식 2차원 배열로 복사
    int** arr = (int**)malloc(sizeof(int*) * n);
    for(int i = 0; i < n; i++){
        arr[i] = (int*)malloc(sizeof(int) * n);
        for(int j = 0; j < n; j++){
            arr[i][j] = board[i][j];
        }
    }

    // moves를 C식 배열로 복사
    int* moveArr = (int*)malloc(sizeof(int) * m);
    for(int i = 0; i < m; i++){
        moveArr[i] = moves[i];
    }

    Struct s;
    init(&s, n * n);

    for(int i = 0; i < m; i++){
        int col = moveArr[i] - 1;

        for(int row = 0; row < n; row++){
            if(arr[row][col] != 0){
                int doll = arr[row][col];
                arr[row][col] = 0;

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

    for(int i = 0; i < n; i++){
        free(arr[i]);
    }
    free(arr);
    free(moveArr);

    return answer;
}