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
const int N = 2e5 + 15, M = 30;
int n, x;
char c;
vector<int> p, r, b;

ll outside(vector<int>& arr, int lo, int hi) {
    if(arr.empty()) return 0;
    int l = arr[0], r = arr.back();
    ll ans = 0;
    if(l < lo) ans += lo - l;
    if(r > hi) ans += r - hi;
    return ans;
}
// 采用方式2，对于在lo和hi的两个p点之间 计算r/b点需要的代价
// 在lo和hi中间没有点的时候 代价为0
ll inside(vector<int>& arr, int lo, int hi) {
    if(arr.empty() || arr.back() <= lo) return 0;
    int idx = lower_bound(arr.begin(), arr.end(), lo) - arr.begin();
    if(arr[idx] >= hi) return 0;
    ll dis = arr[idx] - lo;
    while(idx + 1 < arr.size() && arr[idx + 1] <= hi) {
        dis = max(dis, (ll)arr[idx + 1] - arr[idx]);
        idx++;
    }
    dis = max(dis, (ll)hi - arr[idx]);
    return hi - lo - dis;
}

ll insideAll() {
    ll ans = 0;
    for(int i = 0; i + 1 < p.size(); i++) {
        ll lo = p[i], hi = p[i + 1];
        // 如果lo和hi之间没有b点 d1为0，如果lo和hi之间没有r点 d2为0
        ll d1 = inside(b, lo, hi), d2 = inside(r, lo, hi);
        // d1 = 0，d2 = 0时 hi - lo + d1 + d2 = hi - lo, 就是特殊情况
        // d1或者d2有一个为0，hi - lo + d1 + d2 = 2 * (hi - lo) - maxD 也是特殊情况
        ans += min(2 * (hi - lo), hi - lo + d1 + d2);
    }
    return ans;
}

ll solve() {
    if(p.empty()) {
        ll t1 = r.empty() ? 0 : r.back() - r[0];
        ll t2 = b.empty() ? 0 : b.back() - b[0];
        return t1 + t2;
    }
    ll outBase = outside(b, p[0], p.back()) + outside(r, p[0], p.back());
    return outBase + insideAll();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> x >> c;
        if(c == 'R') r.push_back(x);
        else if(c == 'P') p.push_back(x);
        else b.push_back(x);
    }
    sort(p.begin(), p.end());
    sort(r.begin(), r.end());
    sort(b.begin(), b.end());
    cout << solve();
}