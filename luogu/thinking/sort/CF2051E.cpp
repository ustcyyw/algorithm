/**
 * @Time : 2024/12/24-9:30 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2051E 1613 排序 暴力枚举 双指针
 */
 /*
  * 枚举这些分界价格
  *
  * 高过ai时 购买 但是要将那个人添加到差评池子
  * 高过bi时 将差评池子中的人移除 并且将其记为不买的人
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, k;
vector<int> prices;
vector<vector<int>> as, bs;

void solve() {
    sort(prices.begin(), prices.end());
    sort(as.begin(), as.end()), sort(bs.begin(), bs.end());
    ll sum = 0, out = 0;
    unordered_set<int> bad;
    for(int i = 0, j1 = 0, j2 = 0; i < 2 * n; i++) {
        int p = prices[i];
        while(j1 < n && as[j1][0] < p)
            bad.insert(as[j1++][1]);
        while(j2 < n && bs[j2][0] < p)
            bad.erase(bs[j2++][1]), out++;
        if(bad.size() <= k) {
            ll temp = (ll)(n - out) * p;
            if(temp > sum) sum = temp;
        }
    }
    cout << sum << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> k;
        prices = {}, as = {}, bs = {};
        for(int i = 1, a; i <= n; i++) {
            cin >> a;
            prices.push_back(a), as.push_back({a, i});
        }
        for(int i = 1, b; i <= n; i++) {
            cin >> b;
            prices.push_back(b), bs.push_back({b, i});
        }
        solve();
    }
};