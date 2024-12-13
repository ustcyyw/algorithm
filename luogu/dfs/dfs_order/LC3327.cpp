/**
 * @Time : 2024/12/12-10:10 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3327 dfs序 字符串hash
 */
 /*
  * 对树的dfs 某个子树中的结点 不管是访问还是访问结束 都是集中在一个连续的时间内
  * 因此形成的字符串 一定是整个字符串的一个子串
  * 用dfs序快速定位子串 然后用字符串hash判断是否为回文串
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7, P = 13331;
typedef long long ll;
typedef unsigned long long ull;

ull x[N];
int init = []() -> int {
    x[0] = 1;
    for (int i = 1; i < N; i++)
        x[i] = x[i - 1] * P;
    return 0;
}();

vector<ull> str_hash(string &s) {
    int n = s.size();
    vector<ull> h(n + 1, 0);
    for (int i = 1; i <= n; i++)
        h[i] = h[i - 1] * P + s[i - 1];
    return h;
}

ull get_hash(vector<ull> &h, int l, int r) {
    return h[r + 1] - h[l] * x[r - l + 1];
}

class Solution {
public:
    int time = 0, n;
    string str;
    vector<int> count, order;
    vector<vector<int>> graph;
    vector<bool> findAnswer(vector<int>& parent, string s) {
        this->n = parent.size();
        graph.assign(n, {}), count.assign(n, 1), order.assign(n, 0);
        for(int i = 1; i < n; i++)
            graph[parent[i]].push_back(i);
        dfs(s, 0);
        vector<ull> h1 = str_hash(str);
        reverse(str.begin(), str.end());
        vector<ull> h2 = str_hash(str);
        vector<bool> ans;
        for(int i = 0; i < n; i++)
            ans.push_back(check(h1, h2, i));
        return ans;
    }

    bool check(vector<ull>& h1, vector<ull>& h2, int id) {
        int hi1 = order[id], lo1 = hi1 - count[id] + 1;
        int lo2 = n - 1 - hi1, hi2 = n - 1 - lo1;
        return get_hash(h1, lo1, hi1) == get_hash(h2, lo2, hi2);
    }

    void dfs(string& s, int v) {
        for(int w : graph[v]) {
            dfs(s, w);
            count[v] += count[w];
        }
        order[v] = time++, str.push_back(s[v]);
    }
};
