/**
 * @Time : 2025/10/20-12:50
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : P1972 蓝题 思维 线段树 <套路>重复元素处理
 */
/*
  * 如果要求的区间是[0, i]，只有i这个变量
  * 那么对于重复出现的数 就只用考虑最靠近r的那一个即可，就只计算他的贡献
  * 其余数相同数直接标价为无效
  * 比如数组 [3,1,1,2,3,2,1]
  * i = 0: [3,*,*,*,*,*,*]
  * i = 1: [3,1,*,*,*,*,*]
  * i = 2: [3,*,1,*,*,*,*]
  * i = 3: [3,*,1,2,*,*,*]
  * i = 4: [*,*,1,2,3,*,*]
  * i = 5: [*,*,1,*,3,2,*]
  * i = 6: [*,*,*,*,3,2,1]
  * 随着i变化，整理后的数组在变化，其前缀和sum_change（视有效的数字贡献为1，*号无效则为0）也在动态变化
  * 通过sum_change能以前缀和的思路求出任意区间[l,i]上的不同数的数量（所求答案），其中l取值为[0,i]
  * i依次往右，动态维护sum_change的方法：
  * 1. 当某个数第一次出现的时候，对于右端点属于[i,n]上的区间，这个数对答案的贡献都为1
  * 因此sum_change[i,n]上的所有值都+1
  * 2. 当某个数第二次出现的时候
  *     2.1 如果不对sum_change进行任何操作，l属于[i,j-1]的区间[l,i]上的答案就会比真实的少1
  *         所以必须得操作，接下来就是想操作什么
  *     2.2 如果对sum_change[j,n]上的所有值+1，l属于[0,i-1]的区间[l,i]上的答案就会比正确的多1
  *     2.3 而sum_change[0,i-1]本身也和这个数无关，也不可以进行任何操作，否则l属于[0,i-1]的区间答案都会出错
  *     2.4 因而必须得操作的情况下想到对sum_change[i,j-1]，让sum_change[i,j-1]上的值-1，刚好可以得出正确结果
  *
  * 2.4的做法 也可以从数有效和无效的角度得出
  * 当某个数第一次出现，对sum_change[i,n]区间+1
  * 当该数第二次出现，那第一次出现时就失效了，其对sum_change[i,n]区间的贡献就失效，所以sum_change[i,n]区间-1
  * 但是第二次出现，他对[j,n]上的区间有贡献，sum_change[j,n]区间+1
  * 一来一回，sum_change区间[j,n]上无变化，sum_change区间[i,j-1]要-1
  *
  * 注意这个套路，必须是i依次往右变化，动态维护时才能计算，有点类似离线的思路
  * 不可以整个处理完之后拿来求任意[l,r]上的答案，只能是动态维护过程中求[l,i]上的答案
  *
  * 可以提供给LC3721参考
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 1e9 + 7;
int T, n, m, nums[N], ans[N], pre[N];
vector<vector<int>> query;

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val, tag, cnt;

    int search(int x, int l, int r, int pos) {
        if(l == r) return val[x];
        down(x);
        int mid = (l + r) >> 1;
        if(pos <= mid) return search(ls, l, mid, pos);
        else return search(rs, mid + 1, r, pos);
    }

    // 区间修改操作中的下传函数
    // 如果要多维护最小值/最大值个数操作的时候 也用这个函数即可 因为修改区间值 不影响最值的个数
    void down(int x) {
        if(tag[x] == 0) return;
        val[ls] += tag[x], val[rs] += tag[x];
        tag[ls] += tag[x], tag[rs] += tag[x];
        tag[x] = 0;
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
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0);
        tag = vector(4 * (n + 1), 0);
//        cnt = vector(4 * (n + 1), 0);
    }

    void add(int l, int r, int v) {
        add(1, 0, n, l, r, v);
    }

    int search(int pos) {
        return search(1, 0, n, pos);
    }
};

void solve() {
    SegmentTree st(n);
    for(int i = 1, j = 0; i <= n && j < m; i++) {
        int num = nums[i], k = pre[num];
        if(k == 0) st.add(i, n, 1);
        else st.add(k, i - 1, -1);
        pre[num] = i;
        while(j < m && query[j][1] == i) {
            int l = query[j][0], idx = query[j][2];
            ans[idx] = st.search(i) - st.search(l - 1);
            j++;
        }
    }
    for(int i = 1; i <= m; i++)
        cout << ans[i] << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cin >> m;
        for(int i = 1, l, r; i <= m; i++) {
            cin >> l >> r;
            query.push_back({l, r, i});
        }
        sort(query.begin(), query.end(), [](auto& a, auto& b) -> bool {
            return a[1] < b[1];
        });
        solve();
    }
}