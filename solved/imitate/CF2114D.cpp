/**
 * @Time : 2025/5/30-10:01
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2114D 1400 模拟 暴力枚举
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, M = 1e6 + 5, mod = 998244353;
ll T, n, posX[N], posY[N];
multiset<ll> setX, setY;

ll solve() {
    if(n == 1) return 1;
    ll ans = LONG_LONG_MAX;
    for(int i = 1; i <= n; i++) {
        ll x = posX[i], y = posY[i];
        setX.erase(setX.find(x)), setY.erase(setY.find(y));
        ll x1 = *setX.begin(), x2 = *setX.rbegin();
        ll y1 = *setY.begin(), y2 = *setY.rbegin();
        ll dx = x2 - x1 + 1, dy = y2 - y1 + 1;
        ll temp;
        if(dx * dy >= n) temp = dx * dy;
        else temp = min((dx + 1) * dy, dx * (dy + 1));
        ans = min(temp, ans);
        setX.insert(x), setY.insert(y);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        setX = {}, setY = {};
        for(int i = 1; i <= n; i++) {
            cin >> posX[i] >> posY[i];
            setX.insert(posX[i]), setY.insert(posY[i]);
        }
        cout << solve() << "\n";
    }
}