/**
 * @Time : 2025/2/28-8:31 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF817F 2300 线段树 lazy-tag
 */
/*
 * 操作1 区间上没有的数都添加进去 相当于这个区间上所有数都存在了 标记为1
 * 操作2 区间上有都数都拿出来 相当于区间上所有数都不存在了 标记为0
 * 操作3 区间上没有的添加进去 有的拿出来 相当于两类数互换 标记 0变1，1变0
 * 如果使用 sum[x] 表示区间上的和
 * 那么答案就是找到区间上最小位置 使得该位置对应的sum值为0
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, mod = 1e9 + 7;
ll T, n, q[N][3];
vector<ll> pos = {1};

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> sum, tag;

    int search(int x, int l, int r) {
        if(l == r) return l;
        down(x, l, r);
        int mid = (l + r) >> 1;
        if(sum[ls] != mid - l + 1) return search(ls, l, mid);
        else return search(rs, mid + 1, r);
    }

    // 区间修改操作中的下传函数
    // 如果要多维护最小值/最大值个数操作的时候 也用这个函数即可 因为修改区间值 不影响最值的个数
    void down(int x, int l, int r) {
        if(tag[x] == 0) return;
        int mid = (l + r) >> 1;
        if(tag[x] == 1) { // [l, r]上所有数都存在
            sum[ls] = mid - l + 1, sum[rs] = r - mid;
            tag[ls] = tag[rs] = tag[x];
        } else if(tag[x] == 2) { // [l, r]上所有数都不存在
            sum[ls] = sum[rs] = 0;
            tag[ls] = tag[rs] = tag[x];
        } else {
            sum[ls] = mid - l + 1 - sum[ls];
            sum[rs] = r - mid - sum[rs];
            updateTag3(ls), updateTag3(rs);
        }
        tag[x] = 0;
    }

    void updateTag3(int son) {
        if(tag[son] == 0) tag[son] = 3;
        else if(tag[son] == 3) tag[son] = 0;
        else if(tag[son] == 1) tag[son] = 2;
        else tag[son] = 1;
    }

    // 区间修改
    void add(int x, int l, int r, int a, int b, int v) {
        if(a <= l && r <= b) {
            if(v == 1) sum[x] = r - l + 1;
            if(v == 2) sum[x] = 0;
            if(v == 3) {
                sum[x] = r - l + 1 - sum[x];
                updateTag3(x);
            } else tag[x] = v;
            return ;
        }
        down(x, l, r);
        int mid = (l + r) >> 1;
        if(a <= mid) add(ls, l, mid, a, b, v);
        if(b > mid) add(rs, mid + 1, r, a, b, v);
        sum[x] = sum[ls] + sum[rs];
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        sum = vector(4 * (n + 1), 0); // 区间上的和
        tag = vector(4 * (n + 1), 0);
    }

    void add(int a, int b, int v) {
        add(1, 0, n, a, b, v);
    }

    int search() {
        return search(1, 0, n);
    }
};

int find(ll val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

void solve() {
    SegmentTree st(pos.size());
    for(int i = 1; i <= n; i++) {
        int t = q[i][0], l = find(q[i][1]), r = find(q[i][2]);
        st.add(l, r, t);
        int idx = st.search();
        cout << pos[idx] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    for(ll i = 1, t, l, r; i <= n; i++) {
        cin >> t >> l >> r;
        q[i][0] = t, q[i][1] = l, q[i][2] = r;
        pos.push_back(l), pos.push_back(r), pos.push_back(r + 1);
        if(l > 1) pos.push_back(l - 1);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    solve();
}

/*
 * 另外一种可以通过的思路
 * val0: 区间上没有出现过的数的最小值
 * val1: 区间上出现过的数的最小值
 */
