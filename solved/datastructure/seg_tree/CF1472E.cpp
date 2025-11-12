/**
 * @Time : 2024/7/8-10:28 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1472E 线段树
 */
 /*
  * h和h比较，w和w比较时 找[1, hi - 1]上最小的w来比较
  *
  * h和w比较，w作为基础 找w处于[1, hi - 1]上最小的h
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, h[N], w[N], ans[N];

#define ls x << 1
#define rs (x << 1) | 1
const int MIN_VAL = -2e9, MAX_VAL = 2e9;

class SegmentTree {
private:
    int n;
    vector<int> val, idx;
    // 单点修改
    void add(int x, int l, int r, int pos, int v, int id) {
        if(l == r) {
            if(v < val[x]) val[x] = v, idx[x] = id;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v, id);
        else add(rs, mid + 1, r, pos, v, id);
        val[x] = min(val[ls], val[rs]);
        if(val[x] == val[ls]) idx[x] = idx[ls];
        else idx[x] = idx[rs];
    }

    vector<int> search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return {val[x], idx[x]};
        int mid = (l + r) >> 1;
        vector<int> res = {INT_MAX, -1};
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) {
            vector<int> temp = search(rs, mid + 1, r, a, b);
            if(temp[0] < res[0]) res = temp;
        }
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), MAX_VAL);
        idx = vector(4 * (n + 1), 0);
    }

    void add(int pos, int v, int id) {
        add(1, 0, n, pos, v, id);
    }

    vector<int> search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

vector<int> pos;

void scatter() {
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
}
/*
 * 离散化之后查询某个数在第几个位置 可以同时记录该位置对应的数
 */
int find(int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

void cal(int* a, int* b) {
    int m = pos.size();
    SegmentTree tree(m);
    for(int i = 1; i <= n; i++) {
        tree.add(find(a[i]), b[i], i);
    }
    for(int i = 1; i <= n; i++) {
        if(ans[i] != -1) continue;
        int hi = find(h[i]) - 1;
        if(hi >= 0) {
            vector<int> temp = tree.search(0, hi);
            if(temp[0] < w[i]) ans[i] = temp[1];
        }
    }
}

void solve() {
    scatter();
    cal(h, w), cal(w, h);
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        fill(ans, ans + n + 1, -1);
        pos = {};
        for(int i = 1; i <= n; i++) {
            cin >> h[i] >> w[i];
            pos.push_back(h[i]), pos.push_back(w[i]);
        }
        solve();
    }
};