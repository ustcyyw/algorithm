/**
 * @Time : 2024/12/3-11:14 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1996G 2200 线段树 暴力枚举
 */
/*
  * 问题困难的点在于 任意(a,b)之间有两条路径 a -> b,  b -> a 不知道该选哪条路径
  * 但是只要环中任意一条边断开 所有(a,b)之间就只有一条路径可走
  * 将这些路径选中，看看没有选的有哪些 这就是一个可能的答案。
  * 问题的本质就是能有多少条边断开，还让所有点对联通，与断开一条边来确定点对间对路径思路一致
  * 因此可以枚举强制要断开的边，然后将每个点对还能走的路径选上
  * 选中路径这个操作 就是将编号连续的一系列边使用次数+1。而没有被选中的边就是使用次数为0的边
  * 选择线段树来维护信息 懒更新 维护区间的最小值及最小值的出现次数
  *
  * 逐个枚举边的过程中
  * 有的边进入了 a->b 的范围，那么这个点对就要走 b->a
  * a->b的这些边就要放弃使用，b->a的边要使用
  * 有的边进入了 b->a 的范围 类似地
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, m, a[N], b[N];
vector<vector<int>> arrA, arrB; // 点对的坐标 -> 点对的编号 方便判断当前枚举的边进入了哪个范围

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val, tag, cnt;

    void build(int x, int l, int r) {
        cnt[x] = r - l + 1;
        if(l == r) return;
        int mid = (l + r) >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
    }

    vector<int> search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return {val[x], cnt[x]};
        down(x);
        int mid = (l + r) >> 1;
        vector<int> res = {INT_MAX, 0};
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) {
            vector<int> temp = search(rs, mid + 1, r, a, b);
            if(temp[0] < res[0]) res = temp;
            else if(temp[0] == res[0]) res[1] += temp[1];
        }
        return res;
    }

    // 区间修改操作中的下传函数 改变区间上的值 不会改变区间上的最小值的个数
    void down(int x) {
        if(tag[x] == 0) return;
        val[ls] += tag[x], val[rs] += tag[x];
        tag[ls] += tag[x], tag[rs] += tag[x];
        tag[x] = 0;
    }
    void update(int x) {
        val[x] = min(val[ls], val[rs]);
        cnt[x] = 0;
        if(val[x] == val[ls]) cnt[x] += cnt[ls];
        if(val[x] == val[rs]) cnt[x] += cnt[rs];
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
        update(x);
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0);
        tag = vector(4 * (n + 1), 0);
        cnt = vector(4 * (n + 1), 0);
        build(1, 1, n);
    }

    void add(int a, int b, int v) {
        add(1, 1, n, a, b, v);
    }

    int search() {
        if(val[1] == 0) return n - cnt[1]; // 如果[1,n]上的最小值是0，要选的边数量就是n-cnt[1]
        return n; // 最小值不是0 说明所有边都要选
    }
};

void solve() {
    SegmentTree st(n); // n个结点就有n条边
    for(int i = 1; i <= m; i++) { // 初始化 一开始断开编号为1的边
        if(a[i] == 1) st.add(b[i], n, 1); // 走b->a的路径
        else st.add(a[i], b[i] - 1, 1); // 走a->b的路径
    }
    int ans = st.search();
    for(int idx = 2; idx <= n; idx++) { // 枚举断开的边的编号
        for(int i : arrA[idx]) { // a[i] == idx 那么这个点对从现在开始要走 b->a的路径了
            st.add(b[i], n, 1);
            if(a[i] > 1) st.add(1, a[i] - 1, 1);
            st.add(a[i], b[i] - 1, -1); // 原先a->b的路径不走了
        }
        for(int i : arrB[idx]) { // b[i] == idx 这个点对现在要开始走 a->b的路径了
            st.add(a[i], b[i] - 1, 1);
            st.add(b[i], n, -1); // 原先b->a的路径不走了
            if(a[i] > 1) st.add(1, a[i] - 1, -1);
        }
        ans = min(ans, st.search());
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> m;
        arrA.assign(n + 1, {}), arrB.assign(n + 1, {});
        for(int i = 1; i <= m; i++) {
            cin >> a[i] >> b[i];
            arrA[a[i]].push_back(i), arrB[b[i]].push_back(i);
        }
        solve();
    };
};