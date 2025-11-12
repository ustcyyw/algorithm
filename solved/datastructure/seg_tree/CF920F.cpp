/**
 * @Time : 2025/3/20-9:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF920F 2000 数据结构 数论
 */
 /*
  * 操作1的操作次数极其有限 5 6次之后 操作前后值不变。
  * 值已经不变的 就直接从待修改集合中删除就好
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 15, M = 1e6 + 5;
int n, m, divide[M], nums[N];
set<int> st;

int init = []() -> int {
    for(int i = 1; i < M; i++) {
        for(int j = 1; j * i < M; j++)
            divide[j * i]++;
    }
    return 0;
}();

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<ll> val;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = val[ls] + val[rs];
    }

    ll search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        ll mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res += search(rs, mid + 1, r, a, b);
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0ll);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    ll search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

void change(SegmentTree& tree, int l, int r) {
    set<int> del;
    for(auto it = st.lower_bound(l); it != st.end() && *it <= r; it++) {
        int idx = *it;
        nums[idx] = divide[nums[idx]];
        tree.add(idx, nums[idx]);
        if(nums[idx] == divide[nums[idx]])
            del.insert(idx);
    }
    for(int num : del)
        st.erase(num);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    SegmentTree tree(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
        tree.add(i, nums[i]), st.insert(i);
    }
    for(int i = 1, t, l, r; i <= m; i++) {
        cin >> t >> l >> r;
        if(t == 2) cout << tree.search(l, r) << "\n";
        else change(tree, l, r);
    }
}