/**
 * @Time : 2025/2/16-3:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3455 kmp 双指针 分类讨论
 */
 /*
  * 字符 * 可以匹配0个或者任意个字符
  * 被*隔开的字符串则必须刚好匹配
  * 这些子串为 t1, t2, t3
  * 如果只有1个子串非空 那就用kmp去找是否有匹配的子串 匹配成功 那么p的匹配最小长度就是该子串长度
  * 如果2个子串非空 比如t1和t2，那么匹配项就是 t1*t2
  * 枚举t1出现的位置，然后找t2离t1最近且两个子串不相交的位置 就是一个备选答案
  * 如果3个非空子串 可以枚举t2的位置
  *     找t3离t2最近且两个子串不相交的位置
  *     并且要找t1离t2最近 且两个子串不相交的位置
  *     这样就是一个备选答案
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestMatchingSubstring(string s, string p) {
        int m = p.size();
        if(m == 2) return 0;
        int idx1 = -1, idx2 = -1;
        for(int i = 0; i < m; i++) {
            if(p[i] == '*') {
                if(idx1 == -1) idx1 = i;
                else idx2 = i;
            }
        }
        string t1 = p.substr(0, idx1), t2 = p.substr(idx1 + 1, idx2 - idx1 - 1);
        string t3 = p.substr(idx2 + 1, m - idx2 - 1);
        if(t1.empty() && t2.empty()) return !kmp(s, t3).empty() ? t3.size() : -1;
        if(t2.empty() && t3.empty()) return !kmp(s, t1).empty() ? t1.size() : -1;
        if(t1.empty() && t3.empty()) return !kmp(s, t2).empty() ? t2.size() : -1;
        if(t1.empty()) return check2(s, t2, t3);
        if(t2.empty()) return check2(s, t1, t3);
        if(t3.empty()) return check2(s, t1, t2);
        return check(s, t1, t2, t3);
    }

    int check(string& s, string& p1, string& p2, string& p3) {
        vector<int> arr1 = kmp(s, p1), arr2 = kmp(s, p2), arr3 = kmp(s, p3);
        if(arr1.empty() || arr2.empty() || arr3.empty()) return -1;
        int l1 = p1.size(), l2 = p2.size(), l3 = p3.size();
        int n1 = arr1.size(), n2 = arr2.size(), n3 = arr3.size();
        int ans = INT_MAX;
        for(int i = 0, j = 0, k = 0; i < n2 && j < n3; i++) {
            while(k < n1 && arr1[k] + l1 - 1 < arr2[i])
                k++;
            while(j < n3 && arr3[j] <= arr2[i] + l2 - 1)
                j++;
            if(j < n3 && k - 1 >= 0)
                ans = min(arr3[j] + l3 - arr1[k - 1], ans);
        }
        return ans == INT_MAX ? -1 : ans;
    }

    int check2(string& s, string& p1, string& p2) {
        vector<int> arr1 = kmp(s, p1), arr2 = kmp(s, p2);
        if(arr1.empty() || arr2.empty()) return -1;
        int ans = INT_MAX;
        for(int i = 0, j = 0, n = arr1.size(), m = arr2.size(); i < n && j < m; i++) {
            while(j < m && arr2[j] <= arr1[i] + p1.size() - 1)
                j++;
            if(j < m) ans = min(ans, arr2[j] + (int)p2.size() - arr1[i]);
        }
        return ans == INT_MAX ? -1 : ans;
    }

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
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}