/**
 * @Time : 2025/1/3-1:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1906F 2100 离线思维 线段树 维护区间上非空子数组最大和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5, mod = 998244353;
ll T, n, m, q, ans[N];
vector<vector<int>> opeL, opeR, query;

ll sum[4 * N], sumL[4 * N], sumR[4 * N], ms[4 * N];
#define ls x << 1
#define rs (x << 1) | 1
void update(int x) {
    sum[x] = sum[ls] + sum[rs];
    // 如果最大子数组和没有跨mid max(ms[ls], ms[rs]); 最大子数组和跨越了mid sumL[rs] + sumR[ls]
    ms[x] = max({ms[ls], ms[rs], max(sumL[rs], 0ll) + sumR[ls], sumL[rs] + max(0ll, sumR[ls])});
    sumR[x] = max(sumR[rs], sum[rs] + max(0ll, sumR[ls]));
    sumL[x] = max(sumL[ls], sum[ls] + max(0ll, sumL[rs]));
}

void add(int x, int l, int r, int pos, int v) {
    if(l == r) { // 单点修改 不是单点加减
        sum[x] = sumL[x] = sumR[x] = v, ms[x] = v;
        return ;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) add(ls, l, mid, pos, v);
    else add(rs, mid + 1, r, pos, v);
    update(x);
}

vector<ll> search(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) return {sum[x], sumL[x], sumR[x], ms[x]};
    int mid = (l + r) >> 1;
    vector<ll> res(4, LONG_LONG_MIN);
    if(a <= mid) res = search(ls, l, mid, a, b);
    if(b > mid) {
        if(res[0] != LONG_LONG_MIN) {
            vector<ll> aux(4, 0), rt = search(rs, mid + 1, r, a, b);
            aux[0] = res[0] + rt[0];
            // sumL[x] = max(sumL[ls], sum[ls] + max(0, sumL[rs]));
            aux[1] = max(res[1], res[0] + max(0ll, rt[1]));
            // sumR[x] = max(sumR[rs], sum[rs] + max(0, sumR[ls]));
            aux[2] = max(rt[2], rt[0] + max(0ll, res[2]));
            aux[3] = max({res[3], rt[3],
                          max(rt[1], 0ll) + res[2], rt[1] + max(0ll, res[2])});
            swap(res, aux);
        } else res = search(rs, mid + 1, r, a, b);
    }
    return res;
}

void solve() {
    int j1 = 0, j2 = 0;
    for(auto& t : query) {
        int k = t[0], lo = t[1], hi = t[2];
        while(j1 < m && opeL[j1][0] <= k) {
            add(1, 0, m, opeL[j1][1], opeL[j1][2]);
            j1++;
        }
        while(j2 < m && opeR[j2][0] < k) {
            add(1, 0, m, opeR[j2][1], 0);
            j2++;
        }
        ans[t[3]] = search(1, 0, m, lo, hi)[3];
    }
    for(int i = 1; i <= q; i++)
        cout << ans[i] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1, l, r, x; i <= m; i++) {
            cin >> l >> r >> x;
            opeL.push_back({l, i, x}), opeR.push_back({r, i, x});
        }
        sort(opeL.begin(), opeL.end());
        sort(opeR.begin(), opeR.end());
        cin >> q;
        for(int i = 1, k, s, t; i <= q; i++) {
            cin >> k >> s >> t;
            query.push_back({k, s, t, i});
        }
        sort(query.begin(), query.end());
        solve();
    }
};