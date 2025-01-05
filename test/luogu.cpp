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
const int N = 1e5 + 5, mod = 998244353;
int T, n, k, xs[N], rs[N], qs[N], val[12 * N];
map<int, vector<int>> mp; // 以q为key存放机器人编号

#define lson x << 1
#define rson (x << 1) | 1

// 单点修改
void add(int x, int l, int r, int pos, int v) {
    if (l == r) {
        val[x] += v;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) add(lson, l, mid, pos, v);
    else add(rson, mid + 1, r, pos, v);
    val[x] = val[lson] + val[rson];
}

int search(int x, int l, int r, int a, int b) {
    if (a <= l && r <= b) return val[x];
    int mid = (l + r) >> 1, res = 0;
    if (a <= mid) res = search(lson, l, mid, a, b);
    if (b > mid) res += search(rson, mid + 1, r, a, b);
    return res;
}

void add(int pos, int v) {
    add(1, 0, n, pos, v);
}

int search(int a, int b) {
    return search(1, 0, n, a, b);
}

int find(vector<int> &pos, int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

void collect(vector<int> &arrX, vector<int> &arrV1, vector<int> &arrV2, int q) {
    for (int i = q; i - q <= k; i++) {
        for (int id: mp[i])
            arrX.push_back(id), arrV1.push_back(id), arrV2.push_back(id);
    }
    sort(arrX.begin(), arrX.end(), [&](auto &a, auto &b) -> bool {
        return xs[a] < xs[b];
    });
    sort(arrV1.begin(), arrV1.end(), [&](auto &a, auto &b) -> bool {
        return xs[a] - rs[a] < xs[b] - rs[b];
    });
    sort(arrV2.begin(), arrV2.end(), [&](auto &a, auto &b) -> bool {
        return xs[a] + rs[a] < xs[b] + rs[b];
    });
}

ll cal(vector<int> &arrX, vector<int> &arrV1, vector<int> &arrV2, int q) {
    vector<int> pos;
    for (int id: arrX) {
        pos.push_back(xs[id]);
        pos.push_back(xs[id] + rs[id]);
        pos.push_back(xs[id] - rs[id]);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    int m = pos.size();
    fill(val, val + 4 * (m + 1), 0);
    ll ans = 0;
    set<int> in; // 在线段树中记录着的下标
    for (int i = 0, j1 = 0, j2 = 0; i < arrX.size(); i++) {
        if (qs[arrX[i]] != q) continue;
        int x = xs[arrX[i]];
        while (j1 < arrV1.size()) {
            int id = arrV1[j1], v = xs[id] - rs[id];
            if (v > x) break;
            add(1, 0, m, find(pos, xs[id]), 1), in.insert(id);
            j1++;
        }
        while (j2 < arrV2.size()) {
            int id = arrV2[j2], v = xs[id] + rs[id];
            if (v >= x) break;
            if (in.count(id))
                add(1, 0, m, find(pos, xs[id]), -1), in.erase(id);
            j2++;
        }
        int lo = find(pos, x - rs[arrX[i]]), hi = find(pos, x + rs[arrX[i]]);
        if (in.count(arrX[i]))
            add(1, 0, m, find(pos, x), -1), in.erase(arrX[i]);
        ans += search(1, 0, m, lo, hi);
    }
    return ans;
}

void solve() {
    ll ans = 0;
    vector<int> aux;
    for (auto &p: mp)
        aux.push_back(p.first);
    for (int q: aux) {
        vector<int> arrX, arrV1, arrV2;
        collect(arrX, arrV1, arrV2, q);
        ans += cal(arrX, arrV1, arrV2, q);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            cin >> xs[i] >> rs[i] >> qs[i];
            mp[qs[i]].push_back(i);
        }
        solve();
    }
};