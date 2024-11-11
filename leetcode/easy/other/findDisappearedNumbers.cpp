/**
 * @Time : 2022/5/8-10:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> res;
        int n = nums.size();
        for(int i = 0; i < n; i++)
            move(nums, i);
        for(int i = 0; i < n; i++)
            if(nums[i] != i + 1) res.push_back(i + 1);
        return res;
    }

    void move(vector<int>& nums, int i){
        while (nums[i] != i + 1){
            int j = nums[i] - 1;
            if(j == nums[j] - 1) return;
            exch(nums, i, j);
        }
    }

    void exch(vector<int>& nums, int i, int j){
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
};

int main(){

}