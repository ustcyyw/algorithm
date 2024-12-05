/**
 * @Time : 2023/12/21-7:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int R = 26;

struct Node {
    int cnt;
    Node *next[R];
    Node() {
        memset(next, NULL, sizeof(next));
        cnt = 0;
    }
};

class Trie {
    Node *root = new Node();
    Node* insert(Node* x, string& s, int i) {
        if(x == nullptr)
            x = new Node();
        if(i == s.size()) return x;
        x->next[s[i] - 'a'] = insert(x->next[s[i] - 'a'], s, i + 1);
        x->cnt++;
        return x;
    }

    Node* remove(Node* x, string& s, int i) {
        if(x == nullptr) return nullptr;
        x->cnt--;
        if(i == s.size()) return x;
        x->next[s[i] - 'a'] = remove(x->next[s[i] - 'a'], s, i + 1);
        return x;
    }
public:
    void insert(string& s) {
        root = insert(root, s, 0);
    }

    void remove(string& s) {
        root = remove(root, s, 0);
    }
};