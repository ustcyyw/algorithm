/**
 * @Time : 2024/3/10-2:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛388 t2
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        sort(happiness.begin(), happiness.end());
        long long sum = 0, n = happiness.size();
        for(int i = 0; i < k; i++)
            sum += max(0, happiness[n - 1 - i] - i);
        return sum;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}