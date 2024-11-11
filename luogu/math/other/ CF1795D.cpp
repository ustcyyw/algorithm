/**
 * @Time : 2024/3/7-10:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 同一个三角形 三个顶点同一种颜色 一条边都取不了。
  * 而且会导致另外一个三角形也是三个顶点同一种颜色，只不过颜色相反
  * 因此 要让三角形三个顶点中两个同色 另外一个不同色 （红红蓝、红蓝蓝）
  * 并且为了让取值和最大 在同一个三角形中 应该让单独颜色放在价值最大的两边的公共顶点
  * 1. 三边不一样 或者 仅有两条边相同但这两条边都是价值大的 单独颜色的顶点唯一确定
  * 2. 仅有两条边相同且这两条边价值小 单独颜色的顶点有2个放置方法 这两条小边中任意一边和大边的公共顶点
  * 3. 三边相等，单独颜色的顶点有3个放置方法
  * 方案的安排就是将 n/3 个三角形，挑出其中一半 颜色方案为 红红蓝，那么另外一半即为 红蓝蓝
  * 可能的方案数是组合数 C(n/3, n/6)
  * 另外对于一个三角形 方案数单独计算 最后累乘
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MOD = 998244353, N = 3e5 + 5;
int n, T, nums[N];
ll inv[N / 3 + 5];
int init = []() -> int {
    inv[1] = 1;
    for (int i = 2; i <= N / 3; i++) // 线性逆元
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    return 0;
}();
/*
* 求C(n,i)
* 根据公式 C(n,i) = (n - i + 1) / i * C(n,i - 1)
* 涉及到取摸到时候要使用乘法逆元
*/
ll combination(int m, int k){
    // 递推求组合数，初值 C(k, 0) = 1
    ll ans = 1;
    for (int i = 1; i <= k; i++)
        ans = ans * (m - i + 1) % MOD * inv[i] % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    ll factor = 1;
    for(int i = 0, a, b, c; i < n; i += 3) {
        cin >> a >> b >> c;
        if(a == b && b == c) factor = factor * 3 % MOD;
        else {
            vector<int> temp = {a, b, c};
            sort(temp.begin(), temp.end());
            if(temp[0] == temp[1]) factor = factor * 2 % MOD;
        }
    }
    cout << (combination(n / 3, n / 6) * factor % MOD) << "\n";
};