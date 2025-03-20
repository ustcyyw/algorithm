/**
 * @Time : 2025/3/19-1:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF954G 2000 二分答案 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e4 + 15, mod = 1e9 + 7;
ll T, n, r, k;
vector<ll> nums;

bool check(ll val) {
    vector<ll> arr = nums;
    ll cnt = 0;
    for(ll i = 1, sum = 0; i <= n; i++) {
        sum += arr[i];
        if(sum >= val) continue;
        ll add = val - sum;
        sum = val, arr[min(n, i + 2 * r) + 1] -= add;
        cnt += add;
        if(cnt > k) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> r >> k;
    nums.assign(n + 2, 0);
    for(int i = 1, v; i <= n; i++) {
        cin >> v;
        ll lo = max(1ll, i - r), hi = min(n, i + r);
        nums[lo] += v, nums[hi + 1] -= v;
    }
    ll lo = 0, hi = 2e18;
    while(lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo;
}