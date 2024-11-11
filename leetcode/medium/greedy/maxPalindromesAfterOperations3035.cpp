/**
 * @Time : 2024/2/25-4:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) {
        vector<int> cnt(26, 0);
        for(string& word : words) {
            for(char c : word)
                cnt[c - 'a']++;
        }
        sort(words.begin(), words.end(),
             [](auto& a, auto& b) -> bool {return a.size() < b.size();});
        int res = 0, even = 0, odd = 0; // even: 成对的字母个数；odd不成对的字母个数
        for(int num : cnt) {
            if(num % 2 == 0) even += num;
            else even += num - 1, odd++;
        }
        for(string& word : words) {
            if(fill(even, odd, word.size())) res++;
            else break;
        }
        return res;
    }

    bool fill(int& even, int& odd, int n) {
        if(n % 2 == 1) {
            if(odd > 0) odd--; // 字符长度为奇数 先使用单独字母放中间
            else if(even > 0) odd = 1, even -= 2; // 没有单独字母了 拆一个成对的字母去用 还剩一个又变成单独字母了
            else return false;
            n--;
        }
        even -= n;
        return even >= 0;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}