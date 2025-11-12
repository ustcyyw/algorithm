/**
 * @Time : 2025/10/13-23:34
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3714 2224 思维 hashmap套路
 */
 /*
  * 分类讨论
  * 只有1个字母组成的
  * 只有2个字母组成的
  * 当前下标为i, 前一个下标为j，区间为[j+1,i]
  * i % 2 = j % 2
  * sum1[i] - sum1[j] = (i - j) / 2 -> 2sum1[i] - i = 2sum1[j] - j
  * 3个字母组成
  * 满足 i % 3 = j % 3 并且
  * sum1[i] - sum1[j] = (i - j) / 3 -> 3 * sum1[i] - i = 3 * sum1[j] - j
  * 同理 sum2[i] - sum2[j - 1] = [i - (j - 1)] / 3
  * 三个条件 缺1不可
  *
  * 形式一致，可以用hashmap分组 类似于2数之和的做法
  */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, M = 31, N = 1e5 + 5;
int sum[3][N];

class Solution {
public:
    int n, ans;
    int longestBalanced(string s) {
        s = '.' + s;
        n = s.size(), ans = 0;
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < 3; j++)
                sum[j][i] = sum[j][i - 1];
            sum[s[i] - 'a'][i]++;
        }
        one(s);
        two(s, 'a', 'b'), two(s, 'a', 'c'), two(s, 'b', 'c');
        three(s);
        return ans;
    }

    void three(string& s) {
        vector<unordered_map<int, unordered_map<int, int>>> map(3);
        map[0][0][0] = 0;
        for(int i = 1; i < n; i++) {
            int t = i % 3, v1 = 3 * sum[0][i] - i, v2 = 3 * sum[1][i] - i;
            if(map[t].count(v1) && map[t][v1].count(v2))
                ans = max(ans, i - map[t][v1][v2]);
            else map[t][v1][v2] = i;
        }
    }

    void two(string& s, char a, char b) {
        for(int i = 1, j = 1; i < n; i = j) {
            while(i < n && s[i] != a && s[i] != b) i++;
            if(i == n) break;
            j = i + 1;
            while(j < n && s[j] == a || s[j] == b) j++;
            sub_two(s, a, b, i, j - 1);
        }
    }

    void sub_two(string& s, char a, char b, int lo, int hi) {
        vector<unordered_map<int, int>> map(2);
        int idx = a - 'a', va = 2 * sum[idx][lo - 1] - (lo - 1);
        map[(lo - 1) % 2][va] = lo - 1;
        for(int i = lo; i <= hi; i++) {
            int t = i % 2, v = 2 * sum[idx][i] - i;
            if(map[t].count(v)) ans = max(ans, i - map[t][v]);
            else map[t][v] = i;
        }
    }

    void one(string& s) {
        for(int i = 1, j = 1; i < n; i = j) {
            while(j < n && s[j] == s[i]) j++;
            ans = max(ans, j - i);
        }
    }
};