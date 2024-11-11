/**
 * @Time : 2022/10/19-7:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        long sum = 0, n = nums1.size(), mod = 1e9 + 7;
        vector<int> aux;
        for(int i = 0; i < n; i++){
            sum += abs(nums1[i] - nums2[i]);
            aux.push_back(nums1[i]);
        }
        sort(aux.begin(), aux.end());
        long res = sum;
        for(int i = 0; i < n; i++){
            if(nums1[i] == nums2[i]) continue;
            auto it = lower_bound(aux.begin(), aux.end(), nums2[i]);
            int right = it == aux.end() ? aux[n - 1] : *it;
            int left = it == aux.begin() ? aux[0] : *(--it);
            long temp = sum - abs(nums1[i] - nums2[i]);
            res = min(res, temp + min(abs(left - nums2[i]), abs(right - nums2[i])));
        }
        return int(res % mod);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}