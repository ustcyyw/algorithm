/**
 * @Time : 2024/11/21-11:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 4e6, MAX_VAL = 2e9;
int T, n, q, nums[(int)2e5 + 5] = {0};
char ope;

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
        val[x] = min(val[ls], val[rs]);
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = MAX_VAL;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = min(res, search(rs, mid + 1, r, a, b));
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), MAX_VAL);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

SegmentTree st(N + 5); // 区间查最小值 记录各个长度区间对应的最小端点
map<int, int> range; // 维护区间信息 左端点是某个集合中的数 右端点是集合中下一个数
map<int, multiset<int>> lens; // key：val  区间长度：该长度对应的区间的左端点

// 添加一个区间
void add(int l, int r) {
    int len = r - l - 1;
    range[l] = r;
    int old_val = lens[len].empty() ? MAX_VAL : *lens[len].begin();
    if(l < old_val) st.add(len, l);
    lens[len].insert(l);
}
// 删除一个区间
void del(int l, int r) {
    int len = r - l - 1;
    range.erase(l);
    lens[len].erase(l);
    if(lens[len].empty() || *lens[len].begin() > l)
        st.add(len, lens[len].empty() ? MAX_VAL : *lens[len].begin());
}
// 找到指定数的上一个数
int pre_num(int num) {
    auto it = range.lower_bound(num);
    it--;
    return it->first;
}
// 向集合中添加一个数
void insert(int num) {
    // 找到上一个数 得到上一个数对应的区间
    int lo = pre_num(num), hi = range[lo];
    del(lo, hi);
    add(lo, num), add(num, hi);
}
// 向集合中移除一个数
void remove(int num) {
    int lo = pre_num(num), hi = range[num];
    del(lo, num), del(num, hi);
    add(lo, hi);
}

void init() {
    // 复原线段树到初始状态
    for(auto& p : lens)
        st.add(p.first, MAX_VAL);
    lens = {}, range = {};
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        init();
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        nums[n + 1] = N + 3; // 设置哨兵
        for(int i = 0; i <= n; i++)
            add(nums[i], nums[i + 1]);
        cin >> q;
        for(int i = 1, num; i <= q; i++) {
            cin >> ope >> num;
            if(ope == '+') insert(num);
            else if(ope == '-') remove(num);
            else cout << (st.search(num, N + 3) + 1) << " ";
        }
        cout << "\n";
    }
};