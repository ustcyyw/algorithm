/**
 * @Time : 2023/8/9-4:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 205;
int n, m;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


struct Node {
    ll val;// 整型变量
    Node *next;

    Node() : val(-1ll), next(nullptr) {}

    Node(ll x) : val(x), next(nullptr) {}
};

Node *build(int total) {
    if (total == 0) return nullptr;
    Node *ans = new Node(), *head = ans;
    ans->next = head;
    for (ll i = 0, val; i < total; i++) {
        cin >> val;
        head->next = new Node(val);
        head = head->next;
    }
    return ans->next;
}

void out_list_node(Node *node) {
    while (node != nullptr) {
        cout << node->val << " ";
        node = node->next;
    }
}
