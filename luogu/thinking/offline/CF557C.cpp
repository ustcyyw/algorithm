/**
 * @Time : 2025/3/14-11:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF557C 1900 离线思维 暴力枚举 排序
 */
/*
 * 枚举长度最大的桌腿 比他大的都要移除
 * 比他小的 要移除到少于他 因为d比较小 所以可以用桶排序
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 1e9 + 7;
int T, n, d[205], legs[N][2];
map<int, vector<int>> mp;

ll deleteLeg(int count) {
    if(count <= 0) return 0;
    ll ans = 0;
    for(int i = 1; i <= 200 && count; i++) {
        int t = min(count, d[i]);
        count -= t, ans += t * i;
    }
    return ans;
}

void solve() {
    ll ans = LONG_LONG_MAX, sum = 0;
    for(auto it = mp.rbegin(); it != mp.rend(); it++) {
        vector<int> cds = it->second;
        int cc = cds.size(), left = cc - 1, del = n - cc - left;
        for(int cd : cds)
            d[cd]--;
        ans = min(ans, deleteLeg(del) + sum);
        n -= cc;
        sum += accumulate(cds.begin(), cds.end(), 0ll);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> legs[i][0];
        for(int i = 0; i < n; i++) {
            cin >> legs[i][1];
            d[legs[i][1]]++;
        }
        for(int i = 0; i < n; i++)
            mp[legs[i][0]].push_back(legs[i][1]);
        solve();
    }
}