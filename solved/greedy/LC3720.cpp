/**
 * @Time : 2025/10/20-12:53
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3720 1944 贪心
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        vector<int> count(26, 0);
        for(char c : s)
            count[c - 'a']++;
        int idx = -1, cc = -1;
        for(int i = 0; i < s.size(); i++) {
            int temp = check(target, count, i);
            if(temp != -1) idx = i, cc = temp;
        }
        if(cc == -1) return "";
        target[idx] = (char)(cc + 'a');
        for(int i = 0; i <= idx; i++)
            count[target[i] - 'a']--;
        for(int i = idx + 1, j = 0; i < target.size(); i++) {
            while(count[j] == 0) j++;
            target[i] = (char)(j + 'a');
            count[j]--;
        }
        return target;
    }
    // 检测前缀target[0,hi-1]相同的情况下，s能不能比target字典序大
    int check(string& target, vector<int> cnt, int hi) {
        for(int i = 0; i < hi; i++) {
            int t = target[i] - 'a';
            if(cnt[t] == 0) return -1;
            cnt[t]--;
        }
        int t = target[hi] - 'a';
        for(int i = t + 1; i < 26; i++)
            if(cnt[i] > 0) return i;
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}