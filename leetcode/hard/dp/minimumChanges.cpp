/**
 * @Time : 2023/10/23-8:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛368 T4
 */
#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> factor = vector(201, vector(1, 1));
int init = []() {
    for(int i = 2; i <= 200; i++) {
        for(int j = 2; j <= (int)sqrt(i); j++) {
            if(i % j == 0) {
                factor[i].push_back(j);
                factor[i].push_back(i / j);
            }
        }
    }
    return 0;
}();
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        vector<vector<int>> aux(n + 1, vector(n + 1, 0));
        for(int lo = 0; lo < n; lo++) {
            for(int hi = lo + 1; hi < n; hi++)
                aux[lo + 1][hi + 1] = min_change(s, lo, hi);
        }
        vector<vector<int>> dp(n + 1, vector(k + 1, (int)1e5));
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++) {
            // 因为半回文串 长度为2 长度为i的字符串 最多分为i/2个半回文
            for(int j = 1; j <= min(k, i / 2); j++) {
                // 同理 在[1,t]上有j-1个半回文，其长度至少为 2(j-1) 那么 t >= 2(j-1)
                for(int t = 2 * (j - 1); t < i - 1; t++) {
                    dp[i][j] = min(dp[i][j], dp[t][j - 1] + aux[t + 1][i]);
                }
            }
        }
        return dp[n][k];
    }

    int min_change(string& s, int lo, int hi) {
        int len = hi - lo + 1, res = 1e5;
        for(int d : factor[len]) { // 枚举半回文的间隔d 要能整除len
            int sum = 0;
            for(int k = 0; k < d; k++) { // 根据d 枚举分组的标号
                int i = lo + k, j = hi - d + k + 1; // 根据分组标号确定首尾元素，他们是要进行回文对应的
                while(i < j) {
                    if(s[i] != s[j]) sum++;
                    i += d, j -= d; // 同一组的元素 相邻下标之差就是d
                }
            }
            res = min(res, sum);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}