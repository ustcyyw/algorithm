/**
 * @Time : 2024/11/8-2:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1921F 根号分治 前缀和
 */
 /*
  * 如果 d > 4e2
  * 那么每次计算 最多访问 1e5 / 4e2 = 2.5e2 个数据
  * 2e5次询问 最多有5e7次计算
  *
  * 如果 d <= 4e2
  * 预处理 对于每一个d 处理出各组点的前缀和 会将每个点便利一边
  * 最多计算 4e2 * 1e5 = 4e7 次计算
  * 预处理的这些就得找规律快速计算 可以使用前缀和
  *
  * s = 1, d = 2, k = 3
a[1] * 1 + a[3] * 2 + a[5] * 3

s = 3, d = 2, k = 3
a[3] * 1 + a[5] * 2 + a[7] * 3

s = 5, d = 2, k = 2
a[5] * 1 + a[7] * 2

s = 7, d = 2, k = 2
a[7] * 1 + a[9] * 2

s = 2, d = 3, k = 7
a2 + a5 * 2 + a8 * 3 + a11 * 4 + a14 * 5 + a17 * 6 + a20 * 7

s = 8, d = 3, k = 3
a8 + a11 * 2 + a14 * 3
先将前后缀去掉 保留第3项-第5项

a8 * 3 + a11 * 4 + a14 * 5
首相是第三项 因此减去2倍的基础前缀和 a8 * 2 + a11 * 2 + a14 * 2
得到 a8 * 1 + a11 * 2 + a14 * 3
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, M = 4e2;
int T, n, q, nums[N];
unordered_map<int, unordered_map<int, vector<ll>>> baseSum, mulSum;

void init(int d, int s) {
    vector<ll> base(1, 0ll), mul(1, 0ll);
    for(int i = s, k = 1; i <= n; k++, i += d) {
        base.push_back(base.back() + nums[i]);
        mul.push_back(mul.back() + (ll)nums[i] * k);
    }
    baseSum[d][s] = base, mulSum[d][s] = mul;
}

ll cal(int s, int d, int k) {
    ll ans = 0;
    for(int i = s, j = 1; j <= k; j++, i += d)
        ans += (ll)nums[i] * j;
    return ans;
}

void solve() {
    int m = sqrt(n);
    for(int d = 1; d <= m; d++) {
        for(int s = 1; s <= d; s++) {
            init(d, s);
        }
    }
    for(int i = 1, s, d, k; i <= q; i++) {
        cin >> s >> d >> k;
        ll ans = 0;
        if(d <= m) {
            int lo = s % d == 0 ? s / d : s / d + 1, hi = lo + k - 1;
            s = s % d == 0 ? d : s % d; // 要将s转换为完整数列起点下标
            ll temp = mulSum[d][s][hi] - mulSum[d][s][lo - 1];
            ans = temp - (ll)(lo - 1) * (baseSum[d][s][hi] - baseSum[d][s][lo - 1]);
        } else ans = cal(s, d, k);
        cout << ans << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> q;
        baseSum = {}, mulSum = {};
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};