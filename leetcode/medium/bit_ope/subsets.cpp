/**
 * @Time : 2022/6/9-4:48 PM
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
     * 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
     * 内存消耗：6.7 MB, 在所有 C++ 提交中击败了94.96%的用户
     *
     * 用位运算来处理子集
     */
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        res.push_back({});
        int state = (1 << nums.size()) - 1;
        for(int s = state; s; s = (s - 1) & state){
            vector<int> temp;
            for(int i = 0; i < nums.size(); i++)
                if((1 << i) & s) temp.push_back(nums[i]);
            res.push_back(temp);
        }
        return res;
    }
};

int main(){

}