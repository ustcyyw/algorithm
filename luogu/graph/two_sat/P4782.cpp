/**
 * @Time : 2025/1/30-9:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e6 + 5, M = 2 * N;
int n, m, dfn[M], low[M], color[M], onSta[M];
vector<int> graph[M];

void add(int x1, int v1, int x2, int v2) {
    if(v1 == 0 && v2 == 0) { // x1为假 或者 x2为假
        graph[x1].push_back(x2 + n);
        graph[x2].push_back(x1 + n);
    } else if(v1 == 1 && v2 == 1) { // x1为真 或者 x2为真
        graph[x1 + n].push_back(x2);
        graph[x2 + n].push_back(x1);
    } else if(v1 == 1 && v2 == 0) { // x1为真 或者 x2为假
        graph[x1 + n].push_back(x2 + n);
        graph[x2].push_back(x1);
    } else { // x1为假 或者 x2为真
        graph[x1].push_back(x2);
        graph[x2 + n].push_back(x1 + n);
    }
}

void scc() {
    int cc = 0, time = 1; // 分别表示颜色和时间戳
    stack<int> stack;
    function<void(int)> dfs = [&](int v) -> void {
        dfn[v] = low[v] = ++time;
        onSta[v] = 1, stack.push(v);
        for(int w : graph[v]) {
            if(dfn[w] == 0) {
                dfs(w);
                low[v] = min(low[v], low[w]);
            } else if(onSta[w])
                low[v] = min(low[v], dfn[w]);
        }
        if(dfn[v] == low[v]) {
            color[v] = ++cc;
            int temp = -1;
            while(temp != v) {
                temp = stack.top();
                color[temp] = cc; // 标记该结点的颜色
                onSta[temp] = 0, stack.pop();
            }
        }
    };
    for(int i = 1; i <= 2 * n; i++)
        if(dfn[i] == 0) dfs(i);
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n >> m;
    for(int i = 1, x1, v1, x2, v2; i <= m; i++) {
        cin >> x1 >> v1 >> x2 >> v2;
        add(x1, v1, x2, v2);
    }
    scc();
    for(int i = 1; i <= n; i++) {
        if(color[i] == color[i + n]) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    cout << "POSSIBLE\n";
    for(int i = 1; i <= n; i++)
        cout << (color[i] < color[i + n]) << " ";
};