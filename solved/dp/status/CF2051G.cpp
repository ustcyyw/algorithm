/**
 * @Time : 2024/12/24-9:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2051G 2231 动态规划 状态压缩dp 旅行商问题
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, q, id, full, shrink[N], len[21], dis[21][21]; // dis[i][j]标识i在j的前面 初距离是多少才不会互相碰到
int cache[1 << 20][20];
char ope;

void init() {
    fill(len, len + n + 1, 0), fill(shrink, shrink + n + 1, 0);
    for(int t = 1; t <= q; t++) {
        cin >> id >> ope;
        id--;
        if(ope == '+') { // 影响id放在别人左边的距离
            len[id]++;
            for(int j = 0; j < n; j++)
                dis[id][j] = max(dis[id][j], len[id] - shrink[j]);
        } else shrink[id]++;
    }
}

int dfs(int s, int pre) {
    if(s == 0) return 0;
    if(cache[s][pre] != -1) return cache[s][pre];
    int ans = INT_MAX;
    for(int i = 0; i < n; i++) {
        int t = 1 << i;
        if((s & t) == 0) continue;
        ans = min(ans, dis[i][pre] + dfs(s ^ t, i));
    }
    return cache[s][pre] = ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> q;
        full = (1 << n) - 1;
        memset(cache, -1, sizeof(cache));
        init();
        int ans = INT_MAX;
        for(int i = 0; i < n; i++) {
            ans = min(ans, len[i] + n + dfs(full ^ (1 << i), i));
        }
        cout << ans;
    }
};