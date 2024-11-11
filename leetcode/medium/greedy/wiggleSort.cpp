/**
 * @Time : 2022/6/28-1:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        vector<int> count = vector(5001, 0);
        for(int num : nums)
            count[num]++;
        for(int k = 0, i = 0, j = count.size() - 1; k < nums.size(); k += 2){
            while (nums[i] == 0) i++;
            while (nums[j] == 0) j--;
            nums[k] =
        }
        for(int i = 1; i < nums.size(); i++){
            if(i % 2 == 1 && nums[i] < nums[])
        }
    }

    void exch(vector<int>& nums, int i, int j){
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}