/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, p[N], q[N], mp1[N], mp2[N];

void stdIn(int* arr, int* mp) {
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
        mp[arr[i]] = i;
    }
}
// 计算mex为1的数组
ll cal1() {
    vector<vector<int>> arr1 = {{1, mp1[1] - 1},{mp1[1] + 1, n}};
    vector<vector<int>> arr2 = {{1, mp2[1] - 1},{mp2[1] + 1, n}};
    ll ans = 0;
    for(auto& t1 : arr1) {
        int lo1 = t1[0], hi1 = t1[1];
        for(auto& t2 : arr2) {
            int lo2 = t2[0], hi2 = t2[1];
            int lo = max(lo1, lo2), hi = min(hi1, hi2);
            if(lo > hi) continue;
            ll m = hi - lo + 1;
            ans += m * (m + 1) / 2;
        }
    }
    return ans;
}

void solve() {
    ll ans = cal1();
    int l1 = mp1[1], r1 = mp1[1], l2 = mp2[1], r2 = mp2[1];
    for(int val = 2; val <= n + 1; val++) { // 枚举mex的值
        int i = mp1[val], j = mp2[val];
        // mex值为val 就要过滤掉这个数 这个数在必选区间[l,r]外 才有可能有符合条件的数组
        if((i < l1 || i > r1) && (j < l2 || j > r2)) {
            int lo1, hi1, lo2, hi2;
            if(i < l1) lo1 = i + 1, hi1 = n;
            else lo1 = 1, hi1 = i - 1;
            if(j < l2) lo2 = j + 1, hi2 = n;
            else lo2 = 1, hi2 = j - 1;
            ll lor = max(r1, r2), hir = min(hi1, hi2);
            ll lol = max(lo1, lo2), hil = min(l1, l2);
            if(lol <= hil && lor <= hir)
                ans += (hil - lol + 1) * (hir - lor + 1);
        }
        l1 = min(l1, i), r1 = max(r1, i);
        l2 = min(l2, j), r2 = max(r2, j);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        stdIn(p, mp1), stdIn(q, mp2);
        solve();
    }
};