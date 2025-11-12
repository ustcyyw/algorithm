/**
 * @Time : 2024/12/11-12:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1915F 1500 数据结构 线段树
 */
/*
 * lo1 < lo2 的两个人 如果hi1 < hi2
 * 因为速度一致 所以第一个人追不上第二个人 并且停在它之前 不会打招呼
 * 只有hi1 > hi2，第二个人先停下 然后第一个人追上了 发生一次打招呼
 * 因此要找的就是 起点在某个人右边 并且终点反而在它终点左边的人数
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n;
vector<int> pos;
vector<vector<int>> arr;

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
        // down(x);
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

void scatter() {
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
}

int find(int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

void solve() {
    scatter();
    SegmentTree st(pos.size());
    ll ans = 0;
    for(int i = n - 1; i >= 0; i--) {
        int hi = find(arr[i][1]);
        ans += st.search(0, hi);
        st.add(hi, 1);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        pos = {}, arr = {};
        for(int i = 1, a, b; i <= n; i++) {
            cin >> a >> b;
            pos.push_back(b), arr.push_back({a, b});
        }
        sort(arr.begin(), arr.end());
        solve();
    }
};