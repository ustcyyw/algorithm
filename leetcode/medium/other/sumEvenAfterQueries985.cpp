/**
 * @Time : 2023/3/29-11:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        vector<int> res;
        int sum = 0;
        for(int num : nums)
            if(num % 2 == 0) sum += num;
        for(auto& query : queries){
            int i = query[1], val = query[0];
            if(nums[i] % 2 == 0) sum -= nums[i];
            nums[i] += val;
            if(nums[i] % 2 == 0) sum+= nums[i];
            res.push_back(sum);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}