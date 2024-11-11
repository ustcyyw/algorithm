/**
 * @Time : 2023/4/25-9:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string kthLargestNumber(vector<string>& nums, int k) {
        sort(nums.begin(), nums.end(), [](string& a, string& b) -> bool {
            int n1 = a.size(), n2 = b.size();
            return n1 != n2 ? n1 < n2 : a < b;
        });
        return nums[nums.size() - k];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}