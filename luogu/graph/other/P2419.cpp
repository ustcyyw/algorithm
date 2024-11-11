/**
 * @Time : 2023/5/12-12:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 只要能确定一个点击败的点数 + 击败它的点数 = n - 1
 * 也就确定了它的确切排名为 它击败的点数
 */
#include<bits/stdc++.h>
using namespace std;
int n, m;

void dfs(vector<vector<int>>& graph, vector<vector<bool>>& sets, vector<bool>& marked, int v) {
    marked[v] = sets[v][v] = true;
    for(int w : graph[v]) {
        if(!marked[w])
            dfs(graph, sets, marked, w);
        for(int i = 1; i <= n; i++)
            sets[v][i] = sets[v][i] || sets[w][i];
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    vector<vector<int>> graph1(n + 1), graph2(n + 1);
    for(int i = 0, v, w; i < m; i++) {
        cin >> v >> w;
        graph1[v].push_back(w);
        graph2[w].push_back(v);
    }
    vector<vector<bool>> cnt1(n + 1, vector(n + 1, false)), cnt2(n + 1, vector(n + 1, false));
    vector<bool> marked1(n + 1, false), marked2(n + 1, false);
    for(int i = 1; i <= n; i++)
        if(!marked1[i]) dfs(graph1, cnt1, marked1, i);
    for(int i = 1; i <= n; i++)
        if(!marked2[i]) dfs(graph2, cnt2, marked2, i);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int n1 = accumulate(cnt1[i].begin(), cnt1[i].end(), 0);
        int n2 = accumulate(cnt2[i].begin(), cnt2[i].end(), 0);
        if(n1 + n2 == n + 1) ans++;
    }
    cout << ans << endl;
}