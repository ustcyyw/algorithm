/**
 * @Time : 2025/1/22-8:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF9E 2300 图论 拓扑排序 贪心 dfs
 */
 /*
  * 只能有一个环 并且这个环要包含所有结点
  * 先考虑一些特殊情况
  * 1. 只有一个结点 如果有边 只能有一条 那就是自环
  * 2. 多于一个结点 存在自环的话 还要有一条包括所有结点的环 就不止一个环了
  * 其余情况下 得考虑图中是否有环
  * 可以进行拓扑排序进行检查 但是要注意 有些结点可能没有边 在拓扑时也可以当起点
  * 在拓扑校验通过后 对于图中没有环的情况下
  * 此时图中的结点存在1个或者多个分量中 要最终成环 就需要将这些分量连接起来
  * 因为这个环要包含所有结点 因此一个分量只能是一个单链条
  * 要求字典序最小的加边方案 就按分量的结点编号排序 然后依次连接
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2505, mod = 998244353;
int T, n, m, edges[N][2], degree[51], marked[51];
vector<int> graph[51];

int topol_bfs() {
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] <= 1) queue.push(i);
    int cnt = 0;
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        cnt++;
        for(int w : graph[v])
            if(--degree[w] == 1) queue.push(w);
    }
    return cnt;
}

int check() {
    if(n == 1 && m > 1) return -1;
    // 如果顶点超过1个 并且存在自环 那就错误了
    if(n > 1) {
        for(int i = 1; i <= m; i++)
            if(edges[i][0] == edges[i][1]) return -1;
    }
    int cnt = topol_bfs();
    // cnt = 0 说明图中所有点都在环中 或者压根没有边
    if(cnt == 0 && m == n) return 1; // 刚好就有一个包含所有结点的环
    if(cnt == 0 && m > n) return -1; // 图中所有点都在环中 并且边数超过m 那一定有多于1个环
    if(cnt != n && cnt != 0) return -1; // 图中部分点在一个环中 如果将所有点再连到一个环中 图有多于1个环
    return 0;
}

void dfs(vector<int>& arr, int v) {
    marked[v] = 1;
    if(graph[v].size() == 1) arr.push_back(v);
    for(int w : graph[v]) {
        if(marked[w]) continue;
        dfs(arr, w);
    }
}

struct cmp{
    bool operator()(vector<int>& a, vector<int>& b){
        return a[0] > b[0];
    }
};
priority_queue<vector<int>, vector<vector<int>>, cmp> pq;

void solve() {
    for(int i = 1; i <= n; i++) {
        if(marked[i]) continue;
        vector<int> arr;
        if(graph[i].empty()) arr = {i, i};
        else dfs(arr, i);
        if(arr.size() > 2) {
            cout << "NO\n";
            return;
        }
        if(arr[0] > arr[1]) swap(arr[0], arr[1]);
        pq.push(arr);
    }
    cout << "YES\n";
    cout << pq.size() << "\n";
    while(!pq.empty()) {
        vector<int> a = pq.top(); pq.pop();
        if(pq.empty()) {
            cout << a[0] << " " << a[1];
            break;
        }
        vector<int> b = pq.top(); pq.pop();
        cout << a[0] << " " << b[0] << "\n";
        vector<int> arr = {a[1], b[1]};
        if(arr[0] > arr[1]) swap(arr[0], arr[1]);
        pq.push(arr);
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> m;
        for(int i = 1, v, w; i <= m; i++) {
            cin >> v >> w;
            edges[i][0] = v, edges[i][1] = w;
            degree[v]++, degree[w]++;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        int flag = check();
        if(flag == -1) cout << "NO";
        else if(flag == 1) cout << "YES\n" << 0;
        else solve();
    }
};