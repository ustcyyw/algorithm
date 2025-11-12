/**
 * @Time : 2024/4/9-10:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 单边计算不行 那就双边走。类似于多源bfs的思路 可以减少很多计算
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 2e5 + 5;
ll n, m, grid[25][25], k, len;
unordered_map<ll, ll> dp1[25][25], dp2[25][25];

void trans(unordered_map<ll, ll>& cur, unordered_map<ll, ll>& pre, ll num) {
    for(auto& [v, cnt] : pre) {
        cur[num ^ v] += cnt;
    }
}

void way1() {
    dp1[1][1][grid[1][1]] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(i == 1 && j == 1) continue;
            if(i - 1 + j - 1 > len) continue;
            trans(dp1[i][j], dp1[i - 1][j], grid[i][j]);
            trans(dp1[i][j], dp1[i][j - 1], grid[i][j]);
        }
    }
}

void way2() {
    dp2[n][m][grid[n][m]] = 1;
    for(int i = n; i >= 1; i--) {
        for(int j = m; j >= 1; j--) {
            if(i == n && j == m) continue;
            if(m - i + n - j > len) continue;
            trans(dp2[i][j], dp2[i + 1][j], grid[i][j]);
            trans(dp2[i][j], dp2[i][j + 1], grid[i][j]);
        }
    }
}

void cal(unordered_map<ll, ll>& map1, unordered_map<ll, ll>& map2, ll& ans) {
    for(auto& [v1, cnt1] : map1) {
        ans += cnt1 * map2[k ^ v1];
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    len = (n + m - 2) / 2;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++)
            cin >> grid[i][j];
    }
    if(n == 1 && m == 1) {
        cout << (grid[1][1] == k);
        return 0;
    }
    way1(), way2();
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int j = len + 2 - i;
        if(j >= 1 && j <= m) {
            if(i + 1 <= n) cal(dp1[i][j], dp2[i + 1][j], ans);
            if(j + 1 <= m) cal(dp1[i][j], dp2[i][j + 1], ans);
        }
    }
    cout << ans;
};