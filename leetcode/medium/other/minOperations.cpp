/**
 * @Time : 2024/3/3-3:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        multiset<long long> set;
        for(int num : nums) set.insert(num);
        int cnt = 0;
        while(*(set.begin()) < k) {
            cnt++;
            long long x = *(set.begin());
            set.erase(set.begin());
            long long y = *(set.begin());
            set.erase(set.begin());
            set.insert(min(x, y) * 2 + max(x, y));
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}