//#include<bits/stdc++.h>
//using namespace std;
//typedef long long ll;
//typedef long double ld;
//const int N = 1e5 + 5, mod = 1e9 + 7;
//ll T, n, q[N][3];
//vector<ll> pos = {1};
//
//#define ls x << 1
//#define rs (x << 1) | 1
//
//class SegmentTree {
//private:
//    int n;
//    vector<int> val0, val1, tag;
//
//    void build(int x, int l, int r) {
//        val0[x] = l, val1[x] = n - 1;
//        if(l == r) return;
//        int mid = (l + r) >> 1;
//        build(ls, l, mid), build(rs, mid + 1, r);
//    }
//
//    int search(int x, int l, int r, int a, int b) {
//        if(a <= l && r <= b) return val0[x];
//        down(x, l, r);
//        int mid = (l + r) >> 1, res = INT_MAX;
//        if(a <= mid) res = search(ls, l, mid, a, b);
//        if(b > mid) res = min(res, search(rs, mid + 1, r, a, b));
//        return res;
//    }
//
//    // 区间修改操作中的下传函数
//    // 如果要多维护最小值/最大值个数操作的时候 也用这个函数即可 因为修改区间值 不影响最值的个数
//    void down(int x, int l, int r) {
//        if(tag[x] == 0) return;
//        int mid = (l + r) >> 1;
//
//        if(tag[x] == 1) { // [l, r]上所有数都存在
//            val0[ls] = val0[rs] = n - 1;
//            val1[ls] = l, val1[rs] = mid + 1;
//            tag[ls] = tag[x], tag[rs] = tag[x];
//        } else if(tag[x] == 2) { // [l, r]上所有数都不存在
//            val0[ls] = l, val0[rs] = mid + 1;
//            val1[ls] = val1[rs] = n - 1;
//            tag[ls] = tag[x], tag[rs] = tag[x];
//        } else {
//            swap(val0[ls], val1[ls]);
//            swap(val0[rs], val1[rs]);
//            updateTag3(ls), updateTag3(rs);
//        }
//        tag[x] = 0;
//    }
//
//    void updateTag3(int son) {
//        if(tag[son] == 0) tag[son] = 3;
//        else if(tag[son] == 3) tag[son] = 0;
//        else if(tag[son] == 1) tag[son] = 2;
//        else tag[son] = 1;
//    }
//
//    // 区间修改
//    void add(int x, int l, int r, int a, int b, int v) {
//        if(a <= l && r <= b) {
//            if(v == 1) val0[x] = n - 1, val1[x] = l;
//            if(v == 2) val0[x] = l, val1[x] = n - 1;
//            if(v == 3) {
//                swap(val0[x], val1[x]);
//                updateTag3(x);
//            } else tag[x] = v;
//            return ;
//        }
//        down(x, l, r);
//        int mid = (l + r) >> 1;
//        if(a <= mid) add(ls, l, mid, a, b, v);
//        if(b > mid) add(rs, mid + 1, r, a, b, v);
//        val0[x] = min(val0[ls], val0[rs]);
//        val1[x] = min(val1[ls], val1[rs]);
//    }
//
//public:
//    SegmentTree(int n) {
//        this-> n = n;
//        val0 = vector(4 * (n + 1), 0); // 区间上没有出现过的数的最小值
//        val1 = vector(4 * (n + 1), 0); // 区间上出现过的数的最小值
//        tag = vector(4 * (n + 1), 0);
//        build(1, 0, n);
//    }
//
//    void add(int a, int b, int v) {
//        add(1, 0, n, a, b, v);
//    }
//
//    int search(int a, int b) {
//        return search(1, 0, n, a, b);
//    }
//};
//
//int find(ll val) {
//    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
//}
//
//void solve() {
//    SegmentTree st(pos.size());
//    for(int i = 1; i <= n; i++) {
//        int t = q[i][0], l = find(q[i][1]), r = find(q[i][2]);
//        st.add(l, r, t);
//        int idx = st.search(0, pos.size());
//        cout << pos[idx] << "\n";
//    }
//}
//
//int main() {
//    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
////    cin >> T;
//    cin >> n;
//    for(ll i = 1, t, l, r; i <= n; i++) {
//        cin >> t >> l >> r;
//        q[i][0] = t, q[i][1] = l, q[i][2] = r;
//        pos.push_back(l), pos.push_back(r), pos.push_back(r + 1);
//        if(l > 1) pos.push_back(l - 1);
//    }
//    sort(pos.begin(), pos.end());
//    pos.erase(unique(pos.begin(), pos.end()), pos.end());
//    solve();
//}