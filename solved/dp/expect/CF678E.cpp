/**
 * @Time : 2025/2/16-9:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF678E 2200 动态规律 状态压缩 概率型dp 参考了答案
 */
/*
  * cache[s]: 人的存活状态为s时，0号玩家获胜的最大概率
  * s = 1, 只剩0这个玩家 其获胜概率为1
  * s 为偶数 0这个玩家已经死了 获胜概率为0
  * 状态转移：就像模拟决斗流程 因为0号玩家可以选择决斗的人
  * 挑选任意两个活着的人(i,j)决斗，要在所有(i,j)的组中选最大概率
  * 但是它不能决定决斗的两个人谁赢 i或者j 都可能活下来 要以概率计算
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 1e9 + 7;
int T, n, full;
ld p[20][20];
vector<ld> cache;

ld dfs(int s) {
    if(s == 1) return 1;
    if(s % 2 == 0) return 0;
    if(cache[s] != -1.0) return cache[s];
    ld ans = 0;
    for(int i = 0; i < n; i++) {
        int t1 = 1 << i;
        if(!(t1 & s)) continue;
        for(int j = 0; j < n; j++) {
            int t2 = 1 << j;
            if(!(t2 & s)) continue;
            ans = max(ans, dfs(s ^ t1) * p[j][i] + dfs(s ^ t2) * p[i][j]);
        }
    }
    return cache[s] = ans;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n;
        full = (1 << n) - 1;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                cin >> p[i][j];
        }
        cache.assign(full + 1, -1.0);
        cout << dfs(full);
    }
};