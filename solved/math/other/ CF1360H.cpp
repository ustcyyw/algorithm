/**
 * @Time : 2024/6/27-4:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1360H 数学
 */
 /*
  * 类似CF1144E 都是非10进制数下的找中位数相关的问题
  * 字典序排列顺序与数值大小顺序是一致的
  * 只不过这题还要删除一些数 原本中位数左边被删了几个数 右边被删了几个数
  * 进行相应的移动来弥补 因为删除的数总共才100个 所以移动的距离不会很远 时间复杂度足够
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, m;
string t;
vector<ll> del;
set<ll> st;

ll to_num(string& s) {
    ll ans = 0, temp = 1;
    for(int i = s.size() - 1; i >= 0; i--) {
        if(s[i] == '1') ans += temp;
        temp *= 2;
    }
    return ans;
}

void change(ll& mid, ll cnt, int sign) {
    while(cnt > 0 || st.count(mid)) {
        mid += sign;
        if(!st.count(mid)) cnt--;
    }
}

void solve() {
    sort(del.begin(), del.end());
    ll r = (1ll << n) - 1, mid = r / 2, half = 1ll << (n - 1);
    ll left = upper_bound(del.begin(), del.end(), mid) - del.begin(), right = m - left;
    ll cnt1 = half - left, cnt2 = half - right, diff = cnt1 - cnt2;
    // 找到第一个没有被删除的中间元素（偏左那个）
    while(st.count(mid)) mid--;
    if(diff < 0) { // 左边少了 要右移动
        change(mid, (abs(diff) + 1) / 2, 1);
    } else { // 左边多了 要左移动
        change(mid, diff / 2, -1);
    }
    for(int i = n - 1; i >= 0; i--) {
        if((1ll << i) & mid) cout << 1;
        else cout << 0;
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> m >> n;
        del = {}, st = {};
        for(int i = 0; i < m; i++) {
            cin >> t;
            ll num = to_num(t);
            del.push_back(num), st.insert(num);
        }
        solve();
    }
};