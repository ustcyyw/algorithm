/**
 * @Time : 2022/6/6-1:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> arrayChange(vector<int>& nums, vector<vector<int>>& operations) {
        int map[1000001];
        for(int i = 0; i < nums.size(); i++)
            map[nums[i]] = i;
        for(auto& ope : operations){
            int pre = ope[0], cur = ope[1], index = map[pre];
            nums[index] = cur;
            map[cur] = index;
        }
        return nums;
    }
};

int main(){

}