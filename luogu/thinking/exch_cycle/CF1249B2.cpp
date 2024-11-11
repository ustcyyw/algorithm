/**
 * @Time : 2024/5/22-8:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1249B2 置换环
 */
 /*
  * 因为p是n的排列 所以所有元素都在环中
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, m, nums[N], ans[N], marked[N];

void dfs(int v, int cnt) {
    int w = nums[v];
    cnt++, marked[v] = 1;
    if(marked[w]) ans[v] = cnt;
    else {
        dfs(w, cnt);
        ans[v] = ans[w];
    }
}

void solve() {
    for(int i = 1; i <= n; i++) {
        if(marked[i]) continue;
        dfs(i, 0);
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        fill(marked, marked + n + 1, 0);
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};