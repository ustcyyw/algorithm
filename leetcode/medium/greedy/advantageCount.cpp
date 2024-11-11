/**
 * @Time : 2022/4/25-11:10 AM
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
     * 执行用时：120 ms, 在所有 C++ 提交中击败了76.20%的用户
     * 内存消耗：61.2 MB, 在所有 C++ 提交中击败了54.40%的用户
     */
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), lo = 0, hi = n - 1;
        vector<pair<int, int>> infos2;
        for(int i = 0; i < n; i++)
            infos2.push_back(make_pair(nums2[i], i));
        sort(nums1.begin(), nums1.end());
        sort(infos2.begin(), infos2.end()); // pair默认第一个值升序排列
        vector<int> res = vector(n, 0);
        for(int& num : nums1){
            if(num > infos2[lo].first){
                res[infos2[lo].second] = num;
                lo++;
            } else{
                res[infos2[hi].second] = num;
                hi--;
            }
        }
        return res;
    }
};

int main(){

}