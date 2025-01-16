/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, nums[N], ans[N];
vector<vector<ll>> cache;

ll dfs(int lo, int hi) {
    if(lo == hi) return 0;
    if(cache[lo][hi] != -1) return cache[lo][hi];
    ll t1 = dfs(lo + 1, hi), t2 = dfs(lo, hi - 1);
    return cache[lo][hi] = min(t1, t2) + nums[hi] - nums[lo];
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        cache = vector(n + 1, vector(n + 1, -1ll));
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        sort(nums, nums + n + 1);
        cout << dfs(1, n) << "\n";
    }
};