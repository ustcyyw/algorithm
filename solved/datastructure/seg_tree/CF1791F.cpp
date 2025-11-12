/**
 * @Time : 2025/1/18-11:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1791F 1500 数据结构 线段树 数学
 */
 /*
  * 数位计算操作 操作4 5次肯定就只剩个位数了 就不会再变了
  * 所以只要知道某个点被操作了几次 就能o1得计算出结果
  * 用线段树维护区间修改操作 进行单点计算即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7, R = 26;
int T, n, q, nums[N];

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val, tag;

    int search(int x, int l, int r, int pos) {
        if(l == r) return val[x];
        down(x);
        int mid = (l + r) >> 1;
        if(pos <= mid) return search(ls, l, mid, pos);
        else return search(rs, mid + 1, r, pos);
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

    int search(int pos) {
        return search(1, 0, n, pos);
    }
};

int cal(int val, int cnt) {
    if(val < 10 || cnt == 0) return val;
    int sum = 0;
    while(val > 0) {
        sum += val % 10;
        val /= 10;
    }
    return cal(sum, cnt - 1);
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> q;
        SegmentTree st(n);
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        for(int i = 1, type, x1, x2; i <= q; i++) {
            cin >> type >> x1;
            if(type == 1) {
                cin >> x2;
                st.add(x1, x2, 1);
            } else {
                int cnt = st.search(x1);
                cout << cal(nums[x1], cnt) << "\n";
            }
        }
    }
};