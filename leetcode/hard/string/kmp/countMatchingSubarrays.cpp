/**
 * @Time : 2024/2/11-3:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛384 t4
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 找匹配模式 只与数字大小有关 先将具体数字转化为代表大小关系的字符串
     * 大小关系的表示与pattern统一。
     * 另外特殊处理-1，可以将每个大小关系都+1来避免出现-1。
     * 处理完成后 使用kmp找匹配串即可。
     */
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        string s, p;
        for(int num : pattern)
            p.push_back((char)(num + 1 + '0'));
        for(int i = 0; i < nums.size() - 1; i++) {
            if(nums[i + 1] > nums[i]) s.push_back('2');
            else if(nums[i + 1] == nums[i]) s.push_back('1');
            else s.push_back('0');
        }
        return kmp(s, p).size();
    }

    vector<int> kmp(string &text, string &pattern) {
        int m = pattern.length();
        vector<int> pi(m), res;
        for (int i = 1, c = 0; i < m; i++) {
            char v = pattern[i];
            while (c && pattern[c] != v)
                c = pi[c - 1];
            if (pattern[c] == v) c++;
            pi[i] = c;
        }
        for (int i = 0, c = 0; i < text.length(); i++) {
            char v = text[i];
            while (c && pattern[c] != v)
                c = pi[c - 1];
            if (pattern[c] == v) c++;
            if (c == m) {
                res.push_back(i - m + 1);
                c = pi[c - 1];
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}