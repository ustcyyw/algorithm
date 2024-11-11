/**
 * @Time : 2023/5/15-12:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */


#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m, len[N];
vector<vector<int>> graph;

void dfs(int v) {
    if(len[v] != -1) return;
    int ans = 0;
    for(int w : graph[v]) {
        dfs(w);
        ans = max(ans, len[w]);
    }
    len[v] = ans + 1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    fill(len, len + n + 1, -1);
    graph.assign(n + 1, {});
    for(int i = 1, x, y; i <= m; i++){
        cin >> x >> y;
        graph[y].push_back(x);
    }
    for(int i = 1; i <= n; i++) {
        dfs(i);
        cout << len[i]<< endl;
    }
}