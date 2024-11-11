/**
 * @Time : 2024/5/20-9:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1234E
 */
 /*
  * 从时间复杂度的角度来看 只能是通过一次计算后 其它所有计算都o1地计算出变化值
  * pi 被放到第一个位置
  * 比pi小的数 位置+1，比pi大的数 位置不变 因此如果一对数都在pi左边/右边 是不用变的
  * 但是一个数在左边 一个数在右边的 距离得-1
  * 并且要注意和pi这个数相领的数 计算值都要改变。可以用adj[pi]预先记录与pi相领的数有哪些
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
ll T, n, m, base = 0, x[N];
vector<vector<int>> pairs;
vector<int> adj[N];

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

void init() {
    for(int i = 1; i < m; i++) {
        int n1 = x[i], n2 = x[i + 1];
        base += abs(n1 - n2);
        pairs.push_back({min(n1, n2), max(n1, n2)});
        adj[n1].push_back(n2), adj[n2].push_back(n1);
    }
    sort(pairs.begin(), pairs.end());
}

ll change(int i) {
    ll ans = base;
    for(int num : adj[i]) {
        if(num == i) continue;
        ans = ans - abs(num - i);
        int pos = num < i ? num + 1 : num;
        ans = ans + abs(1 - pos);
    }
    return ans;
}

void solve() {
    init();
    cout << base << " ";
    SegmentTree tree(n);
    for(int i = 2, j = 0, k = pairs.size(); i <= n; i++) {
        ll ans = change(i);
        while(j < k && pairs[j][0] < i) { // 其中一个数小于i的 将另外一个数进行计数
            tree.add(pairs[j][1], 1);
            j++;
        }
        ans -= tree.search(i + 1, n); // 看另一个数大于i的有多少
        cout << ans << " ";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
        cin >> x[i];
    solve();
};