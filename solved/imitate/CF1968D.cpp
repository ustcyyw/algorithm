/**
 * @Time : 2024/5/9-11:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1968D 模拟
 */
 /*
  * 枚举走的过程中停在的终点 剩余时间都在这个位置停留拿分
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll T, n, k, b, s, p[N], a[N];

ll cal(int x) {
    ll ans = 0, sum = 0;
    for(int i = 0; i <= min(k, n - 1); i++) {
        ans = max(ans, sum + (k - i) * a[x]);
        sum += a[x];
        x = p[x];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k >> b >> s;
        for(int i = 1; i <= n; i++)
            cin >> p[i];
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        ll c1 = cal(b), c2 = cal(s);
        if(c1 > c2) cout << "Bodya";
        else if(c1 < c2) cout << "Sasha";
        else cout << "Draw";
        cout << "\n";
    }
};