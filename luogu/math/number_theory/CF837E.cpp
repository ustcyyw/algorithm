/**
 * @Time : 2025/3/2-11:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF837E 2100 数学 数论 dfs
 */
 /*
  * a = k1 * g, b = k2 * g
  *
  * 如果k1 = 1, 那么操作直接执行k2次就结束了
  * 如果k2 = 1, 操作1次就结束了
  * 如果k1是质数 那么直接操作 k2 % k1 次 然后再操作一次就结束
  *
  * 如果k1不是质数 将其分解质因数为 f1, f2 .. fm
  * ci = k2 % fi，就是操作ci次后 k2就能被fi整除
  * 那么此时 k1 /= fi, k2 /= fi, g *= fi
  * 按递归的操作 肯定是先递归min(ci)次，然后g就会变 因此要找到最小的ci
  * k1不必每次都去分解质因数 只要一开始分解一次 然后每次将ci剔除即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5, M = 1e6 + 5, mod = 1e9 + 7;
ll T, a, b;

multiset<ll> get_factor(ll num) {
    multiset<ll> st;
    for(int i = 2; i <= sqrt(num); i++) {
        while(num % i == 0) {
            st.insert(i);
            num /= i;
        }
    }
    if(num > 1) st.insert(num);
    return st;
}

ll dfs(multiset<ll>& st, ll k2) {
    if(st.empty() || k2 == 1) return k2;
    ll cnt = LONG_LONG_MAX, num = -1;
    for(ll t : st) {
        if(cnt > k2 % t)
            cnt = k2 % t, num = t;
    }
    st.erase(st.find(num));
    return cnt + dfs(st, (k2 - cnt) / num);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> a >> b;
    ll g0 = gcd(a, b);
    ll k1 = a / g0, k2 = b / g0;
    multiset<ll> st = get_factor(k1);
    cout << dfs(st, k2);
}