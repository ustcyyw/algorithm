/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
 /*
  * 按题目要求 城市之间的可达性是有方向的
  * 只有 j < i 且gcd(a[i], a[j]) > 1 的城市可以到达a[j]
  * 令 f[i]到达地i个城市的方法
  * f[1] = 1 表示从第一个城市出发 仅有一种方法
  * f[i] = sum{f[j], for j < i && gcd(a[i], a[j]) > 1}
  *
  * gcd(a[i], a[j]) > 1 这个条件 只需要关注两个数是否有公共质因子即可
  * 也就是说 只需要找到某个数有哪些质因子 而不必关注某一个质因子出现了几次
  * 比如8，本质上只能由拥有2这个质因子的城市走过来
  * 因而第一步 可以先将每个城市化简 将其表示为质因子集合
  *
  * 假如有一个数a[i]的因子构成是2*3*5
  * 那么前置位置 拥有质因子的2、3、5的城市都能转移过来
  * 用c[num]表示前置位置含有因子组合为num的城市的总方法数
  * 会首先想到 f[i] = c[2] + c[3] + c[5]
  * 但是这明显会有重复 比如前面有过一个城市拥有质因子2*3或者2*5或者2*3*5，就被重复计算了
  * f[i]是质因子2、3、5的城市的并集 由并集的内方法数求和得到 想到容斥定律
  *
  * 容斥原理，求n个集合的并集有多少个元素
  * 枚举集合数量从1到n
  * 奇加偶减：集合数量为奇数个时，加上其交集的个数；集合数量为偶数时，减去其交集的个数
  * 且固定数量的集合要枚举出所有组合
  * 例如有n=3时，abc，集合数量为2时，共有3个组合ab,ac,bc
  * 例如求|A并B并C| = |A| + |B| + |C| - |A交B| - |A交C| - |B交C| + |A交B交C|
  *
  * 借助容斥原理 计算f[i]时 先求a[i]的质因子集合（最多有8个 取最小的8个质数相乘就会超过1e6）
  * 然后枚举质数的子集 代入公式
  * 算出f[i]后 再更新c
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, M = 1000000, mod = 998244353;
int T, n, nums[N];
ll f[N], c[M];

vector<int> prime, isPrime;
int init = []() {
    isPrime = vector(M + 1, 1);
    for (int i = 2; i <= M; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= M; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    return 0;
}();

vector<int> cal(int num) {
    vector<int> ans;
    for(int i = 0; i < prime.size() && num > 1; i++) {
        if(isPrime[num]) {
            ans.push_back(num);
            break;
        }
        if(num % prime[i] == 0) ans.push_back(prime[i]);
        while(num % prime[i] == 0)
            num /= prime[i];
    }
    return ans;
}

int solve() {

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    }
};