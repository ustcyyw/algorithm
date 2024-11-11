/**
 * @Time : 2024/1/29-4:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 运用 CF1003F
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 在字符串text中找到模式串pattern的所有开头索引
     * @param text
     * @param pattern
     * @return
     */
    vector<int> kmp(string &text, string &pattern) {
        int m = pattern.length();
        vector<int> pi(m), res;
        for (int i = 1, c = 0; i < m; i++) {
            char v = pattern[i];
            while (c && pattern[c] != v)
                c = pi[c - 1];
            if (pattern[c] == v) c++;
            pi[i] = c;
        }
        for (int i = 0, c = 0; i < text.length(); i++) {
            char v = text[i];
            while (c && pattern[c] != v)
                c = pi[c - 1];
            if (pattern[c] == v) c++;
            if (c == m) {
                res.push_back(i - m + 1);
                c = pi[c - 1];
            }
        }
        return res;
    }

    /*
     * 在字符串text中到模式串text[lo, hi]的所有开头索引
     * 也就是模式串通过指定test上的一个子区间来确定
     */
    vector<int> kmp(string &text, int lo, int hi) {
        int m = hi - lo + 1, ans = 0;
        vector<int> pi(m), res;
        for (int i = 1, c = 0; i < m; i++) {
            int v = text[lo + i];
            while (c && text[lo + c] != v)
                c = pi[c - 1];
            if (text[lo + c] == v) c++;
            pi[i] = c;
        }
        for (int i = 0, c = 0; i < text.length(); i++) {
            int v = text[i];
            while (c && text[lo + c] != v)
                c = pi[c - 1];
            if (text[lo + c] == v) c++;
            if (c == m) {
                res.push_back(i - m + 1);
                c = pi[c - 1];
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}