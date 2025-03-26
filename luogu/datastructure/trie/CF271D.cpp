/**
 * @Time : 2025/1/17-11:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF271D 1800 数据结构 trie树
 */
/*
  * 这里不同子数组的定义是内容不同 而不是下标不同
  * 假设子串的左端点是i, 通过双指针找到最大的j使得 s[i,j-1]上最多有k个坏字符
  * 于是这个子串的任意一个前缀都是好子串
  * 为了去重 可以使用trie树 将s[i,j-1]插入trie树中
  * 最终答案就等于trie树中的结点个数（除了根结点）
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7, R = 26;
int T, n, k, ans = 0;
string s, t;

struct Node {
    Node *next[R];
    Node() {
        memset(next, NULL, sizeof(next));
    }
};

Node* insert(Node* x, int i, int j) {
    if(x == nullptr)
        x = new Node();
    if(i == j + 1) return x;
    x->next[s[i] - 'a'] = insert(x->next[s[i] - 'a'], i + 1, j);
    return x;
}

void dfs(Node* x, int cnt) {
    if(cnt > k) return;
    for(int i = 0; i < R; i++) {
        if(x->next[i] == nullptr) continue;
        ans++;
        int add = t[i] == '0';
        dfs(x->next[i], cnt + add);
    }
}

void solve() {
    Node *root = new Node();
    int n = s.size(), cnt = 0;
    for(int i = 0, j = 0; i < n; i++) {
        while(j < n && cnt + (t[s[j] - 'a'] == '0') <= k) {
            cnt += t[s[j] - 'a'] == '0';
            j++;
        }
        root = insert(root, i, j - 1);
        cnt -= t[s[i] - 'a'] == '0';
    }
    dfs(root, 0);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> s >> t >> k;
        solve();
    }
};