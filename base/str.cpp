/**
 * @Time : 2023/2/25-7:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;

/*
 * 字符串hash
 */

/*
* 记h[i]为str[0...i - 1]的hash值，且h[0] = 0
* (类似于前缀和一样，hash数组的下标与字符串的下标有1的差距)
* h[i] = h[i - 1] * p + str[i - 1] 一般p取131或者13331
* (也可以理解为将字符串转化为p进制数)
* 注意：使用无符号数，溢出的时候就是自动进行了取模
*
* 通过字符串hash值，可以快速地求出某个子串地hash值，这也类似于前缀和
* str[l, r]的hash值为 h[r + 1] - h[l] * p ^ (r - l + 1)
*
* 减去 h[l] * p ^ (r - l + 1) 是因为，在计算至h[r + 1]时，h[l]这一部分被乘了p ^ (r - l + 1)次
* 也就是p进制数中将高位数字去掉
*
* 需要使用p ^ (r - l + 1)，因而在计算h的过程中也同时计算p的幂次数组x
* x[0] = 1
* x[i] = p * x[i - 1]
*/
const int P = 13331;
void str_hash(string &s) {
    int n = s.size();
    vector<ull> h(n + 1, 0), x(n + 1, 0);
    h[0] = 0, x[0] = 1;
    for (int i = 1; i <= n; i++) {
        h[i] = h[i - 1] * P + s[i - 1];
        x[i] = x[i - 1] * P;
    }
}

ull get_hash(vector<ull> &h, vector<ull> &x, int l, int r) {
    return h[r + 1] - h[l] * x[r - l + 1];
}

// 单纯算一个字符串整体的hashcode
ull str_hash_code(string &s) {
    int n = s.size();
    ull hash = 0;
    for(int i = 1; i <= n; i++)
        hash = hash * P + s[i - 1];
    return hash;
}

/*
 * 双hash 注意数据类型选用ll
 * 注意模版中s的有效下标从1开始 所以在init_hash函数中第二行在开头位置添加'.'
 */
const int N = 1e5 + 5;
const ull B1 = 131, P1 = 1e9 + 7;      // 第一个哈希参数
const ull B2 = 29, P2 = 998244353;  // 第二个哈希参数

ull H1[N], H2[N];  // 哈希值
ull P1_pow[N], P2_pow[N];  // 幂次表

void init_hash(string& s) {
    int n = s.size();
    s = '.' + s;
    P1_pow[0] = P2_pow[0] = 1;
    for (int i = 1; i <= n; i++) {
        P1_pow[i] = P1_pow[i - 1] * B1 % P1;
        P2_pow[i] = P2_pow[i - 1] * B2 % P2;
    }
    for (int i = 1; i <= n; i++) {
        H1[i] = (H1[i - 1] * B1 + s[i]) % P1;
        H2[i] = (H2[i - 1] * B2 + s[i]) % P2;
    }
}

// 获取子串 [l, r] 的哈希值
pair<ull, ull> get_hash(int l, int r) {
    ull hash1 = (H1[r] - H1[l - 1] * P1_pow[r - l + 1] % P1 + P1) % P1;
    ull hash2 = (H2[r] - H2[l - 1] * P2_pow[r - l + 1] % P2 + P2) % P2;
    return {hash1, hash2};
}

/*
 * z函数 扩展kmp算法 线性时间复杂度
 * 给定字符串s，长度为n
 * 定义z[i]为 s和它的后缀字符串s[i, n - 1]的最长公共前缀(lcp)的长度
 * 例如       s = a a a b a a a b c
 * 对应的z函数为   9 2 1 0 4 2 1 0 0
 *
 * z-box
 * 对于子串s[i,n-1],与s前缀匹配的区间是 [i, i + z[i] - 1],这个匹配区间就叫z-box
 * 维护右端点最靠右的z-box,为了简便,记为区间[l,r], s[l,r]是s的一个前缀
 * 在计算i时,保证了l <= i
 *
 * 通过z-box来简化计算
 * s[l,r]是s的一个前缀,即 s[l,r] = s[0, r - l]
 * 计算z[i]时
 * 1.如果i > r,以i为起点暴力计算即可
 * 2.如果i <= r,此时有 s[i, r] = s[j, r - l], j = i - l
 *      2.1 如果 j + z[j] - 1 < r - l (j的匹配区间没有超过z-box对应的前缀区间)
 *          在 r - l的左边s[j, n - 1]与s就出现了不匹配
 *          因为 s[i, r] = s[j, r - l], 那么在 r 右边也出现不匹配，lcp也就找到了
 *          z[i] = z[j]
 *      2.2 j + z[j] - 1 >= r - l
 *          s[j, r - l]与s前缀完全匹配，那么s[i, r]与s前缀完全匹配
 *          但是从r+1这个位置还是否匹配 需要继续检查
 *   对于情况2的两种case，可以归纳为 先把s[i, n - 1]与s的最长前缀长度预设为 z[i] = min(z[j], r - i + 1)
 *   然后从 s[i + z[i]] 与 s[z[i]]开始进行逐字匹配 确定最长前缀。
 *   对于case2.1 在s[z[i]]就发现不匹配，直接结束；对于case2.2 就是从r+1开始匹配
 * 对于case1 也可以归纳为 z[i] = 0, 然后从s[i + z[i]]与s[z[i]]开始匹配
 *
 * 更新z-box：最靠右的右端点变化，就进行更新
 */

