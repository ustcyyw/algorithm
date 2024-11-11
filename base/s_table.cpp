/**
 * @Time : 2024/7/11-7:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : st表
 */
 /*
  * 对于不可修改情况下，多组询问求取区间某些值 可以使用st表
  * 只要是满足 f(a,a) = a这个性质的求值 都可以使用
  * 比如 min max gcd lcm or and
  * 静态预处理 时间复杂度 nlogn 后 单次查询是o(1)的
  *
  * 利用倍增的思想实现
  * 定义dp[i][j]：以i为左端点，长度为2^j的区间上的xxx值，也就是区间[i, i + 2^j - 1]上的xx值
  * dp[i][0] = nums[i]
  * dp[i][j] = f(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1])
  */
 /*
  * 注意：！ xor不可以用st表维护 因为xor(a, a) = 0
  */
#include<bits/stdc++.h>
using namespace std;

class STable {
    int n, m;
    vector<vector<int>> dp;

    int f(int num1, int num2) {
        // 可以替换为其它函数
        return max(num1, num2);
    }

public:
    STable(vector<int>& nums) {
        n = nums.size(), m = log2(n);
        dp.assign(n, vector(m + 1, 0));
        for(int i = 0; i < n; i++)
            dp[i][0] = nums[i];
        for(int j = 1; j <= m; j++) {
            int pj = 1 << (j - 1);
            for(int i = 0; i + pj < n; i++) {
                dp[i][j] = f(dp[i][j - 1], dp[i + pj][j - 1]);
            }
        }
    }

    int search(int l, int r) {
        int len = r - l + 1, j = log2(len);
        return f(dp[l][j], dp[r - (1 << j) + 1][j]);
    }
};

int main(){

    
    cout << 0 << endl;
}