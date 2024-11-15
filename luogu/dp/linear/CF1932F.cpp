/**
 * @Time : 2024/11/14-11:41 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1932F 动态规划 1900
 */
 /*
  * 如果选择了某一个点 这个点对应的区间范围内 都不能有任何点 否则会导致有猫被喂两次而死
  * dp[i]截止某点 最多喂养的数量
  * 1. 不选i点 dp[i - 1]
  * 2. 选i点 dp[j - 1] + cnt[i]，j是i对应的所有区间中 最左端的边界, cnt[i]是i点对应了多少个区间
  *
  * 预处理pre[i]，表示i对应的所有区间中 最左端的边界
  * 以及cnt[i]
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e6 + 5;
int T, n, m, ls[N], cnt[N], pre[N], dp[N];
vector<vector<int>> rs;

void solve() {
    multiset<int> st;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < ls[i]; j++)
            st.insert(i); // 左边界的有序集合
        cnt[i] = st.size();
        pre[i] = st.empty() ? 1 : *st.begin();
        for(int l : rs[i])
            st.erase(st.find(l));
    }
    dp[0] = 0;
    for(int i = 1; i <= n; i++) {
        dp[i] = max(dp[i - 1], dp[pre[i] - 1] + cnt[i]);
    }
    cout << dp[n] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        rs.assign(n + 1, {});
        fill(ls, ls + n + 1, 0);
        for(int i = 1, l, r; i <= m; i++) {
            cin >> l >> r;
            ls[l]++, rs[r].push_back(l);
        }
        solve();
    }
};