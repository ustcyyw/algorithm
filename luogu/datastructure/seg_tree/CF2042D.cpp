/**
 * @Time : 2024/12/30-2:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2042D 1900 离线思路 数据结构 线段树 二分查找
 */
/*
 * 需要特判有区间完全一样的情况
 *
 * 区间[l,r]的父区间[lo,hi]满足 lo <= l, 且 hi >= r
 * 先将集合按左端点排序 所有lo <= l的区间在处理区间[l,r]时都已经考虑了
 * 将集合的覆盖用区间修改+1来表示 那么在r点的值 就代表了有多少个区间覆盖了[l,r]
 * 要找到所有这些区间 就向右去找最大的hi使得 val[r] = val[hi]
 * 这样就找到了所有父区间的交集的右端点，左端点用类似的思路再来一遍
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, ans[N];
set<ll> zero;
vector<vector<int>> arr;
vector<int> pos;

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val, tag;

    int search(int x, int l, int r, int a) {
        if(l == r) return val[x];
        down(x);
        int mid = (l + r) >> 1;
        if(a <= mid) return search(ls, l, mid, a);
        return search(rs, mid + 1, r, a);
    }
    // 区间修改操作中的下传函数
    // 如果要多维护最小值/最大值个数操作的时候 也用这个函数即可 因为修改区间值 不影响最值的个数
    void down(int x) {
        if(tag[x] == 0) return;
        val[ls] += tag[x], val[rs] += tag[x];
        tag[ls] += tag[x], tag[rs] += tag[x];
        tag[x] = 0;
    }

    // 区间修改
    void add(int x, int l, int r, int a, int b, int v) {
        if(a <= l && r <= b) {
            val[x] += v, tag[x] += v;
            return ;
        }
        down(x);
        int mid = (l + r) >> 1;
        if(a <= mid) add(ls, l, mid, a, b, v);
        if(b > mid) add(rs, mid + 1, r, a, b, v);
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0);
        tag = vector(4 * (n + 1), 0);
    }

    void add(int a, int b, int v) {
        add(1, 0, n, a, b, v);
    }

    int search(int a) {
        return search(1, 0, n, a);
    }
};

void scatter() {
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    m = pos.size();
}

int find(int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

int searchR(SegmentTree& st, int lo, int hi, int v) {
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(st.search(mid) >= v) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

int searchL(SegmentTree& st, int lo, int hi, int v) {
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(st.search(mid) >= v) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

void solve() {
    scatter();
    sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool {
        return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
    });
    SegmentTree st1(m);
    for(int i = 0; i < n; i++) {
        int lo = find(arr[i][0]), hi = find(arr[i][1]);
        int v = st1.search(hi);
        if(v != 0) {
            int r = searchR(st1, hi, m, v);
            ans[arr[i][2]] = pos[r] - arr[i][1];
        }
        st1.add(lo, hi, 1);
    }
    sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool {
        return a[1] != b[1] ? a[1] < b[1] : a[0] > b[0];
    });
    SegmentTree st2(m);
    for(int i = n - 1; i >= 0; i--) {
        int lo = find(arr[i][0]), hi = find(arr[i][1]);
        int v = st2.search(lo);
        if(v != 0) {
            int l = searchL(st2, 0, hi, v);
            ans[arr[i][2]] += arr[i][0] - pos[l];
        }
        st2.add(lo, hi, 1);
    }
    for(int i = 1; i <= n; i++)
        cout << (zero.count(i) ? 0 : ans[i]) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        fill(ans, ans + n + 1, 0);
        arr = {}, pos = {}, zero = {};
        map<ll, int> map;
        for(int i = 1, l, r; i <= n; i++) {
            cin >> l >> r;
            ll key = ll(l) * (1e9 + 1) + r;
            if(map.count(key))
                zero.insert(i), zero.insert(map[key]);
            else map[key] = i;
            pos.push_back(l), pos.push_back(r);
            arr.push_back({l, r, i});
        }
        solve();
    }
};