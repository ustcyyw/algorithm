/**
 * @Time : 2024/2/7-9:49 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 5;
int T, n, k, maxV, nums[N];

bool check(int val) {
    for(int i = 1; i <= n; i++) {
        int temp = k, v = val, j = i;
        for(; j <= n && temp >= 0; j++, v--) {
            if(v <= nums[j]) return true;
            temp -= v - nums[j];
        }
    }
    return false;
}

void solve() {
    int lo = maxV, hi = 2e8;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if (check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        maxV = 0;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            maxV = max(maxV, nums[i]);
        }
        solve();
    }
};