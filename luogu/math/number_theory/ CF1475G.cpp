/**
 * @Time : 2024/7/8-11:31 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1475G 数论 动态规划
 */
 /*
  * 注意 2e5这个大小范围内的数 因子个数并不多
  * 可以枚举最大的数 然后考虑它的因子里面再选一个数
  * 那这个因子就是当前考虑到的最大数 继续选它的一个因子 动态规划
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, cnt[N], cache[N], maxVal;

int dfs(int num) {
    if(num == 1) return cnt[1];
    if(cache[num] != -1) return cache[num];
    int res = 0;
    for(int i = 1; i <= sqrt(num); i++) {
        if(num % i == 0) {
            res = max(dfs(i), res);
            if(i * i != num && i != 1) res = max(dfs(num / i), res);
        }
    }
    res += cnt[num];
    return cache[num] = res;
}

void solve() {
    int ans = 0;
    for(int i = 1; i <= maxVal; i++) {
        if(cnt[i]) ans = max(dfs(i), ans);
    }
    cout << n - ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        memset(cnt, 0, sizeof(cnt));
        fill(cache, cache + N - 1, -1);
        maxVal = 0;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            cnt[num]++, maxVal = max(maxVal, num);
        }
        solve();
    }
};