/**
 * @Time : 2024/7/7-3:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1462F 线段树 前后缀分解 排序
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, suf[N];
vector<int> pos;
vector<vector<int>> range;

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val, tag;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] += v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = val[ls] + val[rs];
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res += search(rs, mid + 1, r, a, b);
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

void scatter() {
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    m = pos.size();
}
/*
 * 离散化之后查询某个数在第几个位置 可以同时记录该位置对应的数
 */
int find(int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

void solve() {
    scatter();
    sort(range.begin(), range.end());
    SegmentTree tree1(m), tree2(m);
    for(int i = n - 1; i >= 0; i--) {
        int lo = find(range[i][0]), hi = find(range[i][1]);
        suf[i] = tree2.search(lo, hi);
        tree2.add(lo, 1);
    }
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int lo = find(range[i][0]), hi = find(range[i][1]);
        int cnt = tree1.search(lo, m - 1);
        ans = max(ans, cnt + 1 + suf[i]);
        tree1.add(hi, 1);
    }
    cout << n - ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        pos = {}, range = {};
        for(int i = 1, l, r; i <= n; i++) {
            cin >> l >> r;
            pos.push_back(l), pos.push_back(r);
            range.push_back({l, r});
        }
        solve();
    }
};