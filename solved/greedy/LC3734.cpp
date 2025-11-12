/**
 * @Time : 2025/11/3-20:39
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3734 2360 贪心 暴力枚举 类似LC3720
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, m;
    string target;
    string lexPalindromicPermutation(string s, string target) {
        n = target.size(), m = n / 2, this->target = target;
        vector<int> count(26, 0);
        for(char c : s)
            count[c - 'a']++;
        // 先检查是否可以得到回文串
        int cnt = 0;
        for(int j = 0; j < 25; j++)
            cnt += count[j] % 2;
        if(cnt > 1) return "";
        vector<int> arr1 = count, arr2 = count;
        // 考虑特殊的前一半都与target相同的回文串是否可行
        string p = build(arr1, m);
        if(p > target) return p;
        // 枚举s和target可能的最大相同前缀s[0,i-1]
        int idx = -1, c = -1;
        for(int i = 0; i < m; i++) {
            int temp = check(count, i);
            if(temp != -1)
                idx = i, c = temp;
            if(count[target[i] - 'a'] >= 2) count[target[i] - 'a'] -= 2;
            else break;
        }
        if(idx == -1) return "";
        string ans = build(arr2, idx);
        ans[idx] = ans[n - 1 - idx] = (char)(c + 'a'), arr2[c] -= 2;
        for(int i = idx + 1, j = 0; i < m; i++) {
            while(arr2[j] == 0) j++;
            ans[i] = ans[n - 1 - i] = (char)(j + 'a'), arr2[j] -= 2;
        }
        return ans;
    }

    string build(vector<int>& count, int idx) {
        string ans(n, '.');
        for(int i = 0, j = n - 1; i < idx; i++, j--) {
            if(count[target[i] - 'a'] < 2) return "";
            ans[i] = ans[j] = target[i];
            count[target[i] - 'a'] -= 2;
        }
        for(int i = 0; i < 26; i++) {
            if(count[i] % 2 == 1)
                ans[m] = (char)(i + 'a'), count[i]--;
        }
        return ans;
    }

    int check(vector<int>& count, int idx) {
        for(int j = target[idx] - 'a' + 1; j < 26; j++)
            if(count[j] > 1) return j;
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}