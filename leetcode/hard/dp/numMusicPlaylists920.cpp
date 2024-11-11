/**
 * @Time : 2023/4/15-6:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    // dp[i][j] 截止第i个位置 播放了j首歌的方案数
    int mod = 1e9 + 7;
    int numMusicPlaylists(int N, int L, int K) {
        vector<vector<long>> dp(L + 1, vector(N + 1, 0l));
        dp[0][0] = 1;
        for(int i = 1; i <= L; i++){
            for(int j = 1; j <= min(N, i); j++){ // 枚举当前位置一共听了多少歌
                // 截止上一个位置 共听了j-1首，当前位置听了剩余的N - j + 1中的一首
                dp[i][j] = dp[i - 1][j - 1] * (N - j + 1) % mod;
                // 截止上一个位置 共听了j首 dp[i - 1][j]，当前位置要选其中的一首重复听
                // 那么最近的K首是不能选的，就选剩下的j-K首中的一首
                // 如果j <= K, 说明这j首里面不管选哪一首，都会导致重复，于是这种情况失效
                if(j > K) dp[i][j] = (dp[i][j] + dp[i - 1][j] * (j - K)) % mod;
            }
        }
        return (int)dp[L][N];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}