/**
 * @Time : 2023/4/21-4:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

int primes[] = {2,3,5,7,11,13,17,19,23,29};
class Solution {
public:
    int squareFreeSubsets(vector<int>& nums) {
        vector<int> aux; // 本身就含有平方因子的元素 一定不能选 直接去掉
        for(int num : nums){
            if(num % 4 && num % 9 && num % 16 && num % 25)
                aux.push_back(num);
        }
        int n = aux.size(), u = (1 << 10) - 1, mod = 1e9 + 7;
        function<int(int)> factors = [](int num) -> int{
            int status = 0;
            for(int i = 0; i < 10 && primes[i] <= num; i++){
                if(num % primes[i] == 0)
                    status |= 1 << i;
            }
            return status;
        };
        // dp[i][j] : 截止元素i，因子状态为j的子集数目
        vector<vector<long>> dp(n + 1, vector(u + 1, 0l));
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++){
            // s 枚举前置状态 只有前置状态与当前状态无交集时 才能pick当前的元素
            for(int s = 0, cur = factors(aux[i - 1]); s <= u; s++){
                dp[i][s] = (dp[i][s] + dp[i - 1][s]) % mod;
                if(s & cur) continue;
                dp[i][s | cur] = (dp[i][s | cur] + dp[i - 1][s]) % mod;
            }
        }
        long res = 0;
        // 注意 由于有1的存在，状态0不代表空集，可能是选了1。但里面有一个是空集 要减去
        for(int i = 0; i <= u; i++)
            res += dp[n][i];
        return (int)((res - 1) % mod);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}