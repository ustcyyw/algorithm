/**
 * @Time : 2024/9/19-4:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1872G 数学 暴力枚举
 */
/*
  *
2 ^ 18 = 262144 = 2.6e5
也就是数组中如果出现18个2 把所有2选进去就能保证更好
更一般地 如果 2 ^ k >= n 那么只要把所有2选进去 一定更好
并且如果还有其它数大于2 那么选择进去增加得更多

将所有非1的数下标记录下 如果超过18个数 直接全选即可
如果不超过18个数 可以累乘 如果成绩超过数组元素之和 也按全选
否则（累乘最大不超过1e9 * 2e5 可以用longlong存放数据） 可以暴力计算最大值 枚举l和r
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, nums[N], sum[N];
vector<int> arr;

bool check() {
    if(arr.size() >= 18) return true;
    __int128 mul = 1, t = 2e14 + 5;
    for(int idx : arr) {
        mul *= nums[idx];
        if(mul >= t) return true;
    }
    return false;
}

void solve() {
    if(check()) {
        cout << arr[0] << " " << arr.back() << "\n";
        return;
    }
    // 枚举要取的边界 l r
    ll lo = 1, hi = 1, val = sum[n];
    for(int i = 0; i < arr.size(); i++) {
        ll l = arr[i], mul = nums[l];
        for(int j = i + 1; j < arr.size(); j++) {
            ll r = arr[j];
            mul *= nums[r];
            ll t = sum[l - 1] + mul + sum[n] - sum[r];
            if(t > val) val = t, lo = l, hi = r;
        }
    }
    cout << lo << " " << hi << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        arr = {};
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            sum[i] = sum[i - 1] + nums[i];
            if(nums[i] > 1) arr.push_back(i);
        }
        solve();
    }
};