/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, mod = 1e9 + 7;
int T, n, m, a[N];
vector<int> pos;
map<int, vector<int>> mp;

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

int find(int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

void solve() {
    ll ans = 0;
    SegmentTree tree(m);
    for(int i = n; i >= 1; i--) {
        if(a[i] > i) ans += tree.search(find(i), m);
        if(mp.count(i)) {
            for(int x : mp[i]) {
                ans -= tree.search(find(x), m);
            }
        }
        tree.add(find(a[i]), 1);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pos.push_back(i), pos.push_back(a[i]);
        if(a[i] < n && a[i] > i) mp[a[i]].push_back(i);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    m = pos.size();
    solve();
}