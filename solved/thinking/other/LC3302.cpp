/**
 * @Time : 2025/1/28-3:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3302 字符串 前后缀分解 贪心 暴力枚举
 */
 /*
  * 子序列对应的字符串有一个字符不同 那么不同的那个位置 修改s1还是s2都一样
  * 考虑修改s1中第i个字符
  * 截止s1[i-1]， 已经匹配了s2的前j-1个字符
  * 那么第i个字符的修改 应该改为s2[j] 因为前面都已经匹配到了s2[0,j-1]
  * 改为s2[0,j-1]上的任意一个字符 最终也不会选择i这个下标
  *
  * 如果s[i+1, n1-1]上能将s2[j+1,n2-1]的字符都匹配上
  * 那么将前面匹配s2[0,j-1]的下标选上 再将i选上 再从s[i+1]开始匹配s2[j+1,n2-1]的下标选上
  * 就可以几乎相等地匹配上s2 （i位置进行了一个字符的修改）
  * 并且这就是字典序号最小的方案 因为s1是从左往右枚举i
  * 第一个i满足上述条件时 就是通过一次修改 能让匹配的下标序列在靠前的下标减小值
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> validSequence(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size();
        vector<int> pre(n1, 0), suf(n1, 0); // suf[i]从i位置开始 最多能匹配s2的多少个后缀字符
        for(int i = n1 - 1, j = n2 - 1; i >= 0; i--) {
            if(i != n1 - 1) suf[i] = suf[i + 1];
            if(j >= 0 && s2[j] == s1[i]) suf[i] = n2 - j, j--;
        }
        for(int i = 0, j = 0; i < n1; i++) {
            if(i != 0) pre[i] = pre[i - 1];
            if(j < n2 && s2[j] == s1[i]) pre[i] = j + 1, j++;
        }
        vector<int> arr = get_seq(s1, 0, s2, 0);
        //s1的前n2个字符刚好就是s2 那这就是最小序列 直接返回；否则 总能通过一次修改字符 使匹配字典序更小
        if(pre[n2 - 1] == n2) return arr;
        for(int i = 0; i < n1; i++) {
            int j = pre[i];// 截止s1[i]已经匹配了j个字符
            // s1[i]刚好就是s2[j-1] 修改这个字符没有意义
            if(j > 0 && s1[i] == s2[j - 1] && (i == 0 || pre[i] > pre[i - 1])) continue;
            if(i + 1 < n1 && suf[i + 1] >= n2 - 1 - j) {
                vector<int> ans, temp = get_seq(s1, i + 1, s2, j + 1);
                for(int k = 0; k < j; k++)
                    ans.push_back(arr[k]);
                ans.push_back(i);
                for(int idx : temp)
                    ans.push_back(idx);
                return ans;
            }
        }
        return {};
    }

    vector<int> get_seq(string& s1, int i, string& s2, int j) {
        vector<int> ans;
        for( ; i < s1.size() && j < s2.size(); i++) {
            if(s1[i] == s2[j]) {
                ans.push_back(i);
                j++;
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}