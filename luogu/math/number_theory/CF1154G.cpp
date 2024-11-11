/**
 * @Time : 2024/5/10-11:03 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1154G 数论 调和级数
 */
/*
 * lcm(x, y) = x * y / gcd(x, y)
 * x和y的值域是 1e7，那么gcd(x, y) <= 1e7
 *
 * 枚举gcd 对于每个gcd来说 找到最小的拥有这个因子的数 就能确定这个gcd下最小的公倍数
 * 令v = 1e7，gcd的取值范围[1, v]，枚举gcd的取值k
 * 找以k为因子的最小两个数 单次计算 v / k 次
 * 总计算量 v (1 + 1 / 2 + 1 / 3 + ... 1 / v) = vlogv
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 5;
int n, cnt[N];
unordered_map<int, vector<int>> mp;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    int mv = 1;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        cnt[num]++, mv = max(num, mv);
        mp[num].push_back(i);
    }
    ll ans = LONG_LONG_MAX, a, b;
    for(int k = 1; k <= mv; k++) { // 枚举最大公因子gcd的值
        ll num1 = -1, num2 = -1;
        for(int i = k; i <= mv && num2 == -1; i += k) {
            if(cnt[i] > 0) {
                if(num1 == -1) {
                    num1 = i;
                    if(cnt[i] > 1) num2 = i;
                } else num2 = i;
            }
        }
        if(num2 != -1) {
            ll temp = num1 * num2 / k;
            if(temp < ans) {
                ans = temp;
                a = num1, b = num2;
            }
        }
    }
    int i = mp[a][0], j = mp[b].back();
    cout << min(i, j) << " " << max(i, j);
};