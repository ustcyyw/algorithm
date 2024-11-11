/**
 * @Time : 2024/1/2-12:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumLength(string s) {
        int n = s.length();
        vector<vector<int>> lens(26);
        for(int i = 0, j; i < n;) {
            j = i + 1;
            while(j < n && s[j] == s[i]) j++;
            lens[s[i] - 'a'].push_back(j - i);
            i = j;
        }
        function<bool(int)> check = [&](int val) -> bool {
            for(auto& len : lens) {
                int cnt = 0;
                for(int& l : len) {
                    if(l >= val) cnt += l - val + 1;
                    if(cnt >= 3) return true;
                }
            }
            return false;
        };
        int lo = 0, hi = n - 2;
        while(lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if(check(mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo == 0 ? -1 : lo;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}