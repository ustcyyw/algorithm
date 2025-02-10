/**
 * @Time : 2025/2/2-11:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF31C 1700 线段树
 */
 /*
  * 区间修改 + 维护区间上的最大值
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e6 + 5;
int n, arr[N][2];
#define ls x << 1
#define rs (x << 1) | 1
const int MIN_VAL = -2e9;

class SegmentTree {
private:
    int n;
    vector<int> val, tag, cnt;
    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        down(x);
        int mid = (l + r) >> 1, res = MIN_VAL;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = max(res, search(rs, mid + 1, r, a, b));
        return res;
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
        val[x] = max(val[ls], val[rs]);
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

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    SegmentTree tree(N);
    for(int i = 1, l, r; i <= n; i++) {
        cin >> l >> r;
        arr[i][0] = l, arr[i][1] = r - 1;
        tree.add(l, r - 1, 1);
    }
    vector<int> ans;
    for(int i = 1; i <= n; i++) {
        int l = arr[i][0], r = arr[i][1];
        tree.add(l, r, -1);
        if(tree.search(0, N) <= 1) ans.push_back(i);
        tree.add(l, r, 1);
    }
    cout << ans.size() << "\n";
    for(int num : ans)
        cout << num << " ";
};