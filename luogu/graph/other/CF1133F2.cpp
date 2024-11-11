/**
 * @Time : 2024/5/7-10:41 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 观察用例发现 只要有一个起点是1 终点是1的环。就可以去掉一条从1出去的边而不影响连通性
  * 因此先找一找有多少个起点是1 终点是1的环 数量记为sz
  * 如果1的边数 < D，显然无法构建
  * 如果1的变数 - sz > D, 最多可以去掉sz条边，度数要求还是不满足， 但再去掉更多 无法构建生成树
  * 所以也无法构建
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
int n, m, D, marked[N] = {0};
vector<vector<int>> edge;
unordered_set<int> graph[N];
unordered_set<int> cycle;

void dfs(int v, int f) {
    marked[v] = 1;
    for(int w : graph[v]) {
        if(marked[w]) {
            if(w != f && w == 1)
                cycle.insert(v); // 表示这条边是以1为起点的一个环上的边 且一个端点是1
        } else dfs(w, v);
    }
}

void bfs(int s) {
    queue<int> queue;
    marked[s] = 1, queue.push(s);
    while(queue.size()) {
        int v = queue.front();
        for(int w : graph[v]) {
            if(!marked[w]) {
                marked[w] = 1, queue.push(w);
                edge.push_back({v, w});
            }
        }
        queue.pop();
    }
}

bool solve() {
    if(graph[1].size() < D) return false;
    dfs(1, -1);
    // 从1出去的边 最多可以去掉cycle.size()条 再去掉更多 无法构建生成树
    if(graph[1].size() - cycle.size() > D) return false;
    // 要去掉环边的数量为 remove
    int remove = graph[1].size() - D;
    while(remove-- > 0) {
        int v = *cycle.begin();
        graph[1].erase(graph[1].find(v));
        cycle.erase(cycle.begin());
    }
    memset(marked, 0, sizeof(marked));
    bfs(1);
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> D;
    for(int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        graph[v].insert(u), graph[u].insert(v);
    }
    if(solve()) {
        cout << "YES\n";
        for(auto& e : edge) {
            cout << e[0] << " " << e[1] << "\n";
        }
    } else cout << "NO";
};