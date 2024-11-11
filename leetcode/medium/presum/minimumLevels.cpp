/**
 * @Time : 2024/3/31-10:10 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛127 t2
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumLevels(vector<int>& possible) {
        int n = possible.size();
        vector<int> sum(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1];
            if(possible[i - 1] == 0) sum[i] -= 1;
            else sum[i]++;
        }
        for(int i = 1; i < n; i++) {
            if(sum[i] > sum[n] - sum[i])
                return i;
        }
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}