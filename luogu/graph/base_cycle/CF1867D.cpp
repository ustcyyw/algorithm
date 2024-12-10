/**
 * @Time : 2024/12/9-2:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1867D 1800 构造 图论 基环树深林
 */
/*
  * 根据操作规则 l的意义就是指明某个位置指向某一个数
  * 而且数的大小限制在[1,n]之间 也就是说可以当成是某个位置指向某个位置
  * 而b[i]数组也可以认为是下标指向另外一个位置
  * 可以将l和b都看成是给出了一组有向边构成了一个图
  *
  * 必然会有至少一个环 基环树深林
  * k于环的长度等刚好相等 l序列就是环上的值
  * 数枝上的构造 对于树枝部分按拓扑顺序依次填写 直到填到环上的位置
  * 如果还有空余 随便填环上的值即可 因为在构造环的时候会覆盖错误的值
  *
  * 特判 k=1 的时候 要求每个b[i] = i，也就是全为自环
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, k, nums[N], degree[N], marked[N];
vector<vector<int>> graph;

void topol_bfs() {
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        marked[v] = 1;
        for(int w : graph[v])
            if(--degree[w] == 0) queue.push(w);
    }
}

int dfs(int v) {
    marked[v] = 1;
    int w = graph[v][0];
    return marked[w] ? 1 : 1 + dfs(w);
}

bool solve() {
    if(k == 1) {
        for(int i = 1; i <= n; i++)
            if(nums[i] != i) return false;
        return true;
    }
    topol_bfs();
    for(int i = 1; i <= n; i++) {
        if(marked[i]) continue;
        if(k != dfs(i)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> k;
        graph.assign(n + 1, {});
        fill(degree, degree + n + 1, 0), fill(marked, marked + n + 1, 0);
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            graph[i].push_back(nums[i]), degree[nums[i]]++;
        }
        cout << (solve() ? "YES" : "NO") << "\n";
    };
};