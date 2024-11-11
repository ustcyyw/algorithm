/**
 * @Time : 2024/6/16-5:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛402 t2 hashmap计数
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countCompleteDayPairs(vector<int>& hours) {
        map<int, int> mp;
        long long ans = 0;
        for(int num : hours) {
            int mod = num % 24;
            ans += mp[(24 - mod) % 24];
            mp[mod]++;
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}