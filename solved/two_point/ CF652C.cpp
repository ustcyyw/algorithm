/**
 * @Time : 2024/4/9-11:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 枚举区间左端点i，看区间右端点j的可能位置
  * 右端点具有单调性
  * 就是如果[i,j]满足要求 那么[i, j-1]满足要求
  * 如果[i,j]不满足要求 那么[i, j+1]更不满足要求
  * 因此确定最大的j即可。就要求[i,j]内不能有任何一对数
  * 随着i的左移动，i右侧的数对增加或者不变
  * 每有一个数对增加 对j的要求会更严格 所以就要看j是否需要也左移动
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 3e5 + 5;
int n, m, p[N], marked[N], idx[N];
vector<int> mp[N];

void solve() {
    ll ans = 0;
    for(int i = n, j = n + 1; i >= 1; i--) {
        int a = p[i];
        marked[a] = 1;
        for(int b : mp[a]) {
            if(marked[b]) // j是否左移动，要求[i,j]范围内不能有任何一对数 所以j取决于最靠近i的那一对数
                j = min(j, idx[b]);
        }
        ans += j - i;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
        idx[p[i]] = i;
    }
    for(int i = 1, a, b; i <= m; i++) {
        cin >> a >> b;
        mp[a].push_back(b), mp[b].push_back(a);
    }
    solve();
};