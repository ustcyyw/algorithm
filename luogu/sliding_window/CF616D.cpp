/**
 * @Time : 2025/2/13-10:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF616D 1600 滑动窗口
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5, mod = 998244353;
int T, n, k, nums[N], cnt[(int)1e6 + 5];

void solve() {
    int len = 0, l, r;
    for(int i = 1, j = 1, m = 0; j <= n; j++) {
        cnt[nums[j]]++;
        if(cnt[nums[j]] == 1) m++;
        while(m > k) {
            cnt[nums[i]]--;
            if(cnt[nums[i]] == 0) m--;
            i++;
        }
        if(j - i + 1 > len)
            len = j - i + 1, l = i, r = j;
    }
    cout << l << " " << r;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};