/**
 * @Time : 2022/8/5-12:43 PM
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
     * 执行用时：116 ms, 在所有 C++ 提交中击败了99.41%的用户
     * 内存消耗：80.3 MB, 在所有 C++ 提交中击败了67.75%的用户
     *
     * 利用了均值不等式思想的贪心
     */
    int max_val = 1e6 + 1e5, mod = 1e9 + 7;
    int maximumProduct(vector<int>& nums, int k) {
        int min_val = find_min(nums, k);
        cout << min_val << endl;
        for(int num : nums)
            if(num < min_val) k -= (min_val - num);
        long res = 1;
        for(int num : nums){
            int mul = max(num, min_val);
            // 如果k还有剩余，且当前数会被加到最小值，可以再给他+1
            // 并且这样一定能用完k，因为得到min_val后剩余的k
            // 已经不足以让所有值为min_val的数集体+1，否则最小值就是min_val + 1了
            if(k > 0 && mul == min_val)
                mul++, k--;
            res = (res * (long)mul) % mod;
        }
        return (int)res;
    }

    int find_min(vector<int>& nums, int k){
        int lo = 0, hi = max_val;
        while (lo < hi){
            int mid = (lo + hi + 1) >> 1;
            if(check(nums, k, mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    bool check(vector<int>& nums, int k, int val){
        for(int num : nums){
            if(num < val) k -= val - num;
            if(k < 0) break;
        }
        return k >= 0;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}