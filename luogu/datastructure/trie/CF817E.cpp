/**
 * @Time : 2025/4/3-12:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF817E 2000 数据结构 trie树
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, M = 30;
int n, a[N];
const int R = 2;

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
    Node* insert(Node* x, int num, int i) {
        if(x == nullptr)
            x = new Node();
        x->cnt++;
        if(i == -1) return x;
        int d = (1 << i) & num ? 1 : 0;
        x->next[d] = insert(x->next[d], num, i - 1);
        return x;
    }

    Node* remove(Node* x, int num, int i) {
        if(x == nullptr) return nullptr;
        x->cnt--;
        if(i == -1) return x;
        int d = (1 << i) & num ? 1 : 0;
        x->next[d] = remove(x->next[d], num, i - 1);
        return x;
    }

    int search(Node* x, int p, int l, int i) {
        if(x == nullptr || i == -1) return 0;
        int t = 1 << i;
        int dl = (l & t) > 0 ? 1 : 0, dp = (p & t) > 0 ? 1 : 0;
        if(dl) {
            int less = x->next[dp] == nullptr ? 0 : x->next[dp]->cnt;
            return less + search(x->next[!dp], p, l, i - 1);
        } else return search(x->next[dp], p, l, i - 1);
    }

public:
    void insert(int num) {
        root = insert(root, num, M);
    }

    void remove(int num) {
        root = remove(root, num, M);
    }

    int search(int p, int l) {
        return search(root, p, l, M);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    Trie trie;
    for(int i = 1, t, p, l; i <= n; i++) {
        cin >> t >> p;
        if(t == 3) {
            cin >> l;
            cout << trie.search(p, l) << "\n";
        } else if(t == 2) trie.remove(p);
        else trie.insert(p);
    }
}