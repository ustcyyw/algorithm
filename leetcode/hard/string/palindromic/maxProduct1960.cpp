/**
 * @Time : 2023/11/7-5:38 PM
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
     * 显然要找到每一个点为中心的最长回文串 刚好这样的回文串是奇数长度的
     * 可以使用 马拉车算法 预处理出p[i]
     *
     * 因为要求两个回文串的积 并且不能有重叠 可以想到如果枚举分界线i
     * 将s分为左右两个部分 s[0,i], s[i+1, n-1] 并且将这两个区间上最长的回文串找到 相乘就是一个备选答案
     * 用left[i]表示s[0,i]上的最长回文长度
     * 显然 left[i] >= left[i-1]
     * 但是由于s[i]的出现 可能会扩展回文串 例如
     * x x x x x x x x x x x x (x表示该处是某个字符 是啥不重要 看位置)
     *           l   k j   i
     * 如果 p[j] = 3, 那么 s[2j - i, i]是回文串 其长度为 2i - 2j + 1。
     * 在left[i-1]的计算中，j为中心的回文串长度是3，此时扩展为5
     * 如果 p[k] = 2, 那么 s[k-2, k+2]是回文串 但是s[i]的加入并不能扩展该回文串
     * s[k-2, k+2]已经在left[i-1]中考虑了
     * 如果 p[l] = 5, 那么 s[2l - i, i]是回文串
     * 在left[i-1]的计算中，l为中心的回文串长度是9，此时扩展为11
     * 因此 left[i] = max(left[i-1], max{2(i-j) + 1, for all j that j + p[j] >= i})
     * 对于 max{2(i-j) + 1, for all j that j + p[j] >= i}，要尽量取最大
     * 那么应该让j尽可能小，但是随着i的增大，不等式j + p[j] >= i 可能不满足
     * j向左移动吗，不是 因为在尽可能让j小，如果j-1能保证 j - 1 + p[j - 1] >= i成立，那么压根不会考虑j
     * 所以j应该向右移动，i和j的移动方向相同
     *
     * right[i]: 表示s[i,n-1]上的最长回文长度 类似地处理
     */
    long long maxProduct(string s) {
        int n = s.size();
        vector<int> p = manacher(s), left(n, 1);
        for(int i = 1, j = 0; i < n; i++) {
            while(j < n && j + p[j] < i) j++;
            left[i] = max(left[i - 1], 2 * (i - j) + 1);
        }
        long long res = 0;
        for(int i = n - 2, j = n - 1, right = 1; i >= 0; i--) {
            res = max(res, (long long)left[i] * right);
            while(j >= 0 && j - p[j] > i) j--;
            right = max(right, 2 * (j - i) + 1);
        }
        return res;
    }

    vector<int> manacher(string& s) {
        int n = s.size(), mc = -1, mr = -1;
        vector<int> p(n, 0);
        for(int i = 1; i < n; i++) {
            int r;
            if(mr > i) {
                int j = 2 * mc - i;
                r = min(p[j], mr - i);
            } else r = 0;
            while(i + r < n && i - r >= 0 && s[i + r] == s[i - r]) r++;
            p[i] = r - 1; // while循环结束时 s[i + r] != s[i - r]或者已经超出边界了 因此扩展半径时r-1
            if(i + p[i] > mr) mr = i + p[i], mc = i;
        }
        return p;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}