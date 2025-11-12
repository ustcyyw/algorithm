/**
 * @Time : 2025/3/28-10:56 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF962E 2200 贪心 构造 模拟
 */
/*
  * 先排除一些特殊情况
  * 没有p点 分别将r和b连通即可
  *
  * 接下来就是p存在的情况 如果r或者b有一个不存在，比如r点没有的情况
  * 当忽略了b点 依旧要保证p点连通性 以下讨论可以包括这种情况
  * 1. 对于在p范围外的r点和b点 都得分别就近连到p点上
  * 2. 在p范围内的点 比如p1和p2之间
  *     2.1 如果是 p1 -> r...r -> p2 这样连接，在忽略r时 p1和p2也断开了
  *         因此还需要一条 p1 -> b...b -> p2的线路 总的代价是 2 * (p2 - p1)
  *     2.2 如果是先将 p1 -> p2 连起来，然后再考虑b和r的分别连到p1或者p2
  *         b和r是独立且对成的 讨论其中一个即可
  *         一部分b点连p1，一部分b点连p2，每种可能的方案都是 去掉两个b点的一段距离
  *         或者去掉p1和第一个b点，或者去掉p2和最后一个b点 要让距离最小 去掉最大一段距离即可
  *         所以总代价是 3 * (p2 - p1) - maxB - maxR
  *     2.3 特殊的 p1和p2之间没有点 代价之间是p2 - p1
  *         如果p1和p2之间只有一类点 选择2.1的方式是 2 * (p2 - p1); 2.2的方式是 2 * (p2 - p1) - maxB
  *         因此 应该选2.2方式
  *         inside函数计算p1,p2之间的代价时，如果r或者b点没有介于这二者之间的 会返回0
  *
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