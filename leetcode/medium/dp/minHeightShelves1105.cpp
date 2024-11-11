/**
 * @Time : 2023/4/24-12:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * dp[i]放前i本书的最小高度
     */
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for(int i = 1; i <= n; i++){
            // 将[j,i]本书放在当前这一层 枚举j 要保证宽度 <= shelfWidth
            for(int j = i, w = 0, val = -1; j > 0; j--){
                w += books[j - 1][0];
                if(w > shelfWidth) break;
                val = max(val, books[j - 1][1]);
                dp[i] = min(dp[i], dp[j - 1] + val);
            }
        }
        return dp[n];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}