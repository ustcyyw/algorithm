/**
 * @Time : 2023/3/23-1:06 PM
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
     * 对字符串s的扰乱操作记为 change(s)
     * 切割点确定的情况下,将s1分为两个部分，左右分别记为a，b
     * 顺序保持则为a b，可能会顺序颠倒则变为b a
     * 要让s2做为s1的扰乱字符串
     * 则要求s2也相应的拆分为两个部分 c和d
     * 1.与s1中的a b顺序匹配，len(c) = len(a), len(d) = len(b)
     * 并且c = change(a), d = change(b)
     * 2.与s1中的b a顺序匹配，len(c) = len(b), len(d) = len(a)
     * 并且c = change(b), d = change(a)
     * 以上两种情况 只要有一种可以匹配，就可以认为s2 = change(s1)
     *
     * 由此 递归的逻辑就有了
     * 然后就是加上记忆化搜索
     */
    int n;
    string s1, s2;
    unordered_map<int, int> cache;
    bool isScramble(string s1, string s2) {
        this->s1 = s1, this->s2 = s2;
        n = s1.size();
        return march(0, n, 0, n);
    }

    bool march(int lo1, int hi1, int lo2, int hi2) {
        if (lo1 == hi1) return lo2 == hi2 && s1[lo1] == s2[lo2];
        int key = get_key(lo1, hi1, lo2, hi2);
        if (cache.count(key)) return cache[key];
        bool ans = false;
        for (int i = lo1; i < hi1 && !ans; i++) { // 分成s1[lo1, i], s1[i + 1, hi]
            int leftLen = i - lo1 + 1;
            ans = (march(lo1, i, lo2, lo2 + leftLen - 1) && march(i + 1, hi1, lo2 + leftLen, hi2)) ||
                  (march(lo1, i, hi2 - leftLen + 1, hi2) && march(i + 1, hi1, lo2, hi2 - leftLen));
        }
        cache[key] = ans;
        return ans;
    }

    int get_key(int a, int b, int c, int d) {
        return a * n * n * n + b * n * n + c * n + d;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}