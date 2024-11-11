/**
 * @Time : 2022/12/26-9:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int takeCharacters(string s, int k) {
        if(k == 0) return 0;
        int n = s.size(), res = n;
        vector<vector<int>> preSum(n, vector(3, 0));
        preSum[0][s[0] - 'a'] = 1;
        for(int i = 1; i < n; i++){
            for(int j = 0; j < 3; j++)
                preSum[i][j] = preSum[i - 1][j];
            preSum[i][s[i] - 'a']++;
        }
        if(preSum[n - 1][0] < k || preSum[n - 1][1] < k || preSum[n - 1][2] < k)
            return -1;
        vector<int> sum(3, 0);
        for(int lo = n - 1, hi = n - 1; hi >= 0; hi--){
            while (lo >= 0 && preSum[lo][0] + sum[0] >= k &&
                   preSum[lo][1] + sum[1] >= k && preSum[lo][2] + sum[2] >= k) lo--;
            if(lo == -1 && sum[0] >= k && sum[1] >= k && sum[2] >= k)
                res = min(res, n - hi - 1);
            else res = min(res, lo + 2 + n - hi - 1);
            sum[s[hi] - 'a']++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}