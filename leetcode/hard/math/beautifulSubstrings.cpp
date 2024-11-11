/**
 * @Time : 2023/11/26-5:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛373 t4
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 4e3 + 5, T =1e5;
unordered_set<char> st = {'a', 'e', 'i', 'o', 'u'};
vector<int> prime;
int init = []() {
    vector<int> isPrime(N + 1, 1);
    for(int i = 2; i <= N; i++){
        if(isPrime[i] == 0) continue; // 不是素数 跳过
        if((long)i * i >= LONG_LONG_MAX) continue;
        for(int j = i + i; j <= N; j += i) // 将素数的所有倍数标记成合数
            isPrime[j] = 0;
    }
    for(int i = 2; i <= N; i++)
        if(isPrime[i] == 1) prime.push_back(i);
    return 0;
}();
class Solution {
public:
    /*
     * 两个条件逐一分析
     * 1. 元音和辅音字母数量相等
     * 假设用c1和c2 表示截止i位置元音和辅音字母的数量，p1和p2表示截止j位置元音和辅音字母的数量 且 i < j
     * 如果区间[i + 1,j]上元音和辅音字母数量相等，就是 c1 - p1 = c2 - p2
     * 等价变化为 c1 - c2 = p1 - p2。如果只需要满足这个条件 用hash表记录 c1 - c2 出现的次数即可
     *
     * 2 元音和辅音字母数量的乘积为k的倍数
     * 假设区间[i + 1,j]上已经满足条件1，其元音和辅音字母数量相等，均为区间长度的一半
     * 区间长度记为l, l一定是偶数，元音和辅音字母数量均为 l / 2
     * 也就是说 (l / 2)^2 % k == 0 --> l*l / 4 = t * k (t = 1,2...)
     * --> l^2 = t*(4k) (t = 1,2...)
     * 也就是说 4k 是l^2的因子。
     * 如果将4k进行因式分解 4k = p1 ^ a1 * p2 ^ a2 * ... pn ^ an (pi表示质数，ai是该质数出现的次数)
     * 要能让4k 是l^2的因子，l需要被分解为 x * (p1 ^ a1/2 * p2 ^ a2/2 * ... pn ^ an/2) (注意是向上取整)
     * x是正整数，这样l^2 = x^2 * (p1 ^ a1/2 * p2 ^ a2/2 * ... pn ^ an/2) ^ 2，才能被4k整除
     *
     * 例如 4 * k = 2^2 * 3^3 * 5^1 (4k = 540) 时
     * l^2要能被4k整除 l至少得是 l = 1 * (2^1 * 3^2 * 5^1) = 1 * 90
     * l^2 = 8100, 是4k的15倍
     *
     * 令 y = p1 ^ a1/2 * p2 ^ a2/2 * ... pn ^ an/2
     * l = x * y, x是正整数。即区间长度为y的倍数
     * 边界满足什么情况时 能让区间长度为y的倍数，就是边界的下标对y取mod相同时，i % y = j % y
     * 例如 y = 3时 i = 1, j = 4，对3取mod都是1，区间[2,4]的长度正好是3的1倍
     * 因此如果只满足条件2，用hash表记录 下标对y取mod 出现的次数即可
     *
     * 但是1和2都需要满足，是两个集合的交集。那么将两个条件综合起来
     * 记录 (j % y) * 1e5 +  c1 - c2. 出现的次数
     * (使用1e5保证了c1-c2 不会对index % y的值造成影响，因为字符总数才5e4)
     * 如果前置位置也出现了相同的值 可以倒推出满足以上两个条件
     */
    long long beautifulSubstrings(string s, int k) {
        int n = s.size(), y = getY(k), c1 = 0, c2 = 0;
        unordered_map<long long, int> map;
        // 哨兵 可能符合条件的区间是[0, j]，那么其对应的i = -1, 对y取mod为 y - 1
        // 并且 [0, j] 上c1 == c2的话，就要求这个不存在的边界p1 == p2
        map[(y - 1) * T] = 1;
        long long res = 0;
        for(int j = 0; j < n; j++) {
            if(st.count(s[j])) c1++;
            else c2++;
            long long temp = (long long)T * (j % y) + c1 - c2;
            res += map[temp];
            map[temp]++;
        }
        return res;
    }

    int getY(int k) {
        k *= 4;
        int y = 1, i = 0;
        while(k > 1) {
            int a = 0;
            while(k % prime[i] == 0)
                k /= prime[i], a++;
            y *= (int)pow(prime[i], (a + 1) / 2);
            i++;
        }
        return y;
    }
};