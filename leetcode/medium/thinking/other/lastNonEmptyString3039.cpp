/**
 * @Time : 2024/2/29-9:52 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 每次每个存在的字母都要删除最靠前的一个 那么最后一轮删除的一定是出现次数最多的那些字母
    string lastNonEmptyString(string s) {
        vector<int> count(26, 0), pick(26, 0);
        for(char c : s)
            count[c - 'a']++;
        for(int i = 0, cnt = -1; i < 26; i++) {
            if(count[i] > cnt) pick.assign(26, 0), cnt = count[i];
            if(count[i] == cnt) pick[i] = 1;
        }
        string res;
        for(int i = s.size() - 1; i >= 0; i--) {
            if(pick[s[i] - 'a']) {
                res.push_back(s[i]);
                pick[s[i] - 'a'] = 0; // 取过了就不再取
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}