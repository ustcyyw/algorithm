/**
 * @Time : 2025/1/29-7:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1721D 1800 位运算 贪心 试填法
 */
 /*
  * 容易想到试填法
  * 要让某一位d与后结果为1，那么对于所有的 (ai,bi) 在d位上xor结果是1
  * 也就是说 所有的(ai,bi)在d位上一个是0一个是1
  * 于是将a数组 b数组按这一位上是1还是0为标准分为2部分
  * 要求 a中1的部分数量和b中0的部分数量一致，否则这一位就是0
  * 如果能满足要求 就按这样分组 于是a数组和b数组被细分为2个部分
  * 如果不能满足要求 那这一位最终结果是0 就不要将a和b进行细分 以便后续的位可以凑出1
  *
  * 在这个过程中a和b会被分为很多个细小的组 要每个组都能在该位凑出1才进行下一步细分
  * 否则对于下一位的讨论 依旧按当前分组进行
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 998244353, M = 31;
int T, n, a[N], b[N], ans[M];

int check(int d, int lo, int hi) {
    int idx = lo - 1;
    for(int i = lo; i <= hi; i++) {
        int t = 1 << d, t1 = t & a[i], t2 = t & b[i];
        if(t1 == t2) return -1;
        if(i > lo && (a[i - 1] & (1 << d)) != t1) idx = i - 1;
    }
    return idx;
}

void bfs() {
    int d = M - 1;
    vector<vector<int>> cur, nxt;
    cur.push_back({1, n});
    while(d >= 0) {
        nxt.clear();
        for(auto& p : cur) {
            if(ans[d] == 0) continue;
            int lo = p[0], hi = p[1];
            sort(a + lo, a + hi + 1, [&](auto& f1, auto& f2) -> bool {
                int t1 = (1 << d) & f1, t2 = (1 << d) & f2;
                return t1 < t2;
            });
            sort(b + lo, b + hi + 1, [&](auto& f1, auto& f2) -> bool {
                int t1 = (1 << d) & f1, t2 = (1 << d) & f2;
                return t1 > t2;
            });
            int mid = check(d, lo, hi);
            if(mid == -1) ans[d] = 0;
            else {
                if(lo <= mid) nxt.push_back({lo, mid});
                if(mid + 1 <= hi) nxt.push_back({mid + 1, hi});
            }
        }
        if(ans[d] == 1) swap(cur, nxt);
        d--;
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n;
        fill(ans, ans + M, 1);
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        bfs();
        int num = 0;
        for(int i = 0; i < M; i++) {
            if(ans[i] == 1) num |= 1 << i;
        }
        cout << num << "\n";
    }
};