/**
 * @Time : 2023/3/15-10:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
//    int countSubstrings(string s, string t) {
//        int n = s.size(), m = t.size(), res = 0;
//        for(int i = 0; i < n; i++){
//            for(int j = 0; j < m; j++){
//                for(int lo = i, hi = j, cnt = 0; lo < n && hi < m && cnt < 2; lo++, hi++){
//                    if(s[lo] == t[hi]) res += cnt;
//                    else {
//                        cnt++;
//                        if(cnt == 1) res++;
//                    }
//                }
//            }
//        }
//        return res;
//    }

    /*
     * f(i, j)：以s[i], t[j]为结尾的满足条件的子串数目
     *
     * 如果 s[i+1] == t[j+1], 以s[i+1]，t[j+1]为结尾的满足条件的子串
     * 就是将以s[i], t[j]为结尾的满足条件的子串，再加上s[i+1]和t[j+1]这一组字母
     * f(i+1, j+1) = f(i, j)
     *
     * 如果 s[i+1] != t[j+1]
     * 以s[i+1]，t[j+1]为结尾的满足条件的子串,前置位置字母一定相同，
     * 因为那一次修改要用于改s[i+1]
     * 特别地，前置位置为空，一次修改用于改s[i+1]，也满足要求
     * f(i+1, j+1) = g(i, j) + 1
     * 其中g(i, j)表示以s[i], t[j]为结尾的满足条件的子串的最长公共后缀长度
    */
    int countSubstrings(string s, string t) {
        int n = s.size(), m = t.size(), res = 0;
        s = " " + s, t = " " + t;
        vector<vector<int>> g(n + 1, vector(m + 1, 0)), f(n + 1, vector(m + 1, 0));
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                g[i][j] = s[i] == t[j] ? g[i - 1][j - 1] + 1 : 0;
                f[i][j] = s[i] == t[j] ? f[i - 1][j - 1] : 1 + g[i - 1][j - 1];
                res += f[i][j];
            }
        }
        return res;
    }
};

int main() {
    Solution s;

    cout << 0 << endl;
}