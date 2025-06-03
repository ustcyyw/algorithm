/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, M = 1e6 + 5, mod = 998244353;
ll T, n, k, a[N], pre[N], suf[N];

// 检查 num 不断除以2 会不会变为base
bool check(int num, int base) {
    while(num > 1 && num % 2 == 0 && num != base)
        num /= 2;
    return num == base;
}

vector<int> cal(int num) {
    int cnt = 1;
    while(num % 2 == 0)
        num /= 2, cnt *= 2;
    return {cnt, num};
}

int cal(int num, int base) {
    if(!check(num, base)) return cal(num)[0];
    int c = num / base;
    return 1 + (c - 2) * cal(base)[0];
}

bool solve() {
    for(int i = 1; i <= n; i++) {
        vector<int> t = cal(a[i]);
        ll c2 = suf[1] - suf[i], c3 = pre[n] - pre[i];
        if(t[0] + c2 + c3 >= k) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    int t = 0;
    while(T-- > 0) {
        t++;
        cin >> n >> k;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            pre[i] = pre[i - 1] + cal(a[i], a[i - 1]);
        }
        a[n + 1] = 0, suf[n + 1] = 0;
        for(int i = n; i >= 1; i--)
            suf[i] = suf[i + 1] + cal(a[i], a[i + 1]);
        cout << (solve() ? "YES" : "NO") << "\n";
    }
}