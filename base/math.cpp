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
 * 分解质因数 通过Pollard-Rho算法实现
 * 下面的模版是只提取出不同的质因子
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

void fac(set<ll>& st, vector<ll>& ans, ll x) {
    if(x == 1) return;
    if (Miller_Rabin(x)) {
        if(!st.count(x))
            ans.push_back(x), st.insert(x);
        return;
    }
    ll p = x;
    while (p >= x) p = Pollard_Rho(x);
    while ((x % p) == 0) x /= p;
    fac(st, ans, x), fac(st, ans, p);
}

vector<ll> get_prime_factor(ll num) {
    srand((unsigned) time(NULL));
    set < ll > set;
    vector<ll> ans;
    fac(set, ans, num);
    return ans;
}

ll cal(vector<ll> &f, ll total) {
    ll ans = 0;
    int n = f.size(), u = (1 << n) - 1;
    for (int s = 1; s <= u; s++) {
        ll num = 1, cnt = 0;
        for (int j = 0; j < n; j++) {
            if ((1 << j) & s)
                num *= f[j], cnt++;
        }
        ll temp = total / num;
        if (cnt % 2 == 1) ans = (ans + temp) % mod;
        else ans = (ans - temp + mod) % mod;
    }
    return ans;
}

