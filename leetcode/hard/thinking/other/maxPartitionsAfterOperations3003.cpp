/**
 * @Time : 2024/1/9-12:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
class Solution {
public:
    /*
     * suf[i]:在不做任何修改的情况下 s[i, n-1]需要分割成多少组
     * 这是唯一确定的，因为要让每组都含有k个不同字符 且当前组要尽可能的长
     * 可以改动一个字母 位置和改成什么字母不确定 需要枚举 因此
     * suf_change[i][ch]:将s[i]修改为ch后 s[i, n-1]需要分割成多少组
     *
     * 假设 当前修改了第i个位置的字母 并且在不修改的情况下的第j组 包含了s[i]
     * 原本该组囊括的区间是[l,r], 现在因为s[i]被修改了，
     * 所以r可能会变化 r最小可能会变为i-1，也可能不变，也可能变大，最大变为n-1
     * 但是l是不变的，因为这是从前往后唯一决定的 改不改s[i]，第j-1组的右边界都是l-1, 第j组的右边界都是l
     * 在l确定的情况下，可以通过二分确定r会变为多少：找到最大的r1 使得[l,r1]上有k个字母
     * 于是答案就变成了 前面的组数j-1，包含i的当前组1，以s[r1 + 1]需要的分割组数 t
     * 如果 r1 = i-1, t = suf_change[i][ch], 否则 t = suf[r1]
     * 就是 j + suf[r1 + 1]
     */
    int n, k, sum[N][26], suf[N], sufc[N][26];
    int maxPartitionsAfterOperations(string s, int k) {
        if(k == 26) return 1;
        this->n = s.size(), this->k = k;
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < 26; j++)
                sum[i][j] = sum[i - 1][j];
            sum[i][s[i - 1] - 'a']++;
        }
        // 预处理在不改变的情况下，分组的情况
        vector<vector<int>> group;
        for(int i = 0; i < n; ) {
            int r = search(i, n, 'a', 'a'); // 不改变的情况下 就让new_c = old_c
            group.push_back({i, r});
            i = r + 1;
        }
        // 预处理在不改变的情况下 s[i, n-1]需要分割成多少组
        suf[n] = 0;
        // 预处理在改变s[i]的情况下 suf[i][ch]
        memset(sufc[n], 0, sizeof(sufc[n]));
        for(int i = n - 1; i >= 0; i--) {
            suf[i] = 1 + suf[search(i, n, 'a', 'a') + 1];
            int old_c = s[i] - 'a';
            for(int c = 0; c < 26; c++)
                sufc[i][c] = 1 + suf[search(i, i, c, old_c) + 1];
        }
        // 枚举修改的位置和修改成的字符
        int cnt = 0;
        for(int i = 0, j = 0; i < n; i++) {
            if(j < group.size() - 1 && group[j][1] < i)
                j++; // 保证i属于group[j]的范围
            int l = group[j][0], old_c = s[i] - 'a';
            for(int c = 0; c < 26; c++) {
                int r = search(l, i, c, old_c);
                if(r == i - 1) cnt = max(cnt, j + 1 + sufc[i][c]);
                else cnt = max(cnt, j + 1 + suf[r + 1]);
            }
        }
        return cnt;
    }
    // flag标识更换新旧字符的位置是否位于[l,r]上 如果是没有改变字母的情况 传如new_c = old_c即可
    int count(int l, int r, int new_c, int old_c, bool flag) {
        int cnt = 0;
        for(int j = 0; j < 26; j++) {
            int add = 0;
            if(flag) add = (j == new_c) - (j == old_c);
            cnt += sum[r + 1][j] - sum[l][j] + add > 0;
            if(cnt > k) return cnt;
        }
        return cnt;
    }
    // i表示替换新旧字符的位置 如果是没有改变字母的情况 传如new_c = old_c即可
    int search(int l, int i, int new_c, int old_c) {
        int lo = l, hi = n - 1;
        while(lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if(count(l, mid, new_c, old_c, mid >= i) <= k) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }
};