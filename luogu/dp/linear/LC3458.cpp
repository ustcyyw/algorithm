/**
 * @Time : 2025/2/16-2:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3458 动态规划
 */
 /*
  * 计算最大可能的不重叠特殊子字符串数目 看是否 >= k
  * 关键就是怎么划分特殊子字符串
  * s[l,r]是特殊子串 那么s[l,r]上的任何一个字母 都不会出现在s中其它地方了
  *
  * 假设c出现在当前特殊子串中，这个子串的范围至少是[first[c], last[c]]
  * 而这个范围内可能会出现其它字母，因此要将范围内其它字母找到 再看这些字母会将子串扩展到哪
  * 通过这样的方式确定所有可能的特殊子串 （最多26个 因为总共就26个字母）
  *
  * 然后问题就转化为如何选择不重叠区间 使得选择的区间数量最多 动态规划
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string s;
    bool maxSubstringLength(string s, int k) {
        int n = s.size();
        this->s = s;
        vector<int> first(26, -1), last(26, -1);
        for(int i = 0; i < n; i++)
            if(first[s[i] - 'a'] == -1) first[s[i] - 'a'] = i;
        for(int i = n - 1; i >= 0; i--)
            if(last[s[i] - 'a'] == -1) last[s[i] - 'a'] = i;
        vector<vector<int>> arr;
        for(int c = 0; c < 26; c++) {
            if(first[c] != -1)
                arr.push_back(get_range(c, first, last));
        }
        sort(arr.begin(), arr.end());
        int m = arr.size();
        vector<int> dp(m, 0);
        for(int i = 0; i < m; i++) {
            int l = arr[i][0], r = arr[i][1];
            if(l != 0 || r != n - 1) dp[i] = 1;
            for(int j = 0; j < i; j++) {
                if(l > arr[j][1])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            if(dp[i] >= k) return true;
        }
        return false;
    }

    vector<int> get_range(int c, vector<int>& first, vector<int>& last) {
        int l = first[c], r = last[c];
        for(int i = l, j = r; i <= r || j >= l; ) {
            if(i <= r) {
                l = min(l, first[s[i] - 'a']), r = max(r, last[s[i] - 'a']);
                i++;
            }
            if(j >= l) {
                l = min(l, first[s[j] - 'a']), r = max(r, last[s[j] - 'a']);
                j--;
            }
        }
        return {l, r};
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}