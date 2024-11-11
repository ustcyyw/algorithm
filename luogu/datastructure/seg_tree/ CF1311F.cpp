/**
 * @Time : 2024/6/24-3:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1311F 线段树 排序 分类讨论
 */
 /*
  * 按初始位置排序 xi < xj
    速度相等的 距离不会变 最小值就是一开始的距离差
    速度小于的 距离会拉大 最小值就是一开始的距离差
    速度大于的 距离会缩小 不用算
    线段树记录 坐标和，以及点的数量
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5;
typedef long long ll;
int T, n, X[N], V[N];
vector<int> vp;
vector<vector<int>> arr;

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<ll> val, cnt;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] += v, cnt[x]++;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = val[ls] + val[rs], cnt[x] = cnt[ls] + cnt[rs];
    }

    vector<ll> search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return {val[x], cnt[x]};
        int mid = (l + r) >> 1;
        vector<ll> res = {0, 0};
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) {
            vector<ll> temp = search(rs, mid + 1, r, a, b);
            res[0] += temp[0], res[1] += temp[1];
        }
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0ll);
        cnt = vector(4 * (n + 1), 0ll);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    vector<ll> search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

void scatter(vector<int>& pos) {
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
}

int find(vector<int>& pos, int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

void solve() {
    scatter(vp);
    for(int i = 1; i <= n; i++)
        arr.push_back({X[i], find(vp, V[i])});
    sort(arr.begin(), arr.end());
    SegmentTree tree(vp.size());
    ll ans = 0;
    for(auto& p : arr) {
        int x = p[0], v = p[1];
        vector<ll> temp = tree.search(0, v);
        ans += temp[1] * x - temp[0];
        tree.add(v, x);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> X[i];
    for(int i = 1; i <= n; i++) {
        cin >> V[i];
        vp.push_back(V[i]);
    }
    solve();
};