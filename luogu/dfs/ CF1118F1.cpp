/**
 * @Time : 2024/5/6-11:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
int n, ans = 0, bc = 0, rc = 0, blue[N], red[N];
vector<int> graph[N];

void dfs(int v, int f) {
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v);
        blue[v] += blue[w], red[v] += red[w];
        int bf = bc - blue[w], br = rc - red[w];
        if((blue[w] == 0 || red[w] == 0 ) && (bf == 0 || br == 0))
            ans++;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, color; i <= n; i++) {
        cin >> color;
        if(color == 1) bc++, blue[i] = 1;
        if(color == 2) rc++, red[i] = 1;
    }
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    dfs(1, -1);
    cout << ans;
};