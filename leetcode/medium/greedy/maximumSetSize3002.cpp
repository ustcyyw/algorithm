/**
 * @Time : 2024/1/9-12:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumSetSize(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), half = n / 2;
        vector<int> arr1 = filter(nums1), arr2 = filter(nums2);
        int m1 = arr1.size(), m2 = arr2.size(), mb = 0;
        unordered_set<int> set;
        for(int num : arr1)
            set.insert(num);
        for(int num : arr2)
            if(set.count(num)) mb++;
        while(mb) { // 不断移除多的那个集合中的重复元素
            if(m2 > m1) m2--;
            else m1--;
            mb--;
        }
        return min(m1, half) + min(m2, half) - mb;
    }
    // 首先将一个集合中的重复元素去掉
    vector<int> filter(vector<int>& nums) {
        vector<int> res;
        sort(nums.begin(), nums.end());
        res.push_back(nums[0]);
        for(int i = 1; i < nums.size(); i++)
            if(nums[i] != nums[i - 1]) res.push_back(nums[i]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}