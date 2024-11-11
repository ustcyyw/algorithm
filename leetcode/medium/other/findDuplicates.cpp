/**
 * @Time : 2022/5/8-9:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        for(int i = 0; i < nums.size(); i++){
            if(!move(nums, i)) {
                res.push_back(nums[i]);
                nums[i] = 0; // 出现两次的数被统计后，该位置空出，设置为0
            }
        }
        return res;
    }

    bool move(vector<int>& nums, int i){
        // nums[i]还没放到争取的位置，且i这个位置不是空位置时，位置置换
        while (nums[i] != i + 1 && nums[i] != 0){
            int j = nums[i] - 1; // j为要交换到的正确位置
            if(j == nums[j] - 1) return false; // 说明该位置已经是正确的数了
            exch(nums, j, i);
        }
        return true;
    }

    void exch(vector<int>& nums, int i, int j){
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
};

int main(){
    Solution s;
    vector<int> arr = {4,3,2,7,8,2,3,1};
    s.findDuplicates(arr);
}