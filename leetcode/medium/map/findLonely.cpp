/**
 * @Time : 2022/8/25-9:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findLonely(vector<int>& nums) {
        int n = 1e6;
        vector<int> count(n + 1, 0), res;
        for(int num : nums)
            count[num]++;
        if(count[0] == 1 && count[1] == 0)
            res.push_back(0);
        if(count[n] == 1 && count[n - 1] == 0)
            res.push_back(n);
        for(int i = 1; i < n; i++)
            if(count[i] == 1 && count[i - 1] == 0 && count[i + 1] == 0)
                res.push_back(i);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}