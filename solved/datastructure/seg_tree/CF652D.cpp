/**
 * @Time : 2024/4/10-9:14 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#define ls x << 1
#define rs (x << 1) | 1
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 2e5 + 5;
int n, ans[N];
vector<vector<int>> inter;
vector<int> pos;

class SegmentTree {
private:
    int n;
    vector<int> val;

    void add(int x, int l, int r, int p, int v) {
        if(l == r) {
            val[x] += v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(p <= mid) add(ls, l, mid, p, v);
        else add(rs, mid + 1, r, p, v);
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

    void add(int p, int v) {
        add(1, 0, n, p, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

int find(int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

void solve() {
    SegmentTree tree(pos.size());
    sort(inter.begin(), inter.end());
    for(int i = n - 1; i >= 0; i--) {
        int lo = find(inter[i][0]), hi = find(inter[i][1]);
        ans[inter[i][2]] = tree.search(lo, hi);
        tree.add(hi, 1);
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, a, b; i <= n; i++) {
        cin >> a >> b;
        inter.push_back({a, b, i});
        pos.push_back(a), pos.push_back(b);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    solve();
};