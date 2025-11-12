/**
 * @Time : 2024/4/11-3:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 塔的半径最多只允许用一次 塔的攻击力 < 500，格子最多2500个
  * 而且怪兽生命值的增长是指数级别。比如如果有塔的半径是20，怪兽生命值就已经有 3486784401 这不可能消灭
  * 因此估算一个大概的半径 超过R就会导致怪兽生命值一定超出伤害
  * 取R = 12。使用了哪些半径可以用二进制数表示
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1e5 + 5, R = 12, U = (1 << R) - 1;
int T, n, m, k, power[2505][R], pre[U + 5], dp[U + 5];
string grid[51];

void solve() {
    fill(pre, pre + U, -1e9);
    fill(dp, dp + U, -1e9);
    pre[0] = 0;
    for(int i = 1; i <= k; i++) {
        for(int s = 0; s <= U; s++) {
            dp[s] = pre[s]; // 当前塔半径为0的状态
            for(int r = 0; r < R; r++) {
                int t = 1 << r;
                if(t & s) dp[s] = max(dp[s], pre[t ^ s] + power[i][r]);
            }
        }
        swap(dp, pre);
    }
    ll ans = 0;
    // 枚举半径使用状态
    for(int s = U; s; s = (s - 1) & U) {
        ll sum = 0;
        for(int r = 0, p = 1; r < R; r++) {
            p *= 3;
            if((1 << r) & s) sum += p;
        }
        ans = max(ans, pre[s] - sum);
    }
    cout << ans << "\n";
}
// 计算每个塔相应的半径能造成多少伤害
void init(int id, int x, int y, int p) {
    for(int r = 1; r <= R; r++) {
        int cnt = 0, r2 = r * r;
        for(int i = max(1, x - r); i <= min(n, x + r); i++) {
            for(int j = max(1, y - r); j <= min(m, y + r); j++) {
                int dx = i - x, dy = j - y;
                if(dx * dx + dy * dy <= r2 && grid[i][j] == '#')
                    cnt++;
            }
        }
        power[id][r - 1] = cnt * p;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> k;
        for(int i = 1; i <= n; i++) {
            cin >> grid[i];
            grid[i] = '.' + grid[i];
        }
        for(int i = 1, x, y, p; i <= k; i++) {
            cin >> x >> y >> p;
            init(i, x, y, p);
        }
        solve();
    }
};