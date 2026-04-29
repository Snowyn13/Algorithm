#include <string>
#include <vector>

using namespace std;

struct TreeNode {
    int id;
    int x;
    int y;
    TreeNode* left;
    TreeNode* right;
};

struct StackItem {
    TreeNode* node;
    bool visited;
};

struct StackType {
    StackItem * data;
    int top;
    int capacity;
};

void insert_node(TreeNode* root, TreeNode* child);

// ================ 트리 만들기 =================
// y가 가장 큰 노드를 매번 찾아서 삽입한다.

TreeNode * build_tree(TreeNode* nodes, int n) {
    bool * used = new bool[n];

    for (int i = 0; i < n; i++) {
        used[i] = false;
    }

    TreeNode * root = nullptr;

    for (int count = 0; count < n; count++) {
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (used[i]) {
                continue;
            }
            if (selected == -1) {
                selected = i;
            } else if (nodes[i].y > nodes[selected].y) {
                selected = i;
            } else if (nodes[i].y == nodes[selected].y &&
                       nodes[i].x < nodes[selected].x) {
                selected = i;
            }
        }

        used[selected] = true;

        if (root == nullptr) {
            root = &nodes[selected];
        } else {
            insert_node(root, &nodes[selected]);
        }
    }
    
    delete[] used;

    return root;
}

// ================= 이진트리 삽입 =================

void insert_node(TreeNode* root, TreeNode* child) {
    TreeNode* cur = root;

    while (true) {
        if (child->x < cur->x) {
            if (cur->left == nullptr) {
                cur->left = child;
                return;
            }

            cur = cur->left;
        }
        else {
            if (cur->right == nullptr) {
                cur->right = child;
                return;
            }

            cur = cur->right;
        }
    }
}

// stack ADT 구현

void stack_init(StackType* s, int capacity) {
    s->data = new StackItem[capacity];
    s->top = -1;
    s->capacity = capacity;
}

bool stack_empty(StackType* s) {
    return s->top == -1;
}

bool stack_full(StackType* s) {
    return s->top == s->capacity - 1;
}

void stack_push(StackType* s, TreeNode* node, bool visited) {
    if (stack_full(s)) {
        return;
    }

    s->data[++(s->top)].node = node;
    s->data[s->top].visited = visited;
}

StackItem stack_pop(StackType* s) {
    StackItem empty_item;
    empty_item.node = nullptr;
    empty_item.visited = false;

    if (stack_empty(s)) {
        return empty_item;
    }

    return s->data[(s->top)--];
}

// ================= 전위 순회 =================
// root -> left -> right

void preorder(TreeNode* root, int n, int* result) {
    StackType s;
    stack_init(&s, n);

    int idx = 0;

    stack_push(&s, root, false);

    while (!stack_empty(&s)) {
        StackItem item = stack_pop(&s);
        TreeNode* cur = item.node;

        if (cur == nullptr) {
            continue;
        }

        result[idx++] = cur->id;

        if (cur->right != nullptr) {
            stack_push(&s, cur->right, false);
        }

        if (cur->left != nullptr) {
            stack_push(&s, cur->left, false);
        }
    }
}

// ================= 후위 순회 =================
// left -> right -> root

void postorder(TreeNode* root, int n, int* result) {
    StackType s;
    stack_init(&s, n * 2); // 자기 자신을 넣기 위한 여유 스택

    int idx = 0;

    stack_push(&s, root, false);

    while (!stack_empty(&s)) {
        StackItem item = stack_pop(&s);
        TreeNode* cur = item.node;

        if (cur == nullptr) {
            continue;
        }

        if (item.visited) {
            // 자식들을 이미 스택에 넣고 처리한 뒤 다시 만난 노드.
            // 후위 순회에서는 left, right 처리 후 root를 방문하므로 여기서 출력.
            result[idx++] = cur->id;
        }
        else {
            // 처음 만난 노드.
            // root는 나중에 출력해야 하므로 visited=true로 다시 넣어둔다.
            stack_push(&s, cur, true);

            // LIFO라서 right를 먼저 넣고 left를 나중에 넣어야
            // left가 먼저 처리된다.
            if (cur->right != nullptr) {
                stack_push(&s, cur->right, false);
            }

            if (cur->left != nullptr) {
                stack_push(&s, cur->left, false);
            }
        }
    }
}

// solution 함수

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    int n = nodeinfo.size();

    TreeNode* nodes = new TreeNode[n];

    for (int i = 0; i < n; i++) {
        nodes[i].id = i + 1;
        nodes[i].x = nodeinfo[i][0];
        nodes[i].y = nodeinfo[i][1];
        nodes[i].left = nullptr;
        nodes[i].right = nullptr;
    }

    TreeNode* root = build_tree(nodes, n);

    int * pre_result = new int[n];
    int * post_result = new int[n];

    preorder(root, n, pre_result);
    postorder(root, n, post_result);

    vector<vector<int>> answer(2);

    for (int i = 0; i < n; i++) {
        answer[0].push_back(pre_result[i]);
    }

    for (int i = 0; i < n; i++) {
        answer[1].push_back(post_result[i]);
    }

    return answer;
}