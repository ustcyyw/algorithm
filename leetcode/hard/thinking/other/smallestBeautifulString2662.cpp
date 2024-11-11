/**
 * @Time : 2023/5/2-9:50 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 美丽字符串不能有长度大于1的回文串。
     * 意味着s[i] != s[i - 1] 并且 s[i] != s[i - 2]。
     *
     * 要让答案字符串ans字典序大于s，并且是满足以上条件的字典序最小的字符串
     * ans字典序 > s，在ans和s长度一致的情况下，肯定是在某一个位置处 ans[i] > s[i]
     * 要让ans是满足条件的最小字符串，应该尽可能的让i靠右
     * 因此从右开始枚举，看哪一位可以找到ans[i] > s[i], 且 ans[i] < k
     * 并且满足ans[i] != ans[i - 1], ans[i] != ans[i - 2]。注意i位置的左边都有ans[j] = s[j]
     * 找到这一个位置的字符后，保证了ans的字典序 > s
     * i右边位置的字符，就在满足ans[i] != ans[i - 1], ans[i] != ans[i - 2]的情况下 尽可能地小即可
     */
    string smallestBeautifulString(string s, int k) {
        int n = s.size();
        for(int i = n - 1; i >= 0; i--) { // 枚举在哪一位更大
            int cur = get_char(s, i, s[i] - 'a' + 1);
            if(cur >= k) continue;
            string ans = s.substr(0, i);
            ans.push_back((char)(cur + 'a'));
            for(int j = i + 1; j < n; j++){
                char next = (char)(get_char(ans, ans.size(), 0) + 'a');
                ans.push_back(next);
            }
            return ans;
        }
        return "";
    }
    // 获得放在i索引的字符，这个字符保证美丽字符串的条件，并且字典序尽可能小，从start开始尝试
    int get_char(string& s, int i, int start) {
        if(i == 0) return start;
        if(i == 1) {
            for(int cur = start, p = s[i - 1] - 'a'; ; cur++)
                if (cur != p) return cur;
        }
        for(int cur = start, p = s[i - 1] - 'a', pp = s[i - 2] - 'a'; ; cur++){
            if(cur != p && cur != pp) return cur;
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}