/**
 * @Time : 2023/9/18-5:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 选中的人数为a
 * nums[i] = nums[j] = b
 * 如果 b < a 那么i和j都应该被选中 才会开心
 * 如果 b = a i和j怎么都不会开心
 * 如果 b > a 那么i和j不应该被选中
 * 所以值相等的人 要么都被选中 要么都不被选中
 */
class Solution {
public:
    int countWays(vector<int>& nums) {
        int n = nums.size();
        vector<int> count(n, 0);
        for(int num : nums)
            count[num]++;
        vector<vector<int>> arr;
        for(int i = 0; i < n; i++)
            if(count[i]) arr.push_back({i, count[i]});
        int m = arr.size(), res = 0;
        if(arr[0][0] > 0) res++; // 都不选
        if(arr[m - 1][0] < n) res++;
        for(int i = 0, sum = 0; i < m - 1; i++) {
            int b1 = arr[i][0], b2 = arr[i + 1][0];
            sum += arr[i][1];
            if(b1 < sum && b2 > sum) res++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}