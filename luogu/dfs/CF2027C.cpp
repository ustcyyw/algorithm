/**
 * @Time : 2025/1/2-9:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2027C 1500 dfs
 */
 /*
  * 对于特定长度 只有特定的 a[i] + i = len + 1 满足条件 然后添加0后 这个点就不可能再被访问
  * 可以认为某一个点只能访问一次
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5, mod = 998244353;
ll T, n, ans, nums[N];
set<ll> marked;
map<ll, vector<int>> mp;

void dfs(ll len) {
    if(marked.count(len)) return;
    marked.insert(len);
    if(mp[len + 1].empty()) ans = max(ans, len);
    for(int i : mp[len + 1])
        dfs(len + i - 1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        marked = {}, mp = {}, ans = 0;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            if(i != 1) mp[nums[i] + i].push_back(i);
        }
        dfs(n);
        cout << ans << "\n";
    }
};