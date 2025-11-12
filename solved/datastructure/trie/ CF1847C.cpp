/**
 * @Time : 2024/2/14-9:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 5, D = 9;
int T, n, nums[N];

struct Node {
    Node *next[2];
    Node() {
        memset(next, NULL, sizeof(next));
    }
};

class Trie {
    Node *root = new Node();
    Node* insert(Node* x, int& num, int i) {
        if(x == nullptr)
            x = new Node();
        if(i == -1) return x;
        int mask = (num >> i) & 1;
        x->next[mask] = insert(x->next[mask], num, i - 1);
        return x;
    }

    int search(Node* x, int& num, int i) {
        if(x == nullptr || i == -1) return 0;
        int d = (num >> i) & 1;
        if(x->next[!d] != nullptr) return (1 << i) + search(x->next[!d], num, i - 1);
        else return search(x->next[d], num, i - 1);
    }

public:
    void insert(int num) {
        root = insert(root, num, D);
    }

    int search(int num) {
        return search(root, num, D);
    }
};

void solve() {
    int res = 0;
    Trie trie;
    trie.insert(0);
    for(int i = 0, pre = 0; i < n; i++) {
        pre ^= nums[i];
        res = max(res, trie.search(pre));
        trie.insert(pre);
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> nums[i];
        solve();
    }
};