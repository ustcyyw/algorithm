/**
 * @Time : 2024/7/16-8:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1992F 数学 数论 贪心
 */
 /*
  * 只要子数组的范围内挑一系列数乘积不为x 就一直扩大子数组范围
  * 挑的这一系列数 一定是x的因子才行
  * 可以记录所有可能的乘积情况 这些乘积一定是x的因子
  * 然后当前数可以选 也可以不选 看什么时候有乘积为x 就得进行一次分组
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, x, nums[N];
unordered_set<ll> st;

void get_factor() {
    st = {x};
    for(int i = 2; i <= sqrt(x); i++) {
        if(x % i == 0)
            st.insert(i), st.insert(x / i);
    }
}

void solve() {
    get_factor();
    int cnt = 1;
    set<ll> pre = {1}, cur;
    for(int i = 1; i <= n; i++) {
        int num = nums[i];
        if(!st.count(num)) continue;
        for(ll pm : pre) {
            ll t = pm * num;
            cur.insert(pm);
            if(st.count(t)) cur.insert(t);
        }
        if(cur.count(x)) pre = {1}, cnt++, i--;
        else swap(cur, pre);
        cur = {};
    }
    cout << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> x;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};