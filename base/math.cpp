/**
 * @Time : 2023/5/17-6:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6, mod = 1e9 + 7;
typedef long long ll;
typedef unsigned long long ull;
/*
 * 一些常用的数轮结论 持续记录 持续收录
 * 1. 1e9以内的自然数 其因子个数的量级在1e2
 * 最多因子的数是735134400 共有512个因子
 * 2. 在int数据类型范围内 因子个数的量级 1e3
 * 最多因子的数是1745944200 共有1536个因子
 */
/*
 * 求mod意义下的逆元
 */
// qPow(total, mod - 2, mod);
ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

// 预处理阶乘 和 阶乘的逆元
ll x[N], invF[N];
int init = []() -> int {
    x[0] = 1;
    invF[0] = qPow(1, mod - 2);
    for (int i = 1; i < N; i++) {
        x[i] = x[i - 1] * i % mod;
        invF[i] = qPow(x[i], mod - 2);
    }
    return 0;
}();

// 组合数 C(n,a) n个元素取a个
ll C(int n, int a) {
    return x[n] * invF[n - a] % mod * invF[a] % mod;
}

// A(n,a) n个元素取a个并且全排列
ll A(int n, int a) {
    return x[n] * invF[n - a] % mod;
}

/*
 * 数论 Diophantine 方程，利用扩展欧几里得定律
 *
 * 形如 ax + by = c，其中a b c是已知的整数 (x,y)是要求解的整数对
 * 是否有解 先计算 g = gcd(a, b)，如果 c % g = 0，则有解
 * 要求解c1和c2，方程有解必须满足 a % g = 0, g = gcd(A,B)
 * 将方程转换为 x * a / g + y * b / g = c / g
 * 整理形式 x / g * a + y / g * b = c / g
 * x * (g / c) / g * a + y * (g / c) / g * b = 1  （t1）
 *
 * 扩展欧几里得算法求 gcd(a,b)，还可以得出一组系数x和y使得
 * ax + by = gcd(a,b)
 * 于是通过扩展欧几里得算法得出一组解 x0, y0 后
 * x0 * a + y0 * b = g
 * x0 / g * a + y0 / g * b = 1 (t2)
 * 将式子t1和t2进行对比，从形式上可以得出
 * 所以 x * g / c = x0, y * g / c = y0, 由此得到x和y的一组特解
 * xs = c * x0 / g, ys = c * y0 / g
 * 通解答为 x = xs + b / g * k, y = ys - a / g * k
 */
// 扩展欧几里得算法求x0和y0，会存放在变量x和y中，a和b就是标注 方程中的系数
int exgcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// 排列组合方法、公式
/*
 * 隔板法
 * 解决的问题：将x个相同的物品 放入y个相同的箱子中 允许某个箱子为空也允许某个箱子放多个物品
 *
 * 可以想象成 有x + y - 1个空白点 然后将其中 y-1 个点放置隔板
 * 有 y-1 个隔板，就划分出了y个箱子。并且剩余的x个空白点 就是要分配的物品
 * 两个隔板之间的空白点 就是放入某个箱子中的物品数量
 * 其中第一个板子左边、最后一个板子右边的空白点 就是放入第一个、最后一个箱子的物品
 * 相邻的两个隔板之间就意味着对应的箱子不放入物品
 * 因此所有可能的方案数就是 组合数C(x + y - 1, y - 1)
 */

/*
 * 第二类斯特林数
 * 解决的问题：将n个不同的元素拆分为m个非空集合的方案数 记为S(n, m)
 * 通俗说就是：将n个不同的球放入m个相同的箱子（且箱子均非空）的方案数
 * 1. n-1个元素已经拆分为m个非空集合，那么第n个元素可以放到m个集合中的任意一个
 *    S(n - 1, m) * m
 * 2. n-1个元素只拆分为m-1个非空集合，那么第n个元素必须放到第m个集合中
 *    S(n - 1, m - 1)
 * S(n, m) = S(n - 1, m) * m + S(n - 1, m - 1)
 * 边界条件
 * S(0,0) = 1. 0个元素0个集合 只有一种方案
 * S(n,n) = 1. n个元素要拆分到n个集合中 必须每个集合一个元素 只有一种方案
 * S(n,0) = 0. n个元素放到0个集合中 不可能 因此是0种方案
 * S(n,m) = 0 对任意的 m > n. n个元素要拆分到多于n个非空集合 不可能 因此是0种方案
 *
 * 还能解决的问题
 * 1.将n个不同的球放入m个不同的箱子（且箱子均非空）的方案数
 * 将n个不同的球先拆分为m堆 S(n, m)，然后每一堆对应一个箱子
 * 第一堆可选m个箱子，第二堆可选(m-1)个箱子.... 箱子与堆的对应方案有m!种（也就是全排列）
 * 总的方案数就是 m! * S(n, m)
 *
 * 2.将n个不同的球放入m个不同的箱子 箱子允许为空
 * 可以枚举有多少个箱子为空，先通过组合数挑出cnt个空箱子 C(m, cnt)
 * 然后剩下的 m - cnt 个箱子就是非空的了 S(n, m - cnt) * (m - cnt)!
 * 总的方案数就是 sum {C(m, cnt) * S(n, m - cnt) * (m - cnt)!}
 * 例如 LC3317
 */
