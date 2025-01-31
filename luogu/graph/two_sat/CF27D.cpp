/**
 * @Time : 2025/1/30-10:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 考虑路径i和j如何安排 如果这两条路径都放在内或者外会交叉
  * 那么
  * i在内部 -> j在外部， i在外部 -> j在内部
  * j在内部 -> i在外部， j在外部 -> i在内部
  * 有明显的逻辑推导方向 并且在内部还是外部是一个二元状态 可以用0/1分别表示在外部和内部
  * 将问题转化为了2sat问题
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 100 + 5, M = 2 * N;
int n, m, path[N][2], dfn[M], low[M], color[M], onSta[M];
vector<int> graph[M];
// 规定环内为1 环外为0
void add(int i, int j) {
    int v1 = path[i][0], w1 = path[i][1], v2 = path[j][0], w2 = path[j][1];
    if(v1 == v2 || v1 == w2 || w1 == v2 || w1 == w2) return;
    // 查看v2、w2结点是否在 v1-w1的右侧
    int f1 = v2 > v1 && v2 < w1, f2 = w2 > v1 && w2 < w1;
    if(f1 == f2) return; // 同侧 那么这两条路径在环内或者环外都可以
    graph[i].push_back(j + m), graph[i + m].push_back(j);
    graph[j].push_back(i + m), graph[j + m].push_back(i);
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
    for(int i = 1; i <= 2 * m; i++)
        if(dfn[i] == 0) dfs(i);
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        cin >> path[i][0] >> path[i][1];
        if(path[i][0] > path[i][1]) swap(path[i][0], path[i][1]);
    }
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= m; j++) {
            add(i, j);
        }
    }
    scc();
    for(int i = 1; i <= m; i++) {
        if(color[i] == color[i + m]) {
            cout << "Impossible";
            return 0;
        }
    }
    for(int i = 1; i <= m; i++) {
        if(color[i] < color[i + m]) cout << "o";
        else cout << "i";
    }
};