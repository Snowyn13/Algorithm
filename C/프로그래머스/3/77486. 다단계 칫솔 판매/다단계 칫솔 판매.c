#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Member {
    char name[32];
    int profit;

    // 추천인을 가리키는 부모 포인터
    struct Member* parent;
} Member;

bool str_equal(const char* a, const char* b) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }

    return a[i] == b[i];
}

void str_copy(char* dest, const char* src) {
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}

int find_member(Member* members, int n, const char* name) {
    for (int i = 0; i < n; i++) {
        if (str_equal(members[i].name, name)) {
            return i;
        }
    }

    return -1;
}

void distribute(Member* member, int money) {
    Member* cur = member;

    while (cur != NULL && money > 0) {
        int parent_money = money / 10;
        int my_money = money - parent_money;

        cur->profit += my_money;

        cur = cur->parent;
        money = parent_money;
    }
}

// enroll_len은 배열 enroll의 길이입니다.
// referral_len은 배열 referral의 길이입니다.
// seller_len은 배열 seller의 길이입니다.
// amount_len은 배열 amount의 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int* solution(const char* enroll[], size_t enroll_len, const char* referral[], size_t referral_len, const char* seller[], size_t seller_len, int amount[], size_t amount_len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    Member* members = (Member*)malloc(sizeof(Member) * enroll_len);

    for (int i = 0; i < enroll_len; i++) {
        str_copy(members[i].name, enroll[i]);
        members[i].profit = 0;
        members[i].parent = NULL;
    }

    for (int i = 0; i < referral_len; i++) {
        if (!str_equal(referral[i], "-")) {
            int parent_index = find_member(members, enroll_len, referral[i]);
            members[i].parent = &members[parent_index];
        }
    }

    for (int i = 0; i < seller_len; i++) {
        int seller_index = find_member(members, enroll_len, seller[i]);
        distribute(&members[seller_index], amount[i] * 100);
    }

    int* answer = (int*)malloc(sizeof(int) * enroll_len);

    for (int i = 0; i < enroll_len; i++) {
        answer[i] = members[i].profit;
    }

    return answer;
}