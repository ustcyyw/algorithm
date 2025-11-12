/**
 * @Time : 2024/7/28-11:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1660F2 CF1660F1 思维题 线段树
 */
 /*
  * 假设原本有 cnt1 个加号，cnt2个减号 并且有m组减号是相邻可替换的
  * 要满足要求 需要满足条件条件 假设换了n组减号 cnt1 + n = cnt2 - 2 * n
  * 3n = cnt2 - cnt1
  * cnt2 - cnt1 是3的倍数 并且n <= m
  *
  * 差距是3
  * 比如 -+---  --+-- -+-+--- 总之有一组相邻可换
  * 差距是6
  * 比如 -+------  -- + -----
  * 所以只要满足了cnt2 - cnt1是3的正整数倍 就一定能找到足够的相邻可替换的减号组
  *
  * 找cnt2 - cnt1 是3的倍数 只需要找差值同余的情况，所以按余数分组
  * 另外要注意 要满足cnt2 >= cnt1 也就是说在同一个组中 要找差值 <= 当前差值的组
  * 使用线段树
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n;
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

void solve() {
    vector<SegmentTree> trees(3, SegmentTree(2 * n + 1));
    trees[0].add(0 + n, 1);
    ll ans = 0;
    for(int i = 0, sum = 0; i < s.size(); i++) {
        if(s[i] == '+') sum--;
        else sum++;
        int m = (sum % 3 + 3) % 3;
        ans += trees[m].search(0, sum + n);
        trees[m].add(sum + n, 1);
    }
    cout << ans << "\n";
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> s;
        solve();
    }
};