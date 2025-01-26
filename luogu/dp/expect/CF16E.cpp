/**
 * @Time : 2025/1/25-10:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF16E 1900 动态规划 状态压缩 概率dp 刷表法
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 205, mod = 998244353;
int T, n;
long double p[20][20];

void add(vector<bool>& marked, queue<int>& queue, int s) {
    if(marked[s]) return;
    marked[s] = true, queue.push(s);
}

void solve() {
    int full = (1 << n) - 1;
    vector<long double> dp(full + 1, 0.0);
    vector<bool> marked(full + 1, false);
    queue<int> queue;
    dp[full] = 1.0, queue.push(full), marked[full] = 1;
    while(!queue.empty()) {
        int s = queue.front(), cnt = __builtin_popcount(s);
        long double base = 1.0 / (cnt * (cnt - 1) / 2);
        queue.pop();
        for(int i = 0; i < n; i++) {
            int t1 = 1 << i;
            if((t1 & s) == 0) continue;
            for(int j = i + 1; j < n; j++) {
                int t2 = 1 << j;
                if((t2 & s) == 0) continue;
                dp[s ^ t2] += dp[s] * base * p[i][j]; // i赢
                add(marked, queue, s ^ t2);
                dp[s ^ t1] += dp[s] * base * p[j][i]; // j赢
                add(marked, queue, s ^ t1);
            }
        }
    }
    for(int i = 0; i < n; i++)
        cout << dp[1 << i] << " ";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                cin >> p[i][j];
        }
        solve();
    }
};