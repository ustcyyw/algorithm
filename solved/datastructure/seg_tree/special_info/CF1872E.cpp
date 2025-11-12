/**
 * @Time : 2024/9/20-11:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1872E 线段树
 */
 /*
  * 维护区间上的异或和
  * 区间操作是将标识为1和0的两组数调换 调换之后维护两组数区间上的异或和
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, q, nums[N];
string s;
#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val0, val1, tag; //

    void update(int x) {
        val0[x] = val0[ls] ^ val0[rs];
        val1[x] = val1[ls] ^ val1[rs];
    }
    // 单点修改
    void build(int x, int l, int r, int pos, int v, int flag) {
        if(l == r) {
            if(flag) val1[x] = v;
            else val0[x] = v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) build(ls, l, mid, pos, v, flag);
        else build(rs, mid + 1, r, pos, v, flag);
        update(x);
    }

    int search(int x, int l, int r, int a, int b, int flag) {
        if(a <= l && r <= b) return flag == 0 ? val0[x] : val1[x];
        down(x);
        int mid = (l + r) >> 1, res = 0;
        if(a <= mid) res ^= search(ls, l, mid, a, b, flag);
        if(b > mid) res ^= search(rs, mid + 1, r, a, b, flag);
        return res;
    }

    // 区间修改操作中的下传函数
    void down(int x) {
        if(tag[x] == 0) return;
        swap(val1[ls], val0[ls]), swap(val1[rs], val0[rs]);
        tag[ls] ^= tag[x], tag[rs] ^= tag[x];
        tag[x] = 0;
    }
    // 区间修改
    void add(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) {
            tag[x] ^= 1;
            swap(val1[x], val0[x]);
            return ;
        }
        down(x);
        int mid = (l + r) >> 1;
        if(a <= mid) add(ls, l, mid, a, b);
        if(b > mid) add(rs, mid + 1, r, a, b);
        update(x);
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val0 = vector(4 * (n + 1), 0), val1 = vector(4 * (n + 1), 0);
        tag = vector(4 * (n + 1), 0);
    }

    void build(int pos, int v, int flag) {
        build(1, 0, n, pos, v, flag);
    }

    void add(int l, int r) {
        add(1, 0, n, l, r);
    }

    int search(int a, int b, int flag) {
        return search(1, 0, n, a, b, flag);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        SegmentTree tree(n);
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cin >> s >> q;
        for(int i = 1; i <= n; i++)
            tree.build(i, nums[i], s[i - 1] - '0');
        for(int i = 1, t, l, r, g; i <= q; i++) {
            cin >> t;
            if(t == 1) {
                cin >> l >> r;
                tree.add(l, r);
            } else {
                cin >> g;
                cout << tree.search(0, n, g) << " ";
            }
        }
        cout << "\n";
    }
};