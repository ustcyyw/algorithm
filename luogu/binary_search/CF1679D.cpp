/**
 * @Time : 2023/12/8-11:12 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 最大权值最小 标准二分模版
 * 固定结点权值 t 的情况下
 * 1.看能否找到环 成环 就一定能找到长度为k的路径
 * 2.没有环的情况下，dp找最长路径
 * 以上都要注意 如果子结点的权值 <= t 才能访问子结点
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, m, val[N];
long long k;

vector<vector<int>> graph;

bool check_cycle(int t) {
    bool cycle = false;
    vector<bool> marked(n + 1, false), onStack(n + 1, false);
    function<void(int)> dfs = [&](int v) {
        if(cycle) return ;
        marked[v] = true, onStack[v] = true;
        for(int w : graph[v]) {
            if(!marked[w] && val[w] <= t) dfs(w);
            if(marked[w]) {
                if(onStack[w]) {
                    cycle = true;
                    return ;
                }
            }
        }
        onStack[v] = false;
    };
    for(int i = 1; i <= n; i++) {
        if(val[i] <= t && !marked[i])
            dfs(i);
        if(cycle) return true;
    }
    return false;
}

bool check(int t) {
    if(check_cycle(t)) return true;
    if(k > n) return false; // 不存在环的情况下 最长路径最多等于结点数量 k比n大 则找不到这样的路径
    vector<int> depth(n + 1, -1);
    int len = 0;
    function<void(int)> dfs = [&](int v) {
        int cl = 1;
        for(int w : graph[v]) {
            if(depth[w] == -1 && val[w] <= t)
                dfs(w);
            cl = max(cl, depth[w] + 1);
        }
        depth[v] = cl;
        len = max(cl, len);
    };
    for(int i = 1; i <= n; i++) {
        if(val[i] <= t && depth[i] == -1)
            dfs(i);
        if(len >= k) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(val, 0, sizeof(val));
    cin >> n >> m;
    cin >> k;
    int maxV = 0;
    for(int i = 1; i <= n; i++) {
        cin >> val[i];
        maxV = max(maxV, val[i]);
    }
    graph.assign(n + 1, {});
    for(int i = 1, v, w; i <= m; i++) {
        cin >> v >> w;
        graph[v].push_back(w);
    }
    int lo = 1, hi = maxV + 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    if(lo == maxV + 1) cout << -1 << endl;
    else cout << lo << endl;
}
