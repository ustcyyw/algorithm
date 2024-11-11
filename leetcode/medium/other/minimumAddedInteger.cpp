/**
 * @Time : 2024/4/28-10:36 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛395 t2 模拟
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int n = nums1.size(), m = nums2.size();
        function<int(int, int)> cal = [&](int b1, int b2) -> int {
            int res = INT_MAX;
            for(int i = 0, j = 0; i < m; i++, j++) {
                if(j == b1) j++;
                if(j == b2) j++;
                if(res == INT_MAX || res == nums2[i] - nums1[j])
                    res = nums2[i] - nums1[j];
                else return INT_MAX;
            }
            return res;
        };
        int x = INT_MAX;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++)
                x = min(x, cal(i, j));
        }
        return x;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}