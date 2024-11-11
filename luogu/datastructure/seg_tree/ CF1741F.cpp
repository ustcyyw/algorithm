/**
 * @Time : 2024/8/5-12:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1741F
 */
/*
 * 对于某个线段[l,r]找起点在r及右边的其它线段，看这些线段的终点最大值maxE
 * 如果超过了l说明存在交点
 * 否则最短距离可能是 l - maxE
 * 另外找起点超过r的最小起点minS，另一个可能的最短距离为 minS - r
 *
 * 但是只能是不同颜色的 所以需要消除自己这个颜色的影响
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, lbs[N], rbs[N], color[N], ans[N];
vector<ll> pos;
const ll MIN_VAL = -1e10 - 5, MAX_VAL = 1e10 + 5;
#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = max(val[ls], val[rs]);
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = max(res, search(rs, mid + 1, r, a, b));
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
/*
 * 将数组进行离散化
 */
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

void set_val(SegmentTree& tree, map<int, multiset<int>>& ends, int start) {
    multiset<int>& st = ends[start];
    int val = st.empty() ? 0 : *st.rbegin();
    tree.add(start, val);
}

void solve() {
    multiset<int> start_pos = {m - 1}; // 记录起点位置 m-1是设置的哨兵
    map<int, multiset<int>> ends; // 起点 -> 终点位置
    map<int, vector<int>> map; // color -> ids
    for(int i = 1; i <= n; i++) {
        int lo = find(lbs[i]), hi = find(rbs[i]);
        lbs[i] = lo, rbs[i] = hi;
        start_pos.insert(lo), ends[lo].insert(hi);
        map[color[i]].push_back(i);
    }
    SegmentTree tree(m); // 记录起点对应的最大终点位置 并且查询区间最大值
    for(auto& p : ends)
        set_val(tree, ends, p.first);
    for(auto& p : map) {
        vector<int>& arr = p.second;
        // 先全清除 计算后再都放回
        for(int i : arr) {
            int lo = lbs[i], hi = rbs[i];
            start_pos.erase(start_pos.find(lo)), ends[lo].erase(ends[lo].find(hi));
            set_val(tree, ends, lo);
        }
        // 计算
        for(int i : arr) {
            int lo = lbs[i], hi = rbs[i];
            int t1 = tree.search(0, hi), t2 = *start_pos.lower_bound(hi);
            if(t1 >= lo) ans[i] = 0;
            else ans[i] = min(pos[lo] - pos[t1], pos[t2] - pos[hi]);
        }
        // 放回
        for(int i : arr) {
            int lo = lbs[i], hi = rbs[i];
            start_pos.insert(lo), ends[lo].insert(hi);
            set_val(tree, ends, lo);
        }
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        pos = {MIN_VAL, MAX_VAL};
        for(int i = 1; i <= n; i++) {
            cin >> lbs[i] >> rbs[i] >> color[i];
            pos.push_back(lbs[i]), pos.push_back(rbs[i]);
        }
        scatter();
        m = pos.size();
        solve();
    }
};