/**
 * @Time : 2025/1/30-11:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 对于某个数 num 其因子个数取决于其质因子构成
  * 假设其有m个质因子构成 每个质因子分别出现了 c1,c2...cm次
  * 那么其因子的个数为 (c1 + 1) * (c2 + 1) * ... * (cm + 1)
  *
  * 本题给出了因子个数n
  * n = (c1 + 1) * (c2 + 1) * ... * (cm + 1)
  * 所以将n表示为多个大于1的数相乘的形式
  * 某一组乘法形式 就对应了一种质因子构成（质因子的种类数、每种出现了几次）
  * 然后用贪心的思路 让小的质因子出现更多的次数
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e3 + 5, M = 2 * N;
int n;

void dfs(vector<vector<int>>& fac, vector<vector<int>>& divisors, vector<int>& arr, int num) {
    if(num == 1) {
        vector<int> temp = arr;
        fac.push_back(temp);
        return;
    }
    int pre = arr.empty() ? -1 : arr.back();
    for(int d : divisors[num]) {
        if(d == 1 || d < pre) continue;
        if(num / d < d && num / d != 1) continue;
        arr.push_back(d);
        dfs(fac, divisors, arr, num / d);
        arr.pop_back();
    }
}

ll cal(vector<int>& prime, vector<int>& fac) {
    ll ans = 1;
    for(int i = fac.size() - 1, j = 0; i >= 0; i--, j++) {
        int cnt = fac[i] - 1;
        if(cnt > 63) return LONG_LONG_MAX;
        while(cnt-- > 0) {
            ans *= prime[j];
            if(ans > 1e18 || ans <= 0) return LONG_LONG_MAX;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    vector<vector<int>> divisors(n + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; j += i)
            divisors[j].push_back(i);
    vector<int> arr;
    vector<vector<int>> facs;
    dfs(facs, divisors, arr, n);
    vector<int> prime, isPrime(n + 1, 1);
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= n; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    ll ans = LONG_LONG_MAX;
    for(auto& fac : facs)
        ans = min(ans, cal(prime, fac));
    cout << ans << "\n";
};