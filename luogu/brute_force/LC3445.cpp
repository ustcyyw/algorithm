/**
 * @Time : 2025/2/2-10:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3445 暴力枚举 思维
 */
 /*
  * 一共只有5种字符 完全可以枚举一个字符出现奇数次 另外一个字符出现偶数次
  * 选两个字符 将其下标放在arr中 并且规定字符1出现奇数次
  * 字符1出现的奇偶次用s1表示，字符2出现的奇偶次用s2表示
  * (s1,s2)就能表示出两字符的奇偶特性
  * 00: 两个字符出现的次数都是偶数次 那么就得找前面出现10的情况
  * 01: 第一个字符出现偶数次 第二个字符出现奇数次 就得找前面出现11的情况
  * 10: 第一个字符出现奇数次 第二个字符出现偶数次 前面得是00
  * 11: 前面得是01
  * 发现前面的状态就是用当前状态与10求xor
  * 假设选取的子数组是[j+1, i] 答案就是 ci1 - cj1 - (ci2 - cj2) = cj1 - cj2 - (ci1 - ci2)
  * 可以记录下每个状态对应的 c = c1 - c2
  *
  * 在枚举到i位置时 状态 status = (s1 << 1) | s2 要求前面的状态是 ps = status ^ 2
  * 并且对子区间的要求有两个：
  * 1.长度 >= k
  * 2.出现偶数次的字符至少是出现2次 （因为0也是偶数，而奇数次至少是1次 已经确保奇数次的字符出现在该区间中）
  * 因此取 j = min(i - k, pre[i][num2] - 1)
  * 于是要求最大值 就是对于所有满足 x <= j, 并且状态是ps的最小c
  * 按状态分组并且求最小前缀即可快速查询出结果
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string s;
    int n, k;
    vector<vector<int>> pre;
    int maxDifference(string s, int k) {
        this->n = s.size(), this->k = k;
        s = '.' + s;
        this->s = s;
        pre = vector(n + 1, vector(5, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < 5; j++)
                pre[i][j] = pre[i - 1][j];
            pre[i][s[i] -'0'] = i;
        }
        int ans = INT_MIN;
        for(int i = 0; i < 5; i++) {
            for(int j  = 0; j < 5; j++) {
                if(i == j) continue;
                ans = max(ans, cal(i, j));
            }
        }
        return ans;
    }

    int cal(int num1, int num2) {
        int ans = INT_MIN;
        vector<vector<int>> val(4, vector(n + 1, n + 1));
        val[0][0] = 0;
        for(int i = 1, s1 = 0, s2 = 0, c1 = 0, c2 = 0; i <= n; i++) {
            int num = s[i] - '0';
            if(num == num1) s1 ^= 1, c1++;
            else if(num == num2) s2 ^= 1, c2++;
            int status = (s1 << 1) | s2, c = c1 - c2;
            int ps = status ^ 2;
            int j = min(i - k, pre[i][num2] - 1); // 保证子区间长度>=k并且存在nums2
            if(j >= 0) ans = max(ans, c - val[ps][j]);
            for(int u = 0; u < 4; u++)
                val[u][i] = val[u][i - 1];
            val[status][i] = min(val[status][i - 1], c);
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}