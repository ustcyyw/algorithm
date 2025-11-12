/**
 * @Time : 2025/3/13-11:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF808D 1900 暴力枚举
 */
 /*
  * 枚举不调整前的分割线 然后看左边和右边有没有元素调整之后让两边相等
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, nums[N];
multiset<ll> pre, suf;

bool check() {
    ll sum = accumulate(nums + 1, nums + n + 1, 0ll);
    if(sum % 2 == 1) return false;
    if(suf.count(sum / 2)) return true;
    for(ll i = 1, ps = 0, ss; i <= n; i++) {
        ps += nums[i], ss = sum - ps;
        pre.insert(nums[i]), suf.erase(suf.find(nums[i]));
        if(ps == ss) return true;
        if(ps > ss) {
            ll diff = ps - ss;
            if(diff % 2 == 0 && pre.count(diff / 2)) return true;
        } else {
            ll diff = ss - ps;
            if(diff % 2 == 0 && suf.count(diff / 2)) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            suf.insert(nums[i]);
        }
        cout << (check() ? "YES" : "NO") << "\n";
    }
}