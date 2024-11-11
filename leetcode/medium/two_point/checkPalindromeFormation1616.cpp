/**
 * @Time : 2023/2/13-9:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int n;
    bool checkPalindromeFormation(string a, string b) {
        this->n = a.size();
        vector<bool> aPal = self_pal(a), bPal = self_pal(b);
        if(aPal[n / 2] || bPal[n / 2]) return true;
        return check(a, b, aPal, bPal) || check(b, a, bPal, aPal);
    }

    /*
     * 假如是a的前缀和b的后缀组成回文
     * 可能有两种情况 1.a占小部分，b占大部分; 2.a占大部分，b占小部分
     * 1.假设a贡献的长度为i，那么 a[0,i - 1] 与 b[n - i, n - 1] 对称
     * 且b[i, n - i - 1]是一个回文串
     * 2.假设b贡献的长度为i，那么 a[0, i] 与 b[n - i, n - 1] 对称
     * 且a[i, n - i - 1]是一个回文串
     * 两种情况下，都要求a，b两端对称，不同的是中间的回文串谁来贡献
     * (a,b各占拼接串一半的情况，可以视为以上两种情况中任意一种的特殊case)
     *
     * 假如是b的前缀和a的后缀组成回文? 这是对称问题，传参的时候互换a b即可
     */
    bool check(string &a, string &b, vector<bool> &aPal, vector<bool> &bPal) {
        for (int i = 0, j = n - 1; i < n && a[i] == b[j]; i++, j--) {
            int len = (n - (i + 1) * 2) / 2;
            if (aPal[len] || bPal[len]) return true;
        }
        return false;
    }
    // 预处理 中间子串 的回文性
    vector<bool> self_pal(string &a) {
        // dis 表示距离回文中心的距离, 长度为奇数时初始距离为0，偶数初始距离为1
        int dis = (n + 1) % 2;
        vector<bool> pal(n / 2 + 1, false);
        pal[0] = true;
        int lo = n % 2 == 1 ? n / 2 : n / 2 - 1, hi = n / 2;
        while (lo >= 0 && a[lo] == a[hi]) {
            pal[dis] = true;
            dis++, lo--; hi++;
        }
        return pal;
    }
};

int main() {
    Solution s;
    s.checkPalindromeFormation("abdef", "fecab");
    cout << 0 << endl;
}