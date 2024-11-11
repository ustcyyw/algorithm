/**
 * @Time : 2024/1/29-4:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> arrA = kmp(s, a), arrB = kmp(s, b); // 记录a和b的开头索引
        vector<int> res;
        int ma = arrA.size(), mb = arrB.size();
        for(int i = 0, j = 0; i < ma; i++) {
            while(j < mb && arrA[i] - arrB[j] > k) j++;
            if(j != mb && abs(arrA[i] - arrB[j]) <= k)
                res.push_back(arrA[i]);
        }
        return res;
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

/*
 * 用字符串hash找匹配的方法
 */
//typedef unsigned long long ull;
//const int P = 13331, N = 5e5 + 5;
//ull x[N];
//int init = []() -> int {
//    x[0] = 1;
//    for(int i = 1; i < N; i++)
//        x[i] = x[i - 1] * P;
//    return 0;
//}();
//class Solution {
//public:
//
//    ull str_hash2(string& s) {
//        int n = s.size();
//        ull res = 0;
//        for (int i = 1; i <= n; i++)
//            res = res * P + s[i - 1];
//        return res;
//    }
//
//    ull get_hash(vector<ull> &h, int l, int r) {
//        return h[r + 1] - h[l] * x[r - l + 1];
//    }
//
//    vector<int> beautifulIndices(string s, string a, string b, int k) {
//        ull ha = str_hash2(a), hb = str_hash2(b);
//        int n = s.size(), na = a.size(), nb = b.size();
//        vector<ull> h(n + 1, 0);
//        vector<int> arrA, arrB; // 记录a和b的开头索引
//        for (int i = 1; i <= n; i++) {
//            h[i] = h[i - 1] * P + s[i - 1];
//            if(i >= na && ha == get_hash(h, i - na, i - 1))
//                arrA.push_back(i - na + 1);
//            if(i >= nb && hb == get_hash(h, i - nb, i - 1))
//                arrB.push_back(i - nb + 1);
//        }
//        vector<int> res;
//        int ma = arrA.size(), mb = arrB.size();
//        for(int i = 0, j = 0; i < ma; i++) {
//            while(j < mb && arrA[i] - arrB[j] > k) j++;
//            if(j != mb && abs(arrA[i] - arrB[j]) <= k)
//                res.push_back(arrA[i] - 1); // arrA[i]中的索引是从1开始的 所以这里要-1
//        }
//        return res;
//    }
//};

int main(){
    Solution s;
    
    cout << 0 << endl;
}