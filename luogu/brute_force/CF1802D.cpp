/**
 * @Time : 2025/1/16-9:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1802D 1800 暴力枚举 模拟
 */
 /*
  * 假设第一个人的最大价值的礼物是 x
  * 那么所有小于x的ai都可以让第一个人拿着 当然也可以让给第二个人买
  * 而ai > x的商店就都是第二个人买走了对应的bi
  *
  * 枚举第一个人的最大价值礼物
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n;
multiset<int> st1, st2;
vector<vector<int>> stores;

void solve() {
    int ans = INT_MAX;
    for(int i = 0; i < n; i++) {
        st2.erase(st2.find(stores[i][1]));
        int m1 = stores[i][0], m2 = st2.empty() ? (int)-1e9 : *st2.rbegin();
        ans = min(ans, abs(m2 - m1));
        auto it = st1.lower_bound(m1);
        if(it != st1.end() && *it > m2)
            ans = min(ans, abs(*it - m1));
        if(it != st1.begin() && *(--it) > m2)
            ans = min(ans, abs(*it - m1));
        st1.insert(stores[i][1]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n;
        stores = {}, st1 = {}, st2 = {};
        for(int i = 0, a, b; i < n; i++) {
            cin >> a >> b;
            st2.insert(b);
            stores.push_back({a, b});
        }
        sort(stores.begin(), stores.end());
        solve();
    }
};