/**
 * @Time : 2025/1/21-11:23 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2060F 2242 数学 组合数学
 */
 /*
  * 数组所有元素乘积为x 数组的元素是1或者x的一组因子
  * 首先需要将x拆分成多个数乘的形式 x = num1 ^ p1 * nums2 ^ p2 ... numsi ^ pi
  * m = p1 + p2 + ... pi
  * 对于某一个具体的拆分方法 计算可能性
  * 数组的长度len的取值范围是[m,n]
  * 先将长为len的数组中挑出m个位置放这些因子 C(len, m)
  * 然后这些因子本身需要排列，假设其排列方案数为cnt（求cnt就是有重复元素的全排列问题）
  * 针对这一具体拆分方法的方案数就是
  * sum{cnt * C(len, m), for len in [m, n]}
  * = cnt * sum{C(len, m), for len in [m, n]}
  * = cnt * C(n + 1, m + 1)， 这里用了组合数的公式
  * 注意m最多是18，因为所求的x最大是1e5，都拆分为2的乘积，也最多18个2
  * 所以在计算C(n + 1, m + 1)可以直接使用组合数阶乘公式，近似认为o1复杂度
  * 计算时候涉及对 m + 1 阶乘的逆元，并且求cnt时也涉及到阶乘的逆元
  * 因此可以预处理所有20以内的阶乘及逆元
  *
  * 多组case，每次都要从x = 1计算到x = k
  * 都涉及到拆分成多个数乘的形式，这个也进行预处理
  * 计算过程中需要用到每个数的因子，也先预处理出来
  * 最终不关注具体因子是多少，只关注多少个因子，以及相同因子的出现情况
  * 进一步，需要的信息只有m和cnt，可以在得到拆分方案的时候就把这两个值计算出来
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 998244353, M = 20;
int T, n, k;

vector<int> divisors[N];
multimap<int, ll> factors[N];
ll x[M], invF[M];

ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

void dfs(multimap<int, ll>& fac, vector<int>& arr, int num) {
    if(num == 1) {
        map<int, int> mp;
        for(int m : arr)
            mp[m]++;
        ll base = x[arr.size()];
        for(auto& p : mp)
            base = base * invF[p.second] % mod;
        fac.insert({arr.size(), base});
        return;
    }
    int pre = arr.empty() ? -1 : arr.back();
    for(int d : divisors[num]) {
        if(d == 1 || d < pre) continue;
        if(num / d < d && num / d != 1) continue;
        arr.push_back(d);
        dfs(fac, arr, num / d);
        arr.pop_back();
    }
}

int init = []() {
    // 预处理因子
    for (int i = 1; i < N; ++i)
        for (int j = i; j < N; j += i)
            divisors[j].push_back(i);
    // 预处理组合数
    x[0] = 1;
    invF[0] = qPow(1, mod - 2);
    for (int i = 1; i < M; i++) {
        x[i] = x[i - 1] * i % mod;
        invF[i] = qPow(x[i], mod - 2);
    }
    // 预处理拆分成多个数相乘的情况
    vector<int> arr;
    for (int i = 2; i < N; i++) {
        dfs(factors[i], arr, i);
    }
    return 0;
}();

ll comb(int m, int c) {
    ll base = 1;
    for(int j = m; j > m - c; j--)
        base = base * j % mod;
    return base * invF[c] % mod;
}

void solve(int num) {
    ll ans = 0;
    for(auto& p : factors[num]) {
        ans = (ans + p.second * comb(n + 1, p.first + 1)) % mod;
    }
    cout << ans << " ";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> k >> n;
        cout << n << " ";
        for(int num = 2; num <= k; num++)
            solve(num);
        cout << "\n";
    }
};