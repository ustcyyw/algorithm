/**
 * @Time : 2024/2/5-9:26 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛383 t4
 */

/*
 * 题目中1次操作 移除前缀中k个字符 又在后缀添加任意k个字符 那么i次变换后
 * 1.字符串的长度是不变
 * 2.变换后的后缀i * k个字符一定可以和原字符相同 压根不用去管这部分后缀
 * 3.s[i * k]这个字符变成了首字符 也只有s[i * k, n - 1]这部分往前移动的字符可能和原字符不同
 * 那么 如果s[i * k, n - 1]是s的一个前缀 变换后的字符串就和原字符串相等了 找到最小的i就是答案
 * 如果找不到i这样的i，那么就将s删除完一遍即可（都删除了 都任意添加 那必然相等了）
 * 每次删除k个，这种情况的删除次数就是 n % k == 0 ? n / k : n / k + 1
 *
 * 找最小的i使得s[i * k, n - 1]是s的一个前缀
 * 可以使用z函数或者字符串hash
 * z函数的定义为：s和它的后缀字符串s[i, n - 1]的最长公共前缀(lcp)的长度
 * 因此 z[i * k]的值与子串s[i * k, n - 1]长度一致 就满足了要求
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> z_function(string& s){
        int n = s.size();
        vector<int> z(n, 0);
        z[0] = n;
        for(int i = 1, l = 0, r = 0; i < n; i++){
            if(i <= r) z[i] = min(z[i - l], r - i + 1);
            while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
            if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }
        return z;
    }

    int minimumTimeToInitialState(string word, int k) {
        int n = word.size();
        vector<int> z = z_function(word);
        for(int i = k; i < n; i += k) {
            int len = n - 1 - i + 1;
            if(z[i] == len) return i / k;
        }
        return n % k == 0 ? n / k : n / k + 1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}