/**
 * @Time : 2025/2/20-8:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1045G 2200 cdq分治
 */
 /*
  * 和CF762E 是一摸一样的题 代码一点不用改
  *
  * 按视野从大到小排序 这样靠右边的能看见左边的 就相互能看见
（l, mid], (mid, r)两边都已经按q排序的情况下
对于右边的 qi, 左边所有满足 abs(qi - qj) <= k 的机器人，都记录下xj下标
然后去找 [xi - ri, xi + ri] 上一共多少个点
这个区间上的点保证了i可以看到j，并且j的视野更大，j也能看到i
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5;
ll n, m, k, ans = 0;
vector<int> pos;
struct Node {
    int x, r, q;
} robots[N];


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

void dfs(SegmentTree& st, int l, int r) {
    if(l == r) return;
    int mid = (l + r) >> 1;
    dfs(st, l, mid), dfs(st, mid + 1, r);
    for(int i = mid + 1, j1 = l, j2 = l; i <= r; i++) {
        int q = robots[i].q;
        while(j2 <= mid && robots[j2].q - q <= k) {
            st.add(find(robots[j2].x), 1);
            j2++;
        }
        while(j1 <= mid && q - robots[j1].q > k) {
            st.add(find(robots[j1].x), -1);
            j1++;
        }
        int lo = robots[i].x - robots[i].r, hi = robots[i].x + robots[i].r;
        ans += st.search(find(lo), find(hi));
        if(i == r) { // 清理线段树中的值 恢复初值
            while(j1 < j2) {
                st.add(find(robots[j1].x), -1);
                j1++;
            }
        }
    }
    sort(robots + l, robots + r + 1, [](auto& a, auto& b) -> bool {return a.q < b.q;});
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n >> k;
    for(int i = 0, x, r, q; i < n; i++) {
        cin >> x >> r >> q;
        robots[i].x = x, robots[i].r = r, robots[i].q = q;
        pos.push_back(x - r), pos.push_back(x + r), pos.push_back(x);
    }
    // 按视野半径从大到小排序 这样就可以保证靠右的点i能看到j，那么j一定也能看到i
    sort(robots, robots + n, [](auto& a, auto& b) -> bool {
        return a.r > b.r;
    });
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    m = pos.size();
    SegmentTree st(m + 1);
    dfs(st, 0, n - 1);
    cout << ans << "\n";
};