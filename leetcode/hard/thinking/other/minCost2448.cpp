/**
 * @Time : 2022/10/24-8:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * sum:所需的代价之和
     * add 表示 val + 1 要增加的cost之和，reduce则是 val + 1要减少的cost之和
     * 假定从0开始枚举val，那么reduce的初值就是 sum(cost)
     * t[i]表示值为i的所有num的cost之和。
     *
     * 那么枚举到i时 sum = sum + add - reduce
     * 然后 add += t[i], reduce -= t[i]
     */
    long long minCost(vector<int>& nums, vector<int>& cost) {
        int n = nums.size();
        long long sum = 0, add = 0, reduce = 0, max_val = 1e6;
        vector<int> t(max_val + 1, 0);
        for(int i = 0; i < n; i++){
            reduce += cost[i];
            sum += (long long) nums[i] * cost[i];
            t[nums[i]] += cost[i];
        }
        long long res = sum;
        for(int i = 1; i <= max_val; i++){
            sum = sum - reduce + add;
            res = min(res, sum);
            reduce -= t[i], add += t[i];
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}