const int N1 = 1e3 + 5, M1 = 1e3 + 5;
ll S[N1][M1];

int dfs(int n, int m) {
    if (S[n][m] != -1) return S[n][m];
    if ((n == 0 && m == 0) || n == m) return S[n][m] = 1;
    if (m == 0 || m > n) return S[n][m] = 0;
    return S[n][m] = (dfs(n - 1, m) * m % mod + dfs(n - 1, m - 1)) % mod;
}

int init1 = []() -> int {
    memset(S, -1, sizeof(S));
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < M1; j++)
            dfs(i, j);
    }
    return 0;
}();

/*
 * 给定一个字符串表全是0~9但数字字符，给定模数mod
 * v[l,r]表示 s[l,r]上的数字（可以有前导0）% mod 的结果
 * 思路参考字符串hash的做法
 */
int power10[N], h[N];

void str_mod(string &s) {
    // 参数s已经在前缀添加一个哨兵字符 有效下标从1开始
    int n = s.size() - 1;
    power10[0] = 1;
    for (int i = 1; i <= n; i++) {
        h[i] = (h[i - 1] * 10 + s[i] - '0') % mod;
        power10[i] = power10[i - 1] * 10 % mod;
    }
}

int get_mod(int l, int r) {
    return (((h[r] - h[l - 1] * power10[r - l + 1]) % mod) + mod) % mod;
}

/*
 * Pollard-Rho算法
 * 在所求的数很大时 快速分解质因数 可以得到所有质因数
 */
ll bmul(ll a, ll b, ll m) {  // 快速乘
    ull c = (ull) a * (ull) b - (ull) ((long double) a / m * b + 0.5L) * (ull) m;
    if (c < (ull) m) return c;
    return c + m;
}

ll qpow(ll x, ll p, ll mod) {  // 快速幂
    ll ans = 1;
    while (p) {
        if (p & 1) ans = bmul(ans, x, mod);
        x = bmul(x, x, mod);
        p >>= 1;
    }
    return ans;
}

bool Miller_Rabin(ll p) {  // 判断素数
    if (p < 2) return false;
    if (p == 2) return true;
    if (p == 3) return true;
    ll d = p - 1, r = 0;
    while (!(d & 1)) ++r, d >>= 1;  // 将d处理为奇数
    for (ll k = 0; k < 10; ++k) {
        ll a = rand() % (p - 2) + 2;
        ll x = qpow(a, d, p);
        if (x == 1 || x == p - 1) continue;
        for (int i = 0; i < r - 1; ++i) {
            x = bmul(x, x, p);
            if (x == p - 1) break;
        }
        if (x != p - 1) return false;
    }
    return true;
}

ll Pollard_Rho(ll x) {
    ll s = 0, t = 0;
    ll c = (ll) rand() % (x - 1) + 1;
    int step = 0, goal = 1;
    ll val = 1;
    for (goal = 1;; goal *= 2, s = t, val = 1) {  // 倍增优化
        for (step = 1; step <= goal; ++step) {
            t = (bmul(t, t, x) + c) % x;
            val = bmul(val, abs(t - s), x);
            if ((step % 127) == 0) {
                ll d = gcd(val, x);
                if (d > 1) return d;
            }
        }
        ll d = gcd(val, x);
        if (d > 1) return d;
    }
}

