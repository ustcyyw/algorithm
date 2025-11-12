/**
 * @Time : 2025/1/4-1:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2009G2 2200 数学 线段树 单调栈
 */
/* 先按g1的思路求出a数组
  * j = l + k - 1
  * a[j], min(a[j], a[j+1]), min(a[j],a[j+1],a[j+2])
  * 求和 这个过程中加的数越来越小
  *
  * 假设值的变幻位于 j1, j2, j3, 但是 r < j3
  * sum = a[j0] * (j1-j0) + a[j1] * (j2-j1) + a[j2] * (r-j2)
  * 得到一个类似于后缀和的东西 可以用单调栈预处理
  * 然后对于每个查询 只要找到实际求和区间[lo = l + k - 1, r]上的最小值的下标idx
  * 在这个下标的右边直接用这个最小值计算贡献 a[idx] * (r - lo + 1)
  * 左边的部分通过后缀和 sum[lo] - sum[idx]得到
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, k, q, nums[N], a[N], nxt[N];
ll sum[N];


#define ls x << 1
#define rs (x << 1) | 1
const int MIN_VAL = -2e9, MAX_VAL = 2e9;

class SegmentTree {
private:
    int n;
    vector<int> val, idx;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = v, idx[x] = pos;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = min(val[ls], val[rs]);
        if(val[x] == val[ls]) idx[x] = idx[ls];
        else idx[x] = idx[rs];
    }

    vector<int> search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return {val[x], idx[x]};
        int mid = (l + r) >> 1;
        vector<int> res(2, MAX_VAL);
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

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }
    // 返回最小值所在的索引
    int search(int a, int b) {
        return search(1, 0, n, a, b)[1];
    }
};

void initA() {
    map<int, int> cnt;
    multiset<int> st;
    function<void(int)> add = [&](int num) -> void {
        int cc = ++cnt[num];
        st.insert(cc);
        if(cc > 1) st.erase(st.find(cc - 1));
    };
    function<void(int)> remove = [&](int num) -> void {
        int cc = --cnt[num];
        if(cc > 0) st.insert(cc);
        st.erase(st.find(cc + 1));
    };
    for(int lo = 1, hi = 1; hi <= n; hi++) {
        add(nums[hi]);
        if(hi - lo + 1 > k) remove(nums[lo++]);
        a[hi] = k - *st.rbegin();
    }
}

void initSum() {
    stack<int> st;
    sum[n + 1] = 0;
    for(int i = n; i >= 1; i--) {
        int num = a[i];
        while(!st.empty() && num <= a[st.top()])
            st.pop();
        nxt[i] = st.empty() ? n + 1 : st.top();
        st.push(i);
        sum[i] = sum[nxt[i]] + (ll)(nxt[i] - i) * a[i];
    }
}

ll cal(SegmentTree& tree, int l, int r) {
    int lo = l + k - 1, idx = tree.search(lo, r);
//    if(idx == lo) return (ll)a[lo] * (r - lo + 1);
    return sum[lo] - sum[idx] + (ll)(r - idx + 1) * a[idx];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> k >> q;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            nums[i] -= i;
        }
        initA(); initSum();
        SegmentTree tree(n + 1);
        for(int i = 1; i <= n; i++)
            tree.add(i, a[i]);
        for(int i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            cout << cal(tree, l, r) << "\n";
        }
    }
};