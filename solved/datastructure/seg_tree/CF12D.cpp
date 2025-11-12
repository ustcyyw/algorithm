/**
 * @Time : 2025/1/23-10:42 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF12D 2400 数据结构 线段树
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 5e5 + 5, mod = 998244353;
int T, n;
vector<int> a, b, c;
map<int, vector<vector<int>>> mp;

#define ls x << 1
#define rs (x << 1) | 1
const int MIN_VAL = -2e9, MAX_VAL = 2e9;

class SegmentTree {
private:
    int n;
    vector<int> val, tag, cnt;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = max(val[x], v);
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = max(val[ls], val[rs]);
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = MIN_VAL;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = max(res, search(rs, mid + 1, r, a, b));
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), MIN_VAL);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

void std_in(vector<int>& arr) {
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        arr.push_back(num);
    }
}

void scatter(vector<int>& pos) {
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
}

int find(vector<int>& pos, int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

void solve() {
    scatter(b);
    int m = b.size(), ans = 0;
    SegmentTree tree(m);
    for(auto it = mp.rbegin(); it != mp.rend(); it++) {
        vector<vector<int>>& arr = it->second;
        for(vector<int>& p : arr) {
            int lo = find(b, p[0]) + 1;
            int v = lo <= m ? tree.search(lo, m) : -1;
            if(v > p[1]) ans++;
        }
        for(vector<int>& p : arr) {
            int x = find(b, p[0]);
            tree.add(x, p[1]);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        std_in(a), std_in(b), std_in(c);
        for(int i = 0; i < n; i++)
            mp[a[i]].push_back({b[i], c[i]});
        solve();
    }
};