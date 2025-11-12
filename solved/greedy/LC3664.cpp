/**
 * @Time : 2025/10/25-22:10
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3664 2157 暴力枚举 贪心
 */
 /*
  * 两个x字母的牌 不可以相互之间配对 必须搭配单个x字母的牌
  * 单个x字母的牌分为两类，第一个字母为x or 第二个字母为x
  * 因此需要枚举两个x的牌 给到第一类的数量
  *
  * 在具体某一类的搭配选择中，又根据另外一个字母的不同分为多个子类
  * 如果不考虑xx这样的牌
  * 有一个重要的性质：最多的那一种牌数量 <= 其它种类的牌数量之和，就一定能找到完全配对的方法
  *
  * 再考虑到xx这样的牌，应该尽可能先使用他们和单x的牌配对
  * 因为不优先使用他们，他们就会浪费掉，优先使用他们可以让单x的牌中最大的一组先减少，更有可能完全配对
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    int score(vector<string>& cards, char x) {
        int c2 = 0;
        vector<int> count0(26, 0), count1(26, 0);
        for(string& card : cards) {
            char c0 = card[0], c1 = card[1];
            if(c0 == x && c1 == x) c2++;
            else if(c0 == x) count0[c1 - 'a']++;
            else if(card[1] == x) count1[c0 - 'a']++;
        }
        int mv0, sum0, other0, mv1, sum1, other1;
        init(count0, mv0, sum0, other0), init(count1, mv1, sum1, other1);
        int ans = 0;
        for(int c = 0; c <= c2; c++) {
            int t0 = cal(mv0, sum0, other0, c);
            int t1 = cal(mv1, sum1, other1, c2 - c);
            ans = max(ans, t1 + t2);
        }
        return ans;
    }
    // 有c个两x字母的牌，必须都用上
    int cal(int mv, int sum, int other, int c) {
        if(c >= sum) return sum;
        if(mv >= other) {
            int d = mv - other;
            // c不能抹平最多单x牌的优势
            if(c < d) return c + other;
            c -= d;
            return d + (other * 2 + c) / 2;
        } else {
            int d = other - mv;
            if(c < d) return c + (other - c + mv) / 2;
            c -= d;
            return d + (mv * 2 + c) / 2;
        }
    }

    void init(vector<int>& cnt, int& mv, int& sum, int& other) {
        mv = *max_element(cnt.begin(), cnt.end());
        sum = reduce(cnt.begin(), cnt.end()), other = sum - mv;
    }
};