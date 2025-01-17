/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
 /*
  * 只要有一堆石头 > 其它堆石头之和 那么先手一直拿这一堆石头就赢了
所以双方在过程中不会让某一堆石头特别多 都会想均匀地拿石头
一定会将所有石头都拿完 那么
有奇数个石头 先手方多拿一个 然后后手方没得拿就输了
有偶数个石头 双方拿一样多的 后手方最后一次拿了之后先手方就没有石头了
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