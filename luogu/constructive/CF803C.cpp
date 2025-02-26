/**
 * @Time : 2025/2/25-8:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF803C 1900 构造 数学
 */
/*
 * 假设序列的gcd = a1, 那么每个数都含有a1这个因子
 * a1 * (m1 + m2 + m3 + m4 + ... + mk) = sum
 * a1是sum的一个因子 最节省的办法是 m1 = 1, m2 = 2, m3 = 3 ...
 * 因此最省的办法下 和是 a1 * k * (k + 1) / 2
 * 如果 sum > a1 * k * (k + 1) / 2, 就有办法分配
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e3 + 5, M = 400;
ll sum, k;

ll find() {
    if(k > 1e6 || k * (k + 1) / 2 > sum) return -1;
    __int128 base = k * (k + 1) / 2;
    ll ans = -1;
    for(ll i = sqrt(sum); i >= 1; i--) {
        if(sum % i == 0) {
            if(i * base <= sum) ans = max(ans, i);
            if((__int128)sum / i * base <= sum) ans = max(ans, sum / i);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> sum >> k;
    ll a = find();
    if(a == -1) {
        cout << -1;
        return 0;
    }
    for(int i = 1; i < k; i++) {
        cout << a * i << " ";
        sum -= a * i;
    }
    cout << sum;
}