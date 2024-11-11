/**
 * @Time : 2024/5/19-10:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛398 t2 前缀和
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> sum(n + 1, 0);
        sum[1] = 1; // 表示第一个数是符合条件的
        for(int i = 2; i <= n; i++)
            sum[i] = sum[i - 1] + (nums[i - 1] % 2 != nums[i - 2] % 2);
        vector<bool> res;
        for(auto& query : queries) {
            int l = query[0], r = query[1];
            if(l == r) res.push_back(true);
            else res.push_back(sum[r + 1] - sum[l + 1] == r - l);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}