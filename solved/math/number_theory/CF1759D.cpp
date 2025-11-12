/**
 * @Time : 2024/8/26-4:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1759D 数学 数论  贪心
 */
 /*
  * 凑末尾的0 其实就是凑一共有多少个2和5
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 9;
typedef long long ll;
ll T, n, m;

int count(int num, int base) {
    int cnt = 0;
    while(num % base == 0)
        cnt++, num /= base;
    return cnt;
}
// 乘数不超过m的情况下，补齐2或者5，limit表示2和5的差距 也就是最多补全limit个
int cal(int limit, int base) {
    if(limit == 0) return 0;
    for(int i = 1; i <= limit; i++) {
        if(pow(base, i) > m) return i - 1;
    }
    return limit;
}

ll solve() {
    int c2 = count(n, 2), c5 = count(n, 5);
    ll base = 1;
    if(c2 > c5) {
        ll cnt = cal(c2 - c5, 5);
        base = pow(5ll, cnt);
    } else if(c2 < c5) {
        ll cnt = cal(c5 - c2, 2);
        base = pow(2ll, cnt);
    }
    while(base * 10 <= m) base *= 10;
    return n * (m / base) * base;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        cout << solve() << "\n";
    }
};