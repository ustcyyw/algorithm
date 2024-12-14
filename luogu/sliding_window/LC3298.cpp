/**
 * @Time : 2024/12/13-1:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3298 滑动窗口
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        unordered_map<char, int> cnt1, cnt2;
        for(char c : word2)
            cnt2[c]++;
        long long ans = 0;
        for(int n = word1.size(), lo = 0, hi = 0, m = 0, total = cnt2.size(); hi < n; ) {
            while(hi < n && m < total) {
                char c = word1[hi++];
                if(++cnt1[c] == cnt2[c]) m++;
            }
            while(lo < hi && m == total) {
                ans += n - 1 - (hi - 1) + 1;
                char c = word1[lo];
                if(--cnt1[c] == cnt2[c] - 1) m--;
                lo++;
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}