/**
 * @Time : 2023/4/19-10:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPairs(vector<int>& deliciousness) {
        long res = 0, mod = 1e9 + 7;
        unordered_map<int, int> map;
        for(int num : deliciousness) {
            for(int i = 0; i < 22; i++) {
                int t = 1 << i;
                res += map.count(t - num) ? map[t - num] : 0;
            }
            map[num] = map.count(num) ? map[num] + 1 : 0;
            res %= mod;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}