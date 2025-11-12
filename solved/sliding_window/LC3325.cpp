/**
 * @Time : 2024/12/12-11:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3325 滑动窗口
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        int n = s.size(), ans = 0;
        vector<int> cnt(26, 0);
        for(int lo = 0, hi = 0, m = 0; lo < n; lo++) {
            while(m == 0 && hi < n) {
                cnt[s[hi] - 'a']++;
                if(cnt[s[hi] - 'a'] == k) m++;
                hi++;
            }
            if(m > 0) ans += n - 1 - (hi - 1) + 1;
            cnt[s[lo] - 'a']--;
            if(cnt[s[lo] - 'a'] == k - 1) m--;
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}