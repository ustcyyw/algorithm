/**
 * @Time : 2025/4/19-5:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2093E 1500 二分答案
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15;
int T, n, k, nums[N], marked[N];

bool check(int x) {
    int cnt = 0;
    for(int i = 1, j = 1; i <= n; ) {
        int sz = 0;
        while(j <= n && sz < x) {
            int num = nums[j];
            if(num < x && !marked[num]) sz++, marked[num] = 1;
            j++;
        }
        if(sz == x) cnt++;
        while(i < j) {
            if(nums[i] < x) marked[nums[i]] = 0;
            i++;
        }
        if(cnt >= k) return true;
    }
    return false;
}

void solve() {
    int lo = 0, hi = n / k + 1;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
    return 0;
}