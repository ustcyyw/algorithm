/**
 * @Time : 2024/7/2-10:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1385C 二分 贪心
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, nums[N];

bool check(int len) {
    for(int i = len + 1, j = n, pre = -1; i < j; ) {
        if(nums[i] < nums[j]) {
            if(nums[i] < pre) return false;
            pre = nums[i++];
        } else  {
            if(nums[j] < pre) return false;
            pre = nums[j--];
        }
    }
    return true;
}

void solve() {
    int lo = 0, hi = n - 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};