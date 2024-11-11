/**
 * @Time : 2024/5/21-9:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1234D 线段树
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
int T, n, q, p, l, r;
char c;
string s;

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

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    s = '.' + s;
    n = s.size();
    vector<SegmentTree> trees(26, SegmentTree(n));
    for(int i = 1; i < n; i++)
        trees[s[i] - 'a'].add(i, 1);
    cin >> q;
    for(int i = 1, t; i <= q; i++) {
        cin >> t;
        if(t == 1) {
            cin >> p;
            cin >> c;
            trees[s[p] - 'a'].add(p, -1);
            trees[c - 'a'].add(p, 1), s[p] = c;
        } else {
            cin >> l >> r;
            int cnt = 0;
            for(int j = 0; j < 26; j++)
                cnt += trees[j].search(l, r) > 0;
            cout << cnt << "\n";
        }
    }
};