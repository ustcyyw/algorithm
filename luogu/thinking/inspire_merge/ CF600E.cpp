/**
 * @Time : 2024/4/4-11:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1e5 + 5;
// mf[i]: 子树i中颜色出现的最大频率
// mapId[N]:存储子树i的颜色信息的map对应的编号 mp[mapId[i]]就是该子树的颜色信息
int n, colors[N], mf[N], mapId[N];
ll ans[N];
map<int, int> mp[N]; // 记录颜色及出现次数的map集合
vector<int> graph[N]; // 单个case的情况 就不用管初始化

void dfs(int v, int f) {
    mapId[v] = v;
    mp[v][colors[v]] = 1;
    ans[v] = colors[v], mf[v] = 1;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v); // 先将子结点计算完毕 再在父结点合并
        // 子树记录的颜色信息更多时 要将当前树map合并到子树的map中去 启发式合并
        if(mp[mapId[v]].size() < mp[mapId[w]].size()) {
            swap(mapId[v], mapId[w]); // 让mapId[v]指向子树w的那个map，子树w的指向当前map 为后续统一写法做准备
            mf[v] = mf[w]; // 相应的颜色最大频次、颜色和都要先变为w子树的
            ans[v] = ans[w];
        }
        map<int, int> &cur = mp[mapId[v]], &son = mp[mapId[w]];
        for(auto& [c, val] : son) {
            cur[c] += val;
            if(cur[c] > mf[v]) mf[v] = cur[c], ans[v] = 0;
            if(mf[v] == cur[c]) ans[v] += c;
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> colors[i];
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    dfs(1, -1);
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
};