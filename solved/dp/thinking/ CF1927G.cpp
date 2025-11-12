/**
 * @Time : 2024/11/11-12:05 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1927G 动态规划 状态定义特殊
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e3 + 5;
int T, n, a[N];

/*
 * 因为某个点可以向左覆盖或者向右覆盖
 * 当选择向左覆盖时 需要知道左边最远没有覆盖的点 这样才知道当前点左覆盖之后 是否严丝合缝
 * 当选择向右覆盖时 需要知道右边最远已经覆盖到哪一点 这样才知道当前点有没有扩展覆盖的位置
 * 因此可以定义 f[i][l][r]: 考虑前i个点，左边未覆盖的最远点是l，右边最远覆盖到r的最小操作次数
 *
 * 转移方程
 * 1.不使用第i个点 f[i][l][r] = f[i - 1][l][r]
 * 记 lo[i] = max(1, i - a[i] + 1), hi[i] = min(n, i + a[i] - 1)
 * 2.左覆盖
 *      2.1 如果lo[i] > l 那么左边未覆盖的点依然是l，而右边点是否需要更新覆盖到i 其实无所谓
 *      因为左边l没有覆盖，那么必然需要有某一个点 j > i 并且lo[i] <= l来覆盖到l
 *      而这一个点会使得右边界扩展到 max(j,r) > i
 *      2.2 如果lo[i] <= l, 那么左边未覆盖的最远点将变为max(i,r) + 1,
 *      R = max(r, i): 当前点左覆盖可以完美覆盖到l，就连成一片
 *      左边未覆盖最远点可能变为i + 1，也可能是右边最远覆盖点r 再 +1
 *      右边覆盖到的点R = max(i,r) 这里右边覆盖点的更新 其实就是2.1中无效情况下 不更新右边界的补充
 *      f[i][R + 1][R] = f[i-1][l][r] + 1
 * 3.右覆盖
 *      hi[i] <= r : 既然不能扩展右边界 选择右覆盖没有任何意义。其有价值的做法在2中已讨论
 *      所以只讨论 hi[i] > r 的情况
 *      3.1 i <= l : 全都连成一片的情况 f[i][hi[i] + 1][hi[i]] = f[i-1][l][r] + 1
 *      3.2 i > l: 左边未覆盖的最远点是依旧是l 右边则会扩展到hi[i]
 *          f[i][l][hi[i]] = f[i-1][l][r] + 1
 *
 * 边界条件
 * f[0][1][0] = 0
 *
 * 答案：所有点都被覆盖了 意味着左边没有被覆盖的点是n+1,右边最远要将n覆盖住 f[n][n+1][n]
 */
void solve() {
    vector<vector<vector<int>>> f(n + 1, vector(n + 2, vector(n + 1, N)));
    f[0][1][0] = 0;
    for(int i = 1; i <= n; i++) {
        int lo = max(1, i - a[i] + 1), hi = min(n, i + a[i] - 1);
        for(int l = 1; l <= n + 1; l++) {
            for(int r = 0; r <= n; r++) {
                f[i][l][r] = min(f[i][l][r], f[i - 1][l][r]);
                if(lo <= l) { // 左覆盖有效的情况
                    int R = max(i, r);
                    f[i][R + 1][R] = min(f[i][R + 1][R], f[i-1][l][r] + 1);
                }
                if(hi > r) { // 右覆盖有效的情况
                    if(i <= l) f[i][hi + 1][hi] = min(f[i][hi + 1][hi], f[i-1][l][r] + 1);
                    else f[i][l][hi] = min(f[i][l][hi], f[i-1][l][r] + 1);
                }
            }
        }
    }
    cout << f[n][n + 1][n] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        solve();
    }
};