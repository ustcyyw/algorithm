/**
 * @Time : 2024/12/4-10:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3343 记忆化搜索 参考灵神题解
 */
 /*
  * 分析问题的时候 可以先把表达式写出来再观察
  */

 /*
  * 偶数下标和奇数下标的元素，就是在两个集合中的元素，记偶数下标的集合为set1,另外一个为set2
cnt[i]: 表示数字i一共有多少个
ai表示给set1数字i的个数，cnt[i] - ai就是给set2的数字i
在固定a0,a1...a9的情况下，答案就是确定的
set1的可能排列 (n/2)! / (a0!a1!...a9!)
set2的可能排列 (n - n/2)! / ((cnt[0] - a0)!...(cnt[9] - a9)!)
整体排列 (n/2)! * (n - n/2)! / (a0!(cnt[0] - a0)!a1!...a9!(cnt[9] - a9)!)
a0,a1...a9是变量 最终答案就是枚举满足约束的a0...a9，并加和
由于每一项中 (n/2)! * (n - n/2)! 都不变，将其单独提出来
要计算的就是 sum{1/(a0!(cnt[0] - a0)!a1!...a9!(cnt[9] - a9)!)}
涉及取mod，将除法转换为逆元来计算 形式上可以写成
sum{(a0!(cnt[0] - a0)! * a1!(cnt[1] - a1)!... * a9!(cnt[9] - a9)!)}
根据乘法结合律 sum{a0!(cnt[0] - a0)!} * sum{a1!(cnt[1] - a1)!... * a9!(cnt[9] - a9)!)}
假设已知第二项，现在只需要求sum{a0!(cnt[0] - a0)!}即可，那就枚举a0从0到cnt[0]即可

考虑到约束条件 也就是分给set1数字共n/2个，分给set1的数字和为sum/2
从0开始考虑分配 将ai个i分给set1，那么剩余的数字leftC - ai, 剩余的和为leftS - i * ai
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 90, mod = 1e9 + 7;
typedef long long ll;

long long qPow(long long x, long long y) {
    long long ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

// 预处理阶乘 和 阶乘的逆元
long long x[N], invF[N];
int init = []() -> int {
    x[0] = 1;
    invF[0] = qPow(1, mod - 2);
    for (int i = 1; i < N; i++) {
        x[i] = x[i - 1] * i % mod;
        invF[i] = qPow(x[i], mod - 2);
    }
    return 0;
}();

class Solution {
public:
    int cnt[10] = {0};
    vector<vector<vector<ll>>> cache;
    int countBalancedPermutations(string num) {
        int sum = 0;
        for(char c : num)
            sum += c - '0', cnt[c - '0']++;
        if(sum % 2 != 0) return 0;
        int n = num.length(), m = n / 2;
        cache = vector(10, vector(m + 1, vector(sum / 2 + 1, -1ll)));
        ll res = x[m] * x[n - m] % mod * dfs(0, m, sum / 2) % mod;
        return (int)res;
    }

    ll dfs(int i, int leftC, int leftS) {
        if(i == 10) {
            return leftC == 0 && leftS == 0 ? 1 : 0;
        }
        if(cache[i][leftC][leftS] != -1)  return cache[i][leftC][leftS];
        long ans = 0;
        for(int c = 0; c <= min(cnt[i], leftC) && leftS - i * c >= 0; c++) {
            long temp = dfs(i + 1, leftC - c, leftS - i * c);
            ans = (ans + invF[c] * invF[cnt[i] - c] % mod * temp % mod) % mod;
        }
        return cache[i][leftC][leftS] = ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}