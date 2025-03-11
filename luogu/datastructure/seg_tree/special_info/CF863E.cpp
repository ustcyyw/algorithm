/**
 * @Time : 2025/3/10-11:44 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF863E 2000 数据结构 线段树 维护最小值及出现的次数
 */
 /*
  * 被覆盖的点 值 > 0 没有被覆盖的点 值为0
  * 在离散化的时候要注意 将 l-1, r+1也进行离散化
  * 如果不这样做 假如有线段 [19,20],[20,24],[24,25]
  * 离散化之后是[0,1],[1,2],[2,3] 把中间那个删了会认为可行 但实际上21 22 23就没覆盖到
  * 将l-1和r+1也考虑到离散中，那么21和23对应的点 在中间线段被删后 值会变为0 就显示没有覆盖
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 200000 + 5, P = 13331;
int n, tv[N][2];
vector<int> pos;
#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val, tag, cnt;
    void build(int x, int l, int r) {
        cnt[x] = r - l + 1;
        if(l == r) return;
        int mid = (l + r) >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
    }
    // 区间修改操作中的下传函数
    void down(int x) {
        if(tag[x] == 0) return;
        val[ls] += tag[x], val[rs] += tag[x];
        tag[ls] += tag[x], tag[rs] += tag[x];
        tag[x] = 0;
    }

    void update(int x) {
        val[x] = min(val[ls], val[rs]);
        cnt[x] = 0;
        if(val[x] == val[ls]) cnt[x] += cnt[ls];
        if(val[x] == val[rs]) cnt[x] += cnt[rs];
    }

    // 区间修改
    void add(int x, int l, int r, int a, int b, int v) {
        if(a <= l && r <= b) {
            val[x] += v, tag[x] += v;
            return ;
        }
        down(x);
        int mid = (l + r) >> 1;
        if(a <= mid) add(ls, l, mid, a, b, v);
        if(b > mid) add(rs, mid + 1, r, a, b, v);
        update(x);
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0);
        tag = vector(4 * (n + 1), 0);
        cnt = vector(4 * (n + 1), 0);
        build(1, 0, n);
    }

    void add(int a, int b, int v) {
        add(1, 0, n, a, b, v);
    }

    int search() {
        return cnt[1];
    }
};

int find(int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

int solve() {
    SegmentTree st(pos.size());
    for(int i = 1; i <= n; i++) {
        tv[i][0] = find(tv[i][0]), tv[i][1] = find(tv[i][1]);
        st.add(tv[i][0], tv[i][1], 1);
    }
    int baseCnt = st.search();
    for(int i = 1; i <= n; i++) {
        st.add(tv[i][0], tv[i][1], -1);
        if(baseCnt == st.search()) return i;
        st.add(tv[i][0], tv[i][1], 1);
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> tv[i][0] >> tv[i][1];
        pos.push_back(tv[i][0]), pos.push_back(tv[i][1]);
        pos.push_back(tv[i][0] - 1), pos.push_back(tv[i][1] + 1);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    cout << solve() << "\n";
}