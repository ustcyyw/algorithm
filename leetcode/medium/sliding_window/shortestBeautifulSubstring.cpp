/**
 * @Time : 2023/10/15-12:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛367 t2
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size(), len = INT_MAX, left = 0, right = 0, cnt = 0;
        string res = "";
        while (right < n) {
            cnt += s[right] - '0';
            while (cnt == k) cnt -= s[left++] - '0';
            if(cnt == k - 1 && (left != 0 && s[left - 1] == '1')) {
                string temp = s.substr(left - 1, len);
                if(right - left + 2 < len) {
                    len = right - left + 2;
                    res = temp;
                } else if(right - left + 2 == len)
                    if(temp < res) res = temp;
            }
            right++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}