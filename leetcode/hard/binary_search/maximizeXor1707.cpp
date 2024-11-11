/**
 * @Time : 2023/4/11-8:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> infos;
        for(int i = 0; i < queries.size(); i++)
            infos.push_back({queries[i][1], queries[i][0], i});
        sort(infos.begin(), infos.end());
        vector<int> res(queries.size(), -1);
        int j = 0, n = nums.size();
        for(auto& info : infos){
            int m = info[0], x = info[1], index = info[2];
            if(m < nums[0]) continue;
            while (j < n && nums[j] <= m) j++;
            res[index] = search(nums, j - 1, x);
        }
        return res;
    }

    int search(vector<int>& nums, int j, int x){
        int i = 0, digit = first_digit(nums, j, x);
        while (i < j && nums[i] != nums[j]) {
            int t = 1 << digit, lo = i, hi = j;;
            if(t & x) { // x的该位是1，那么就找nums中该位是0的
                while (lo < hi){
                    int mid = (lo + hi + 1) >> 1;
                    if(nums[mid] & t) hi = mid - 1;
                    else lo = mid;
                }
                if(!(t & nums[lo])) j = lo; // 确保这一数位有0，才缩小范围
            } else { // 找nums中该位是1的
                while (lo < hi){
                    int mid = (lo + hi) >> 1;
                    if(nums[mid] & t) hi = mid;
                    else lo = mid + 1;
                }
                if(t & nums[lo]) i = lo;
            }
            digit--;
        }
        return x ^ nums[i];
    }

    int first_digit(vector<int>& nums, int j, int x){
        for(int i = 31, num = nums[j]; i >= 0; i--){
            int t = 1 << i;
            if((num & t) || (x & t))
                return i;
        }
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}