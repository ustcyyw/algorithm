/**
 * @Time : 2023/12/21-8:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 位运算的题 可以试试拆位 一位一位地分析
 *
 * 二进制位的最高位 如果有的数是1，有的数是0，那么无论x的这一位是0还是1
 * 这一位都会有数字是1 那么究竟让哪些数字保留1，是让原本的1变0还是保持不变 就需要看下一位的情况
 * 但如果这一位都是1或者都是0，那么取x的当前位为相应的1或者0 就能让这一位全变为0
 */
#include<bits/stdc++.h>
using namespace std;
const int R = 2, N = 30;
int n;

struct Node {
    Node *next[R];
    Node() {
        memset(next, NULL, sizeof(next));
    }
};

class Trie {
    Node *root = new Node();
    Node* insert(Node* x, bitset<N> s, int i) {
        if(x == nullptr)
            x = new Node();
        if(i == -1) return x;
        x->next[s[i]] = insert(x->next[s[i]], s, i - 1);
        return x;
    }
    int dfs(Node* x, int i) {
        if(x->next[0] == nullptr && x->next[1] == nullptr) return 0;
        if(x->next[0] == nullptr) return dfs(x->next[1], i - 1);
        if(x->next[1] == nullptr) return dfs(x->next[0], i - 1);
        // 左右两个子结点都存在值的情况 看哪一边经过变化后值更小 然后加上当前位必然保留的1
        int t = 1 << i;
        return min(dfs(x->next[0], i - 1), dfs(x->next[1], i - 1)) + t;
    }
public:
    void insert(bitset<N>& s) {
        root = insert(root, s, N - 1);
    }

    int minMax() {
        return dfs(root, N - 1);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    Trie *trie = new Trie();
    cin >> n;
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        bitset<N> s(num);
        trie->insert(s);
    }
    cout << trie->minMax() << endl;
}