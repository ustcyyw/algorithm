/**
 * @Time : 2024/12/22-5:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 最小的元素 继续让他变小 肯定保证了不会和其它元素重合
     * 将每个值的元素先尽可能变小 然后尽可能地将其操作为不同值
     */
    int maxDistinctElements(vector<int>& nums, int k) {
        map<int, int> mp;
        for(int num : nums)
            mp[num]++;
        int pre = INT_MIN, ans = 0; // pre表示当前元素可以从什么值开始，因为前面的变换可能已经占了一些值
        for(auto& [num, cnt] : mp) {
            int lo = max(pre, num - k), hi = min(lo + cnt - 1, num + k);
            ans += hi - lo + 1, pre = hi + 1;
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}