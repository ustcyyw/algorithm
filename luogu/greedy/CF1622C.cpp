/**
 * @Time : 2024/3/13-5:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 贪心
 * 1.在有两个数不同的情况下 交换操作优于或者等价于减操作
 * 2.交换应该用最小数和较大的数进行 这样减少的更多
 * 3.如果已经确定了要交换哪些数 以及减操作的次数 那么一定是在最小数上完成所有减操作 再进行交换
 *
 * 排序后枚举交换多少个较大的数 计算此时需要多少次减操作
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 2e5 + 5;
ll T, n, k, nums[N], sum[N] = {0}, mv;

ll solve() {
    sort(nums + 1, nums + n + 1);
    mv = nums[1];
    for(int i = 2; i <= n; i++)
        sum[i] = sum[i - 1] + nums[i];
    ll res = max(sum[n] + mv - k, 0ll); // 只使用减操作
    if(res == 0) return 0;
    for(int i = n; i > 1; i--) {
        ll m = n - i + 2, red = k - sum[i - 1];
        ll x = red / m;
        if(x * m + sum[i - 1] > k) x -= 1;
        if(x >= mv) return min(res, m - 1);
        res = min(res, m - 1 + mv - x);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        sum[0] = 0;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    }
};