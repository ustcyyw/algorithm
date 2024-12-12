/**
 * @Time : 2024/12/11-2:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1926G 1900 动态规划 树型dp
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n;
string s;
vector<vector<int>> graph, cache;

int dfs(int v, int f, char type) {
    if(s[v] != 'C' && s[v] != type) return 1e9; // 无法强行改变非c的类型
    if(f != -1 && graph[v].size() == 1) return 0;
    int flag = type == 'S';
    if(cache[v][flag] != -1) return cache[v][flag];
    int ans = 0;
    for(int w : graph[v]) {
        if(w == f) continue;
        int c1 = dfs(w, v, type), c2 = dfs(w, v, type == 'S' ? 'P' : 'S') + 1;
        ans += min(c1, c2);
    }
    return cache[v][flag] = ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        graph.assign(n + 1, {}), cache.assign(n + 1, vector(2, -1));
        for(int i = 2, num; i <= n; i++) {
            cin >> num;
            graph[i].push_back(num), graph[num].push_back(i);
        }
        cin >> s;
        s = '.' + s;
        if(s[1] == 'C') cout << min(dfs(1, -1, 'S'), dfs(1, -1, 'P')) << "\n";
        else cout << dfs(1, -1, s[1]) << "\n";
    }
};