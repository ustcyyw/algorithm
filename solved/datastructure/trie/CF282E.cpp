/**
 * @Time : 2024/1/19-9:01 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * xor的最大值 trie树 本题要求前后缀不相交 所以要动态删除
  */
#include<bits/stdc++.h>
using namespace std;
const int R = 2, N = 1e5 + 5, M = 41;

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
    Node* insert(Node* x, bitset<M>& s, int i) {
        if(x == nullptr)
            x = new Node();
        x->cnt++;
        if(i == -1) return x;
        x->next[s[i]] = insert(x->next[s[i]], s, i - 1);
        return x;
    }

    Node* remove(Node* x, bitset<M> s, int i) {
        if(x == nullptr) return nullptr;
        x->cnt--;
        if(i == -1) return x;
        x->next[s[i]] = remove(x->next[s[i]], s, i - 1);
        return x;
    }

    long long search(Node* x, int i, long long val) {
        if(x == nullptr || i == -1) return 0;
        long long mask = (1ll << i) & val;
        int t = mask > 0 ? 0 : 1;
        if(x->next[t] != nullptr && x->next[t]->cnt)
            return (1ll << i) + search(x->next[t], i - 1, val);
        else return search(x->next[(t + 1) % 2], i - 1, val);
    }
public:
    void insert(bitset<M> s) {
        root = insert(root, s, M - 1);
    }

    void remove(bitset<M> s) {
        root = remove(root, s, M - 1);
    }

    long long search(long long val) {
        return search(root, M - 1, val);
    }
};

long long n, nums[N], arr[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    Trie trie;
    trie.insert(bitset<M>(0));
    long long t = 0, res = 0;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
        t ^= nums[i];
        trie.insert(bitset<M>(t)), arr[i] = t;
    }
    t = 0;
    for(int i = n; i >= 1; i--) {
        res = max(res, trie.search(t));
        trie.remove(bitset<M>(arr[i]));
        t ^= nums[i];
    }
    cout << res << endl;
}