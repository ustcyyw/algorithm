/**
 * @Time : 2024/4/20-11:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 如果某个点到根的距离 > 2
 * 要么它的儿子或者直接父亲接条边到根结点 要么它自己接条边到根结点
 * 但是完全没必要通过一条边接其它结点 如果这个结点非添加一条边 那干嘛不直接接根结点呢
 *
 * 某个结点的状态会影响父亲或者儿子 所以定义状态的时候只定义某个结点是否添加边 dp的时候会有后效性
 * 因此定义状态要再考虑加一个维度，就是当前结点是否已经距离根 <= 2
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, depth[N];
vector<int> graph[N];
vector<vector<vector<int>>> cache;

void dfs1(int v, int f) {
    if(f != -1) depth[v] = depth[f] + 1;
    for(int w : graph[v])
        if(w != f) dfs1(w, v);
}
// add 表示当前结点是否添加了一条边；s 表示当前结点是否已经到达根结点距离 <= 2
int dfs2(int v, int f, int add, int s) {
    if(graph[v].size() == 1 && f != -1) return add || (!s);
    if(cache[v][add][s] != -1) return cache[v][add][s];
    int ans = add, diff = -1e9;
    for(int w : graph[v]) {
        if(w == f) continue;
        if(add || depth[v] <= 1) { // 当前结点添加了边 或者其深度 <= 1 那么其子结点到根的距离一定 <= 2
            ans += min(dfs2(w, v, 1, 1), dfs2(w, v, 0, 1));
        } else { // 当前结点不添加边 先计算 默认儿子结点可以加边可以不加边
            int t1 = dfs2(w, v, 0, 0), t2 = dfs2(w, v, 1, 1);
            ans += min(t1, t2);
            if(!s) { // 当前结点到达根的距离 > 2，要求至少要有一个子结点添加边
                diff = max(diff, t1 - t2); // 默认是子结点不加边 但是记录t1-t2最大值
            }
        }
    }
    if(!add && depth[v] > 2 && !s) { // 当前结点到达根的距离 > 2
        // 如果diff < 0，t1都是比t2要小的，在默认计算中都选了子结点不加边，但是现在要换一个子结点添加边
        if(diff < 0) ans -= diff;
    }
    return cache[v][add][s] = ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    dfs1(1, -1);
    cache.assign(n + 1, vector(2, vector(2, -1)));
    cout << dfs2(1, -1, 0, 1);
};