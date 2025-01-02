/**
 * @Time : 2025/1/1-10:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1571D 1800 暴力枚举 容斥定律
 */
 /*
  * 只有1000个运动员 因此暴力枚举第一名和第二名是可以的
  *
  * 容斥定律
  * 猜中1 + 猜中2 - 都中 = 两个都猜中的 + 只猜中1 + 只猜中2
  *
  * c2:两个都猜中的
  * 只猜中其中1个 = 猜中1 + 猜中2 - 2 * c2
  *
  * 预先处理猜中1的 猜中2的 都猜中的人数
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e3 + 5, mod = 998244353;
int T, n, m, first[N], last[N], f1, l1;
map<int, int> mp;

void solve() {
    int ans = 1;
    for(int f = 1; f <= n; f++) {
        for(int l = 1; l <= n; l++) {
            if(l == f || (f1 == f && l1 == l)) continue;
            int c2 = mp[f * N + l], c1 = first[f] + last[l] - 2 * c2;
            if(f1 != f && l1 != l) ans = max(ans, c2 + c1 + 1);
            else ans = max(ans, c2 + 1);
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1, f, l; i <= m; i++) {
            cin >> f >> l;
            if(i == 1) f1 = f, l1 = l;
            first[f]++, last[l]++, mp[f * N + l]++;
        }
        solve();
    }
};