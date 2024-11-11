/**
 * @Time : 2022/11/28-11:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你数字字符串 s ，请你返回 s 中长度为 5 的 回文子序列 数目。由于答案可能很大，请你将答案对 109 + 7 取余 后返回。

提示：

如果一个字符串从前往后和从后往前读相同，那么它是 回文字符串 。
子序列是一个字符串中删除若干个字符后，不改变字符顺序，剩余字符构成的字符串。
 

示例 1：

输入：s = "103301"
输出：2
解释：
总共有 6 长度为 5 的子序列："10330" ，"10331" ，"10301" ，"10301" ，"13301" ，"03301" 。
它们中有两个（都是 "10301"）是回文的。
示例 2：

输入：s = "0000000"
输出：21
解释：所有 21 个长度为 5 的子序列都是 "00000" ，都是回文的。
示例 3：

输入：s = "9999900000"
输出：2
解释：仅有的两个回文子序列是 "99999" 和 "00000" 。
 

提示：

1 <= s.length <= 104
s 只包含数字字符。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/count-palindromic-subsequences
 */
class Solution {
public:
    /**
     * 长度为5的子序列，中间那个字母是任意可选的。
     * 因此想到不考虑中间字母是哪一个， 只关注其左右两边的两个数字构成的子序列
     * 如果左边选了jk，右边就得是kj
     * 因此也可以想到找到某个位置i（中间字母）左边，右边的数字序列统计情况
     * 因为两个数字的序列总共只有100种组合，可以进行按数字序列的分类计数
     */
    int n, mod = 1e9 + 7;
    int countPalindromes(string s) {
        n = s.size();
        vector<vector<vector<int>>> left = getLeftInfos(s), right = getRightInfos(s);
        long long res = 0;
        for(int i = 2; i < n - 2; i++){
            // 枚举前后数对子序，前缀为数字 j k, 后缀则为k j
            for(int j = 0; j < 10; j++)
                for(int k = 0; k < 10; k++)
                    res = (res + (long long)left[i - 1][j][k] * right[i + 1][k][j]) % mod;
        }
        return (int) res;
    }

    vector<vector<vector<int>>> getLeftInfos(string& s){
        vector<int> cnt(10, 0); // 记录数字的出现次数
        vector<vector<vector<int>>> infos(n, vector(10, vector(10, 0)));
        cnt[s[0] - '0'] = 1;
        for(int i = 1; i < n; i++){
            int num = s[i] - '0';
            for(int j = 0; j < 10; j++){
                for(int k = 0; k < 10; k++)
                    infos[i][j][k] = infos[i - 1][j][k];
                infos[i][j][num] += cnt[j];
            }
            cnt[num]++;
        }
        return infos;
    }

    vector<vector<vector<int>>> getRightInfos(string& s){
        vector<int> cnt(10, 0); // 记录数字的出现次数
        vector<vector<vector<int>>> infos(n, vector(10, vector(10, 0)));
        cnt[s[n - 1] - '0'] = 1;
        for(int i = n - 2; i >= 0; i--){
            int num = s[i] - '0';
            for(int j = 0; j < 10; j++){
                for(int k = 0; k < 10; k++)
                    infos[i][k][j] = infos[i + 1][k][j];
                infos[i][num][j] += cnt[j];
            }
            cnt[num]++;
        }
        return infos;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}