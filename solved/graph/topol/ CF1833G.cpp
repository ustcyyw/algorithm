/**
 * @Time : 2024/9/5-9:39 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1833G 拓扑排序
 */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, degree[N], cnt[N], marked[N];
set<int> ans;
vector<vector<pair<int, int>>> graph;

bool solve() {
    if(n % 3 != 0) return false;
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 1) queue.push(i);
    while(!queue.empty()) {
        int sz = queue.size();
        while(sz-- > 0) {
            int v = queue.front(); queue.pop();
            marked[v] = 1;
            if(cnt[v] > 3) return false;
            if(cnt[v] == 3) { // 进行切割
                cnt[v] = 0;
                for(auto& p : graph[v]) {
                    if(!marked[p.first]) ans.insert(p.second);
                }
            }
            for(auto& p : graph[v]) {
                int w = p.first;
                cnt[w] += cnt[v];
                if(--degree[w] == 1) queue.push(w);
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        graph.assign(n + 1, {}), ans = {};
        fill(degree, degree + n + 1, 0), fill(cnt, cnt + n + 1, 1);
        fill(marked, marked + n + 1, 0);
        for(int i = 1, v, w; i < n; i++){
            cin >> v >> w;
            graph[v].push_back({w, i}), graph[w].push_back({v, i});
            degree[v]++, degree[w]++;
        }
        if(!solve()) cout << "-1\n";
        else {
            cout << ans.size() << "\n";
            for(int id : ans)
                cout << id << " ";
            cout << "\n";
        }
    }
};