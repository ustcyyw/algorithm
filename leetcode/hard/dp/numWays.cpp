/**
 * @Time : 2022/8/15-1:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mod = 1e9 + 7;
    unordered_map<int, int> cache;
    int numWays(int steps, int arrLen) {
        return (int)move(steps, 0, arrLen);
    }

    long move(int step, int pos, int arrLen){
        if(pos > step || pos < 0 || pos >= arrLen) return -1;
        if(step == 0 && pos == 0) return 1;
        int key = pos * 1e3 + step;
        if(cache.count(key)) return cache[key];
        long ways = 0;
        for(int i = -1; i < 2; i++){
            long temp = move(step - 1, pos + i, arrLen);
            if(temp != -1)
                ways = (ways + temp) % mod;
        }
        cache[key] = ways;
        return ways;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}