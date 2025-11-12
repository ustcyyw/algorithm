/**
 * @Time : 2024/5/21-8:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1974C hashmap计数
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, M = 1e7;
ll T, n, nums[N], ans = 0;
map<ll, map<ll, int>> maps[3];
map<ll, int> cnts[3];

void cal(map<ll, int>& cnt, map<ll, map<ll, int>>& map, ll key, ll third) {
    ans += cnt[key] - map[key][third];
    cnt[key]++, map[key][third]++;
}

void solve() {
    for(int i = 1; i <= n - 2; i++) {
        ll a = nums[i], b = nums[i + 1], c = nums[i + 2];
        cal(cnts[0], maps[0], a * M + b, c);
        cal(cnts[1], maps[1], a * M + c, b);
        cal(cnts[2], maps[2], b * M + c, a);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        ans = 0;
        for(int i = 0; i < 3; i++)
            cnts[i].clear(), maps[i].clear();
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};