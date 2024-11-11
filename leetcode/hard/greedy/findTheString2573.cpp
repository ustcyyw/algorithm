/**
 * @Time : 2023/4/24-10:33 PM
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
     * 要构造最小的字符串
     * s[0]一定是放a。 如果s[0]放的不是a，在构造完成之后，完全可以通过与其它位置的字符交换，将a交换到第一个位置
     * 当然，这里的交换是一系列字符串的交换，因为lcp矩阵规定了哪些子串有公共前缀
     * 进一步就知道哪些子串开头第一个字母相同，就将这些字母划分为连通分量
     * lcp[i][j] > 0 说明s[i] = s[j]
     *
     * s[0]放了a，并且与0这个位置同一个分量的位置都被放置为0
     * 那么接下来最靠左，且没有放置字母的位置就应该放b，以此类推
     * 等构造完成后，再得到答案字符串的lcp矩阵，与题目提供的矩阵进行比较
     * 完成一致才说明合法。
     */
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        string s(n, '.');
        for(int i = 0, k = 0; i < n; i++){
            if(s[i] != '.') continue;
            char c = (char)(k++ + 'a');
            if(c > 'z') return "";
            for(int j = i; j < n; j++)
                if(lcp[i][j]) s[j] = c;
        }
        vector<vector<int>> dp(n, vector(n, 0));
        for(int i = n - 1; i >= 0; i--) {
            for(int j = i; j >= 0; j--) {
                if(lcp[i][j] != lcp[j][i]) return "";
                if(s[i] == s[j]) {
                    dp[i][j] = i < n - 1 && j < n - 1 ? 1 + dp[i + 1][j + 1] : 1;
                }
                if(dp[i][j] != lcp[i][j]) return "";
            }
        }
        return s;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}