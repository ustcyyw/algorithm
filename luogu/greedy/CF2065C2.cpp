/**
 * @Time : 2025/2/11-9:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2065C2 贪心
 */
/*
  * 非递减序列 一定是靠前的数字越小越好
  * 前一个数字经过变换后是pre 当前数字 bj - ai >= pre, bj >= pre + ai
  * 当然 当前数字也可以不进行操作
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5;
ll T, n, m, a[N];
set<ll> st;

bool solve() {
    ll pre = LONG_LONG_MIN;
    for(int i = 1; i <= n; i++) {
        ll temp = pre + a[i];
        if(st.lower_bound(temp) == st.end() && a[i] < pre)
            return false;
        if(st.lower_bound(temp) == st.end()) pre = a[i];
        else {
            if(a[i] >= pre) pre = min(a[i], *st.lower_bound(temp) - a[i]);
            else pre = *st.lower_bound(temp) - a[i];
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T--) {
        cin >> n >> m;
        st = { };
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1, b; i <= m; i++) {
            cin >> b;
            st.insert(b);
        }
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};