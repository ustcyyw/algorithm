/**
 * @Time : 2025/3/14-9:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF557E 2300 trie树 递归
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 5000 + 5, mod = 1e9 + 7;
int T, n, K, maxV[N], st[N][N];
string s;

struct Node {
    int cnt, flag;
    Node *left, *right;
    Node() : cnt(0), flag(0), left(nullptr), right(nullptr) {}
};

class Trie {
    Node *root = new Node();
    Node* insert(Node* x, int start, int i) {
        if(x == nullptr)
            x = new Node();
        if(st[start][i - 1])
            x->cnt += 1, x->flag += 1;
        if(i == s.size() || i > maxV[start]) return x;
        if(s[i] == 'a') x->left = insert(x->left, start, i + 1);
        else x->right = insert(x->right, start, i + 1);
        x->cnt = x->flag + count(x->left) + count(x->right);
        return x;
    }

    void search(Node* x, int k, char c, string& ans) {
        if(x == nullptr || x->flag >= k) {
            ans.push_back(c);
            return;
        }
        int cc = x->flag, lc = count(x->left);
        if(cc + lc < k) search(x->right, k - cc - lc, 'b', ans);
        else search(x->left, k - cc, 'a', ans);
        if(c != '.') ans.push_back(c);
    }

    int count(Node* x) {
        return x == nullptr ? 0 : x->cnt;
    }

public:
    void insert(int start) {
        root = insert(root, start, start);
    }

    string search(int k) {
        string ans;
        search(root, k, '.', ans);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

void check(int lo, int hi) {
    while(lo >= 0 && hi < n && s[lo] == s[hi]) {
        st[lo][hi] = 1, maxV[lo] = max(maxV[lo], hi);
        lo -= 2, hi += 2;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> s >> K;
        n = s.size();
        for(int i = 0; i < n; i++) {
            check(i, i), check(i - 1, i + 1);
            check(i, i + 1), check(i - 1, i + 2);
        }
        Trie trie;
        for(int i = 0; i < n; i++)
            trie.insert(i);
        cout << trie.search(K);
    }
}