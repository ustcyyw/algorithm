/**
 * @Time : 2024/5/25-2:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1731C 正难则反
 */
/*
 * 一个数的因子是成对出现的 除非他是完全平方数
 * 小于等于400000的数中 完全平方数只有650个
 * 2e5 * 650 = 13e7
 * 用总的 - 不满足条件的 （正难则反）
 * 不满足条件就是指 区间异或为完全平方数
 * cur ^ pre = a, pre = a ^ cur 所以可以用hash表计数
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
ll T, n, nums[N];
vector<int> arr;

int init = []() -> int {
    for(int i = 0; i * i < 2 * N; i++)
        arr.push_back(i * i);
    return 0;
}();

void solve() {
    int cnt[4 * N] = {0};
    cnt[0] = 1;
    ll ans = 0, cur = 0;
    for(int i = 1; i <= n; i++) {
        cur ^= nums[i];
        for(int a : arr)
            ans += cnt[cur ^ a];
        cnt[cur]++;
    }
    cout << n * (n + 1) / 2 - ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};