/**
 * @Time : 2024/5/22-8:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1249C2 状态压缩 双指针
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n;
vector<ll> nums1, nums2, arr1, arr2;

void combination(vector<ll>& nums, vector<ll>& arr) {
    int m = nums.size(), full = (1 << m) - 1;
    for(int s = 0; s <= full; s++) {
        ll sum = 0;
        for(int j = 0; j < m; j++) {
            if((1 << j) & s)
                sum += nums[j];
        }
        arr.push_back(sum);
    }
    sort(arr.begin(), arr.end());
}

int init = []() -> int {
    for(ll i = 0, num = 1; i <= 38; i++, num *= 3) {
        if(i < 19) nums1.push_back(num);
        else nums2.push_back(num);
    }
    combination(nums1, arr1), combination(nums2, arr2);
    return 0;
}();

void solve() {
    int m1 = arr1.size(), m2 = arr2.size();
    ll ans = LONG_LONG_MAX;
    for(int i = 0, j = m2 - 1; i < m1; i++) {
        while(j >= 0 && arr2[j] + arr1[i] >= n) j--;
        ans = min(ans, arr1[i] + arr2[j + 1]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        solve();
    }
};