/**
 * @Time : 2023/9/19-10:37 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minLengthAfterRemovals(vector<int>& nums) {
        int n = nums.size(), single = 0;
        vector<int> arr;
        for(int i = 0, j = 1; i < n; i = j) {
            while (j < n && nums[j] == nums[i]) j++;
            if(j - i > 1) {
                for(int k = i; k < j; k++)
                    arr.push_back(nums[i]);
            }
            else single++;
        }
        int m = arr.size(), half = m / 2, equal = m;
        for(int i = half - 1, j = m - 1; i >= 0; i--, j--)
            if(arr[i] != arr[j]) equal -= 2;
        if(equal >= single) return equal - single;
        return (single - equal) % 2;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}