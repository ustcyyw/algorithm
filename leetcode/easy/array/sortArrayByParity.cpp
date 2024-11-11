/**
 * @Time : 2022/4/29-12:13 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int i = 0, n = nums.size();
        while (i < n && nums[i] % 2 == 0) i++;
        for(int j = i + 1; j < n; j++){
            if(nums[j] % 2 == 0){
                int temp = nums[i];
                nums[i++] = nums[j];
                nums[j] = temp;
            }
        }
        return nums;
    }
};

int main(){

}