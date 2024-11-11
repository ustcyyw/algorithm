/**
 * @Time : 2024/7/25-10:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF985E 双指针 线段树
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 5e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, k, d, nums[N];

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

bool solve() {
    SegmentTree tree(n);
    tree.add(0, 1);
    for(int lo = 1, hi = 1; hi <= n; hi++) {
        while(nums[hi] - nums[lo] > d) lo++;
        int j = hi - k + 1;
        if(lo <= j) {
            int temp = tree.search(lo - 1, j - 1);
            if(temp == 1) tree.add(hi, 1);
        }
    }
    return tree.search(n, n);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k >> d;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    sort(nums + 1, nums + n + 1);
    cout << (solve() ? "YES" : "NO") << "\n";
};