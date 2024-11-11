/**
 * @Time : 2023/9/18-10:59 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
     * 完全平方数 质因子是成对出现的
     * 可以枚举出现奇数次的质因子（或者他们的组合），然后乘以成对出现的质因子
     * 这样就能保证这一系列的数相乘，质因子总是成对出现
     *
     * 首先 成对出现的质因子系列，就可以用1,2,3...的平方来表示
     * 1 4 9 16...
     * 选择出现奇数次的质因子 如 6
     * 那么这一系列的数就是
     * 6 24 54 96... 最多有100个数，因为n最大为1e4
     * 任意两个数之积 6 * 54 = 6 * 6 * 9
     * 24 * 96 = 4 * 6 * 16 * 6
     * 6已经是成对出现了，满足题目要求
     *
     * 在枚举出现奇数次的质因子时，可以借鉴素数筛选的思路优化
     */
vector<int> aux;
int init = [](){
    for(int i = 1; i * i <= 1e4; i++)
        aux.push_back(i * i);
    return 0;
}();
class Solution {
public:
    long long maximumSum(vector<int>& nums) {
        int n = nums.size();
        vector<bool> marked(n + 1, false);
        function<long long(int)> get_sum = [&](int base) -> long long {
            long long sum = 0;
            for(int i = 0; i < aux.size() && aux[i] * base <= n; i++)
                sum += nums[aux[i] * base - 1];
            return sum;
        };
        long long res = 0;
        for(int i = 1; i <= n; i++) {
            res = max(res, (long long)nums[i]);
            if(marked[i]) continue;
            for(int j = i; i != 1 && j <= n ; j += i)
                marked[j] = true;
            res = max(res, get_sum(i));
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}