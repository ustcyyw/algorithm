/**
 * @Time : 2024/12/4-11:42 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int D = 30;
struct Node {
    Node *next[2];
    int cnt = 0;
    Node() {
        memset(next, NULL, sizeof(next));
    }
};

class Trie {
    Node *root = new Node();
    Node* insert(Node* x, int v, int i) {
        if(x == nullptr)
            x = new Node();
        x->cnt++;
        if(i == -1) return x;
        int k = (1 << i) & v ? 1 : 0;
        x->next[k] = insert(x->next[k], v, i - 1);
        return x;
    }

    int search(Node* x, int v, int i) {
        if(i == -1) return 0;
        int k = (1 << i) & v ? 1 : 0, other = (k + 1) % 2;
        if(x->next[other] != nullptr && x->next[other]->cnt > 0)
            return (1 << i) + search(x->next[other], v, i - 1);
        else if(x->next[k] != nullptr && x->next[k]->cnt > 0)
            return + search(x->next[k], v, i - 1);
        return 0;
    }

    Node* remove(Node* x, int v, int i) {
        if(x == nullptr) return nullptr;
        x->cnt--;
        int k = (1 << i) & v ? 1 : 0;
        x->next[k] = remove(x->next[k], v, i - 1);
        return x;
    }

public:
    void insert(int v) {
        root = insert(root, v, D);
    }

    int search(int v) {
        return search(root, v, D);
    }

    void remove(int v) {
        root = remove(root, v, D);
    }
};