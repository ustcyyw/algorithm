/**
 * @Time : 2024/7/13-8:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1579E2 线段树
 */
 /*
  * 考虑nums[i]怎么放的时候 nums[0, i - 1]的数不管是什么顺序
  * nums[i]放在队列头或者尾得到的逆序对都是相同的
  * 而nums[i]放哪对nums[i + 1]又是没有影响的
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, nums[N];
#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] += v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = val[ls] + val[rs];
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res += search(rs, mid + 1, r, a, b);
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

vector<int> pos;

void scatter() {
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
}
/*
 * 离散化之后查询某个数在第几个位置 可以同时记录该位置对应的数
 */
int find(int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

void solve() {
    scatter();
    m = pos.size();
    SegmentTree tree(m);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int num = nums[i], idx = find(num);
        int t1 = idx == 0 ? 0 : tree.search(0, idx - 1); // 放在队头的逆序对
        int t2 = idx == m - 1 ? 0 : tree.search(idx + 1, m - 1); // 放在队尾
        ans += min(t1, t2);
        tree.add(find(num), 1);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        pos = {};
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            pos.push_back(nums[i]);
        }
        solve();
    }
};