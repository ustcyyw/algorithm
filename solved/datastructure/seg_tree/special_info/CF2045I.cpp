/**
 * @Time : 2024/12/27-9:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2045I 2100 数据结构 线段树 区间上不同元素的个数
 */
/*
  * 波浪序列中 两个x，两个y之间的间隔均为1 并且根据定义 f(x,y) = f(y,x)
  * 对于指定的x和y, 在找最长波浪序列的时候 先遇到x或者y就选择 然后切换去找另外一个数，以此类推
  * 在扫一遍数组的时候 枚举到nums[i]时，不妨假设 x = nums[i]就是波浪序列的两个数之一
  * 而前一个x位于j位置 [j+1, i-1]上的任意元素y
  * y和x是f(x,y)的一部分 i处的x对f(x,y)的贡献+1（y的贡献在之前计算了）
  * 但要注意 如果两个x之间有相同元素，比如y=3出现了3次 根据波浪序列的定义
  * 只有其中一个数被放在波浪序列中
  * 因而这个x会使多少个f(x,y)加1，就是[j+1, i-1]上不同元素的个数
  * 求 sum{f(x,y)} 那么在具体某个f(x,y)长度+1时，就往答案里+1，结果正确
  *
  * 如何求区间上不同元素的个数
  * 假设有两对相同的数，这两对数的下标分别为[j1, i1], [j2, i2]
  * 并且y在[j1, i1]上出现了两次，同时也在[j2, i2]出现了两次 位置是k1 k2
  * 其大小关系可能是
  * j1, j2, k1, k2, i1, i2
  * j2, j1, k1, k2, i2, i1
  * 那么在计数[j1, i1]和[j2, i2]的时候 其实都只计数k2这一次即可
  * 又或者y在[j1, i1]上出现了两次，但在[j2, i2]上只出现了k2
  * 其大小关系可能是
  * j1, k1, j2 ,k2, i2, i1
  * j1, k1, j2 ,k2, i1, i2
  * 那么在计数[j1, i1]和[j2, i2]的时候 其实都只计数k2这一次即可
  *
  * 一般地说明 因为是向右枚举 所以在相同数num又出现时 只记录最靠右的那一次
  * 对于位置[l,r]如果会num 那么仅保留num最右侧的能计数到 也不会重复
  * 但是如果不包含num，保留num最右侧也不会被计数到
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
int T, n, m, pre[N], nums[N], mp[N];


#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val, tag, cnt;
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
    ll ans = 0;
    SegmentTree st(n);
    for(int i = 1; i <= n; i++) {
        int l = pre[i] + 1, r = i - 1;
        int cnt = l <= r ? st.search(l, r) : 0;
        ans += cnt;
        // nums[i]第一次出现 除开它要接在前面以及出现的元素后面
        // 它自己要成为还没有出现过的元素的波浪序列中的第一个 所以要额外计数
        if(pre[i] == 0)
            ans += m - 1 - cnt;
        st.add(pre[i], -1), st.add(i, 1);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            pre[i] = mp[nums[i]];
            mp[nums[i]] = i;
        }
        solve();
    }
};