vector<int> z_function(string& s){
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = n;
    for(int i = 1, l = 0, r = 0; i < n; i++){
        if(i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}


/*
 * 马拉车算法 Manacher算法 线性时间复杂度内解决以某个点为中心的奇数长度的最长回文子串
 * 给定字符串s
 * p[i]：表示以s[i]为中心的最长回文字符串的扩展半径 那么以这个点为中心的回文串的长度就是 2 * p[i] + 1
 * 如 eabaf 中 p[2] = 1, 其对应的最长回文"aba"长度为3
 *
 * 利用已有信息 利用回文串的对称性
 *
 * 令mr为已经找到的回文子字符串能覆盖到的最右边边界 的索引
 * mc则为该mr对应的回文中心的索引
 *
 * 假设求i的时候 找到i关于mc的对称点j
 * x x x x x x x  x x x x x  x x x  (x表示该处是某个字符 是啥不重要 看位置)
 *       j     mc     i     mr
 *
 * 假设p[j] = 2 关于j有对称性 关于mc还有对称性 于是也能发现关于i有对称性
 * 要计算p[i]，在这个基础上继续扩展即可, 假设i的扩展半径为r， r = p[j]
 * x x x x x x x  x x x x x  x x x
 *       j     mc     i   mr
 *   a b   b a    a b   b a          (相同字母表示该处相等)
 * 但是p[j] = 3 由于mc的对称边界最右边就是mr，那么关于mc的对称信息 也受mr的限制
 * r = min(p[j], mr - i)
 */
vector<int> manacher(string& s) {
    int n = s.size(), mc = -1, mr = -1;
    vector<int> p(n, 0);
    for(int i = 1; i < n; i++) {
        int r;
        if(mr > i) {
            int j = 2 * mc - i;
            r = min(p[j], mr - i);
        } else r = 0;
        while(i + r < n && i - r >= 0 && s[i + r] == s[i - r]) r++;
        p[i] = r - 1; // while循环结束时 s[i + r] != s[i - r]或者已经超出边界了 因此扩展半径时r-1
        if(i + p[i] > mr) mr = i + p[i], mc = i;
    }
    return p;
}



/*
 * 后缀数组
 * 把s的每个后缀按字典序排列。排序序号从1开始，字符串的下标从1开始
 * sa[i]:排名为i的后缀的起始位置的下标
 * rk[i]:起始位置下标为i的后缀，排名为多少
 * 如 字符串 aba，其后缀的排序为 a, aba, ba，那么
 * sa[1] = 3, 对应的后缀是a; sa[2] = 1, 对应的后缀是aba; sa[3] = 2, 对应的后缀是ba
 * rk[1] = 2, rk[2] = 3, rk[3] = 1
 *
 * sa与rk互为逆映射。sa[rk[i]] = rk[sa[i]] = i
 *
 * height[i]: 排名为i和i-1的两个后缀的最长公共前缀(lcp)
 * 高度数组可以表示后缀的相似度
 * sa中相邻的两个后缀，相似度最高，公共前缀最长(lcp(i, i + 1) >= lcp(i, i + 2) >= ...)
 */

/*
 * 求sa数组：倍增法 + 桶排序
 * 倍增法：先对1个字母排序，再根据1个字母得出2个字母的排序，再根据2个字母的排序得出4个字母的排序
 * 双关键字联合使用，第一个关键字下标为i，其排序为rank[i]; 第二个关键字下标为i + w，排序为rank[i + w]
 * 其中w = 1,2,4,8...
 * 下文用 key1表示第一关键字; key2表示第二关键字
 * 用x表示key1的排序数组, x[i]:后缀编号为i的key1的排名
 * 用y表示key2排名对应的编号数组, y[i]:key2排名为i的后缀编号
 * 桶排序：
 * 先对key1的排序计数，使用c表示计数数组，然后求c的前缀和
 * 这样就知道key1对应的排序范围
 * 然后根据key2的排序，倒着放入key1的范围，就得到了最终排名
 * 比如 key1 排序为3的后缀共有3个，排序小于3的后缀的有x个
 * 求出c的前缀和后 c[3] = x + 3，这个关键字对应的排序是x + 1 ~ x + 3
 * 在这3个后缀中，以key2排序，排第三的，在最终排名的就是 x + 3，排第二的，在最终排名的就是 x + 3
 *
 * tip：x的参数是后缀编号，输出是排名
 * sa、y、c的参数是排名。sa和y输出是后缀编号
 */

const int N = 1e6;
int x[N], y[N], c[N], sa[N];

void get_sa(string &s) {
    memset(x, 0, sizeof(x)), memset(y, 0, sizeof(y));
    memset(c, 0, sizeof(c)), memset(sa, 0, sizeof(sa));
    int n = s.size(), m = 26; // m表示字符集的大小，也是桶的个数
    s = " " + s; // 因为后缀编号从1开始取，因此设置一个哨兵
    int i, w; // w表示倍增法中区间的长度
    // 初始化
    // 初始排名x[i]就是s[i]这个字符在字符集中的排序，并且进行桶排序的计数。
    // x[i] = s[i] - 'a' + 1，注意+1是要保证字母序最小的排名在1。根据字符集不同，可能要换字符排序映射
    for (i = 1; i <= n; i++) c[x[i] = s[i] - 'a' + 1]++;
    // 计数后求前缀和，得出key1对应的排序范围
    for (i = 1; i <= m; i++) c[i] += c[i - 1];
    // 根据key2的排序，倒着放入key1的范围，得到初始化的sa
    // x[i] 字符i的排序，c[x[i]]该字符的排序范围，倒序占用一个位置后，要减少1。
    // sa[c[x[i]]--] = i, c[x[i]]--这个排序对应的字符下标就是i
    for (i = n; i >= 1; i--) sa[c[x[i]]--] = i;

    // 倍增法
    for (w = 1; w <= n; w <<= 1) {
        int num = 0;
        // s[n - w + 1, n]这一部分后缀，没有key2，理解为key2无穷小
        // 因此key2最小从1开始，依次对应这部分后缀
        for (i = n - w + 1; i <= n; i++) y[++num] = i;
        // 除开无穷小的key2, 后缀排序从小到大查看，看对应的下标sa[i]，sa[i]如果在[w + 1, n]上，它就可以做为key2
        // 倍增区间长为w，这个key2对应的key1的位置就是sa[i] - w
        for (i = 1; i <= n; i++)
            if (sa[i] > w) y[++num] = sa[i] - w;

        // 更新了key2排名对应的后缀编号y后，进行与初始化类似的桶排序
        // step1 : 清空桶, 桶的个数为m
        for (i = 1; i <= m; i++) c[i] = 0;
        // step2 : 对key1的排序序号进行计数
        for (i = 1; i <= n; i++) c[x[i]]++;
        // step3 : 计数数组的前缀和，确定key1对应的排序区间
        for (i = 1; i <= m; i++) c[i] += c[i - 1];
        // step4 : 根据key2找到对应的后缀编号，在相应的排序区间上，倒序占用一个位置
        // y[i]: key2排序为i的后缀编号，x[y[i]]该后缀对应的key1的排序序号
        // c[x[y[i]]]: 此时应该占用的位置，也就是排序序号。
        // 那么这个排序序号对应的后缀编号（字符下标）就是y[i]
        for (i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];

        // 要更新x，且y已经没用了（因为倍增区间的长度变了，key2的信息要更新），就先用y来存x
        swap(x, y);
        int p = 0; // 表示key1的排名, 现在y表示key1的排序数组
        for (i = 1; i <= n; i++) {
            // sa[i]排序为i的后缀编号，y[sa[i]]该后缀key1的排名
            // sa[i] + w 这个后缀对应的第二个关键字的索引，y[sa[i] + w]就是该后缀的key2的排名
            // 如果key1和key2的排序都相等，这一轮排序后，新排序序列里，他们的排名都是p
            // 否则 新序列里排名会增加1
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + w] == y[sa[i - 1] + w]) x[sa[i]] = p;
            else x[sa[i]] = ++p;
        }
        if (p == n) break; // 排序完成
        m = p; // 更新字符集大小
    }
}


int rk[N], height[N];

void get_rk_and_height(string &s, int n) { // n为原字符串长度
    memset(rk, 0, sizeof(rk)), memset(height, 0, sizeof(height));
    int i, j, k = 0;
    for (i = 1; i <= n; i++) rk[sa[i]] = i;
    for (i = 1; i <= n; i++) { // 后缀编号为i的后缀的排名 rk[i]
        if (rk[i] == 1) continue; // rk为1的后缀，height[i] = 0, 不用计算
        if(k) k--;
        j = sa[rk[i] - 1]; // 当前排名-1的后缀的编号，也就是起始下标
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
        height[rk[i]] = k;
    }
}

class Solution {
public:

};

int main() {
    Solution s;

    cout << 0 << endl;
}