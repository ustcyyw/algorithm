/**
 * @Time : 2024/9/11-3:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3281 二分答案 贪心
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, d;
    int maxPossibleScore(vector<int>& start, int d) {
        n = start.size(), this->d = d;
        sort(start.begin(), start.end());
        long long lo = 0, hi = 2e9;
        while(lo < hi) {
            long long mid = (lo + hi + 1) >> 1;
            if(check(start, mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    bool check(vector<int>& start, long long val) {
        for(long long i = 1, x = start[0]; i < n; i++) {
            if(x + val > (long long)start[i] + d) return false;
            x = max(x + val, (long long)start[i]);
        }
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}