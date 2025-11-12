/**
 * @Time : 2024/7/7-1:04 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1454E 图论 基环树 数学
 */
 /*
  * 明显n个结点和n条边 保证连通的情况下 一定有且仅有一个环
  * 环中的元素：假设有cycle个 找规律发现其能贡献的路线有 cycle * (cycle - 1)
  * 不在环中的元素：
  * 也就是枝条 按枝条与环的交点结点分组 因为每个组内的元素合在一起看，可以等价为一条元素个数相同的单链条
  * 链条长度为 num, 那么链条内部的路线有 num * (num - 1) / 2
  * 但是考虑到链条还可以到环内的元素，逆时针和顺时针走简单路线分别可以再到达 cycle - 1个元素
  * 这部分的贡献为 (num - 1) * (cycle - 1) * 2
  * 这里 num - 1是扣除在环中也在链条中的那个结点 也就是环与枝条的交点
  *
  * 还要考虑不同组枝条之间的路径，可以通过环逆时针或者顺时针地到达 为了避免重复
  * 可以用当前枝条数目 (num - 1) * 前面组别的颜色个数sum * 2
  * 更新sum时也要注意 sum += num - 1
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, degree[N], cycle, marked[N];
ll ans;
vector<vector<int>> graph;

void find_cycle() {
    cycle = n;
    queue<int> queue;
    for(int i = 1; i <= n; i++) {
        if(degree[i] == 1) queue.push(i);
    }
    while(!queue.empty()) {
        int v = queue.front(); queue.pop();
        marked[v] = 1, cycle--;
        for(int w : graph[v]) {
            if(--degree[w] == 1) queue.push(w);
        }
    }
    ans += (ll)cycle * (cycle - 1);
}

int dfs(int v, int f) {
    int cnt = 1;
    for(int w : graph[v]) {
        if(w == f || marked[w] != 1) continue;
        cnt += dfs(w, v);
    }
    return cnt;
}

// 找到环中结点挂的枝条上的结点数目
vector<int> find_path() {
    vector<int> arr;
    for(int i = 1; i <= n; i++) {
        if(marked[i] == 1) continue;
        int cnt = dfs(i, -1);
        if(cnt > 1) arr.push_back(dfs(i, -1));
    }
    return arr;
}

void solve() {
    find_cycle();
    vector<int> arr = find_path();
    for(ll i = 0, sum = 0; i < arr.size(); i++) {
        ll num = arr[i];
        ans += num * (num - 1) / 2 + (num - 1) * sum * 2 + (num - 1) * (cycle - 1) * 2;
        sum += num - 1;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        graph.assign(n + 1, {}), ans = 0;
        fill(degree + 1, degree + n + 1, 0), fill(marked + 1, marked + n + 1, 0);
        for(int i = 1, v, w; i <= n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
            degree[v]++, degree[w]++;
        }
        solve();
    }
};