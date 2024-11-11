/**
 * @Time : 2023/2/28-1:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        int i = 0, lo = 0, n = groups.size(), m = nums.size();
        while (i < n && lo < m){
            int j = 0, t = groups[i].size(), hi = lo;
            if(m - lo + 1 < t) return false;
            while (j < t && groups[i][j] == nums[hi]) j++, hi++;
            if(j == t) i++, lo = hi;
            else lo++;
        }
        return i == n;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}