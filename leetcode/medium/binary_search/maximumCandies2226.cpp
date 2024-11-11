/**
 * @Time : 2022/10/31-1:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k) {
        int lo = 0, hi = 1e7;
        while (lo < hi){
            int mid = (lo + hi + 1) >> 1;
            if(check(candies, k, mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    bool check(vector<int>& candies, long long k, int val){
        long long cnt = 0;
        for(int candy : candies){
            cnt += candy / val;
            if(cnt >= k) return true;
        }
        return false;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}