// 质因数分解
vector<ll> factor(ll n) {
    vector<ll> factors;
    if (n == 1) return factors;
    if (Miller_Rabin(n)) {
        factors.push_back(n);
        return factors;
    }
    ll d = Pollard_Rho(n);
    vector<ll> left = factor(d), right = factor(n / d);
    factors.insert(factors.end(), left.begin(), left.end());
    factors.insert(factors.end(), right.begin(), right.end());
    return factors;
}

vector<ll> get_factor(int num) {
    srand((unsigned) time(NULL)); // 必须的
    return factor(num);
}
/*
 * ******************** Pollard-Rho算法 end
 */

/*
 * 一个分解较小的数的质因子的方法
 */
multiset<int> get_factor2(int num) {
    multiset<int> st;
    for(int i = 2; i <= sqrt(num); i++) {
        while(num % i == 0) {
            st.insert(i);
            num /= i;
        }
    }
    if(num > 1) st.insert(num);
    return st;
}

/*
 * 将一个数分解成 多个大于1的数相乘的形式 会包括其自身那个解
 * 需要预处理数的因子 divisors[num]
 */
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

/*
 * 容斥原理
 * 求n个集合的并集有多少个元素
 * 枚举集合数量从1到n
 * 奇加偶减：集合数量为奇数个时，加上其交集的个数；集合数量为偶数时，减去其交集的个数
 * 且固定数量的集合要枚举出所有组合
 * 例如有n=3时，abc，集合数量为2时，共有3个组合ab,ac,bc
 *
 * 例如求|A并B并C| = |A| + |B| + |C| - |A交B| - |A交C| - |B交C| + |A交B交C|
 */

/*
 * 倍数容斥
 * 通过集合之间的倍数（或因数）关系，用容斥原理求解 f[i]（恰好为 i）的数量。
 * 常和gcd / lcm相关计数问题一起出现
 *
 * 例如：求满足gcd为i(i = 1,2,...,n)的（子序列/数对/连通分量）的数量
 *
 * 记 g[i]为gcd值是"i的倍数"时的总方案数，f[i]为gcd值恰好为i的总方案数
 * 求g数组的时候，含有因子i的数num，最终其gcd才会是i的倍数
 * 需要“按num的因子分组”，也就是将num放到所有它的因子的集合中
 * 分组完成后，再根据问题，求出该组对应的g[i]
 *
 * g[i] = f[i] + f[2*i] + f[3*i] + ... + f[k*i]
 * f[i] = g[i] - sum{f[2*i] + f[3*i] + ... + f[k*i]}
 * 先求出所有g[i]，然后从大到小计算f[i]，因为小的答案依赖于大的结果
 * 对于所有的i计算sum{f[2*i] + f[3*i] + ... + f[k*i]}，其实就是调和级数求和
 * i = 1, 要计算 f[2] + f[3] + ... f[n]
 * i = 2, 要计算 f[4] + f[6] + ... f[n]
 * ...
 * 因此由g求f的过程，总的时间复杂度是nlog(n)
 * 例题 LC3312,LC3671
 *
 * 例如：求满足lcm为i(x = 1,2,...,n)的（子序列/数对/连通分量）的数量
 * 记 l[i]为lcm值是"i的因子"时的总方案数，f[i]为lcm值恰好为i的总方案数
 * (example, i = 10, l[i]就是所有lcm=1,2,5,10的总方案数)
 * (如果有num1 * c1 = i, num2 * c2 = i, 那么lcm(num1, num2)一定是i的因子)
 * 求l数组的时候，所有num * c = i的数，最终其lcm会是i的因子
 * 需要“按num的倍数分组”，也就是将num放到所有它的倍数的集合中（当然有个上限控制）
 * （example:如果当前数num是3，那么我应该把它放到i=3,6,9,12...的分组中）
 * 分组完成后，再根据问题，求出该组对应的l[i]
 *
 * l[i] = f[i] + ... +f[c2] + f[c1]
 * f[i] = l[i] - sum{f[c(n-1)] + ... + f[c2] + f[c1]}
 * sum{f[c(n-1)] + ... + f[c2] + f[c1]}的意义是：i除了其本身外的所有因子求和
 * 其中c1,c2...指的是i的因子(example, i = 10, c1 = 1, c2 = 2, c3 = 5, c4 = 10)
 * 先求出所有l[i]，然后从小到大计算f[i]，因为大的答案依赖于小的结果
 * （分组依据及计算方向都刚好和gcd的问题相反）
 * 因为i的因子个数比较少，整体时间复杂度可接受
 */
